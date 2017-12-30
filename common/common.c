/*
 * Copyright (C) 2016 Rob Clark <robclark@freedesktop.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */

#include "common.h"

/*
 * device
 */

struct msm_device * msm_device_open(void)
{
	struct msm_device *dev = calloc(1, sizeof(*dev));
	uint64_t val;

	dev->fd = drmOpen("msm", NULL);
	if (dev->fd < 0)
		return NULL;

	dev->dev = fd_device_new(dev->fd);
	if (!dev->dev) {
		printf("failed to initialize freedreno device\n");
		return NULL;
	}

	dev->pipe = fd_pipe_new(dev->dev, FD_PIPE_3D);
	if (!dev->pipe) {
		printf("failed to initialize freedreno pipe\n");
		return NULL;
	}

	if (fd_pipe_get_param(dev->pipe, FD_GPU_ID, &val)) {
		printf("could not get gpu-id\n");
		return NULL;
	}
	dev->gpu_id = val;

	dev->ring = fd_ringbuffer_new(dev->pipe, 0x10000);
	if (!dev->ring) {
		printf("failed to initialize freedreno ring\n");
		return NULL;
	}

	return dev;
}

/*
 * screen
 */

struct msm_screen * msm_screen_setup(struct msm_device *dev)
{
	struct msm_screen *screen = calloc(1, sizeof(*screen));

	drmModeRes *resources;
	drmModeConnector *connector = NULL;
	drmModeEncoder *encoder = NULL;
	int ret, i, area;

	resources = drmModeGetResources(dev->fd);
	if (!resources) {
		printf("drmModeGetResources failed: %s\n", strerror(errno));
		return NULL;
	}

	/* find a connected connector: */
	for (i = 0; i < resources->count_connectors; i++) {
		connector = drmModeGetConnector(dev->fd, resources->connectors[i]);
		if (connector->connection == DRM_MODE_CONNECTED) {
			/* it's connected, let's use this! */
			break;
		}
		drmModeFreeConnector(connector);
		connector = NULL;
	}

	if (!connector) {
		/* we could be fancy and listen for hotplug events and wait for
		 * a connector..
		 */
		printf("no connected connector!\n");
		return NULL;
	}

	/* find highest resolution mode: */
	for (i = 0, area = 0; i < connector->count_modes; i++) {
		drmModeModeInfo *current_mode = &connector->modes[i];
		int current_area = current_mode->hdisplay * current_mode->vdisplay;
		if (current_area > area) {
			screen->mode = current_mode;
			area = current_area;
		}
	}

	if (!screen->mode) {
		printf("could not find mode!\n");
		return NULL;
	}

	/* find encoder: */
	for (i = 0; i < resources->count_encoders; i++) {
		encoder = drmModeGetEncoder(dev->fd, resources->encoders[i]);
		if (encoder->encoder_id == connector->encoder_id)
			break;
		drmModeFreeEncoder(encoder);
		encoder = NULL;
	}

	if (!encoder) {
		printf("no encoder!\n");
		return NULL;
	}

	screen->crtc_id = encoder->crtc_id;
	screen->connector_id = connector->connector_id;

	screen->scanout = msm_bo_new(dev, screen->mode->hdisplay,
			screen->mode->vdisplay, DRM_FORMAT_ARGB8888);
	if (!screen->scanout)
		return NULL;

	ret = drmModeSetCrtc(dev->fd, screen->crtc_id, screen->scanout->fb_id,
			0, 0, &screen->connector_id, 1, screen->mode);
	if (ret) {
		printf("failed to set mode: %s\n", strerror(errno));
		return NULL;
	}

	return screen;
}

/*
 * buffer object
 */

struct msm_bo *msm_bo_new(struct msm_device *dev, uint32_t width,
		uint32_t height, uint32_t format)
{
	struct msm_bo *bo = calloc(1, sizeof(*bo));
	uint32_t handles[4] = {0};
	uint32_t pitches[4] = {0};
	uint32_t offsets[4] = {0};
	int ret;

	bo->cpp = fourcc2cpp(format);
	if (!bo->cpp)
		return NULL;

	bo->dev = dev;
	bo->width  = width;
	bo->height = height;
	bo->stride = width * bo->cpp;
	bo->format = format;

	bo->bo = fd_bo_new(dev->dev, bo->height * bo->stride, 0);

	handles[0] = fd_bo_handle(bo->bo);
	pitches[0] = bo->stride;

	ret = drmModeAddFB2(dev->fd, width, height, format,
			handles, pitches, offsets, &bo->fb_id, 0);
	if (ret) {
		printf("failed to create fb: %s\n", strerror(errno));
		return NULL;
	}

	return bo;
}

/* for cases where you want to construct a bogus or fixed bo addr: */
struct msm_bo *msm_bo_new_addr(struct msm_device *dev, uint32_t width,
		uint32_t height, uint32_t format, uint64_t addr)
{
	struct msm_bo *bo = calloc(1, sizeof(*bo));
	int cpp;

	cpp = fourcc2cpp(format);
	if (!cpp)
		return NULL;

	bo->dev = dev;
	bo->width  = width;
	bo->height = height;
	bo->stride = width * cpp;
	bo->format = format;

	bo->addr = addr;

	return bo;
}

void msm_bo_emit(struct msm_bo *bo, struct fd_ringbuffer *ring, uint32_t off)
{
	if (bo->bo) {
		OUT_RELOCW(ring, bo->bo, off, 0, 0);
	} else if (bo->dev->gpu_id < 500) {
		OUT_RING(ring, bo->addr + off);
	} else {
		OUT_RING(ring, lower_32_bits(bo->addr + off));
		OUT_RING(ring, upper_32_bits(bo->addr + off));
	}
}
