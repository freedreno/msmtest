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

#ifndef COMMON_H
#define COMMON_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm/drm_fourcc.h>

#include <freedreno_drmif.h>
#include <freedreno_ringbuffer.h>

#include "util.h"
#include "ring.h"
#include "adreno_common.xml.h"
#include "adreno_pm4.xml.h"


/**
 * upper_32_bits - return bits 32-63 of a number
 * @n: the number we're accessing
 *
 * A basic shift-right of a 64- or 32-bit quantity.  Use this to suppress
 * the "right shift count >= width of type" warning when that quantity is
 * 32-bits.
 */
#define upper_32_bits(n) ((uint32_t)(((n) >> 16) >> 16))

/**
 * lower_32_bits - return bits 0-31 of a number
 * @n: the number we're accessing
 */
#define lower_32_bits(n) ((uint32_t)(n))


struct msm_device {
	int fd;
	struct fd_device *dev;
	struct fd_pipe *pipe;
	struct fd_ringbuffer *ring;
	uint32_t gpu_id;
};

struct msm_device * msm_device_open(void);

struct msm_bo;

struct msm_screen {
	drmModeModeInfo *mode;
	uint32_t crtc_id;
	uint32_t connector_id;
	struct msm_bo *scanout;
};

struct msm_screen * msm_screen_setup(struct msm_device *dev);

struct msm_bo {
	struct msm_device *dev;
	struct fd_bo *bo;
	uint64_t addr;   /* if !bo */
	uint32_t fb_id;
	uint32_t width, height, stride, cpp;
	uint32_t format;
};

struct msm_bo *msm_bo_new(struct msm_device *dev, uint32_t width,
		uint32_t height, uint32_t format);
struct msm_bo *msm_bo_new_addr(struct msm_device *dev, uint32_t width,
		uint32_t height, uint32_t format, uint64_t addr);
void msm_bo_emit(struct msm_bo *bo, struct fd_ringbuffer *ring, uint32_t off);

static inline
int fourcc2cpp(uint32_t format)
{
	switch (format) {
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
		return 4;
	default:
		// TODO maybe more formats someday
		printf("unknown format\n");
		return 0;
	}
}

static void
hexdump_dwords(const void *data, int sizedwords)
{
	uint32_t *buf = (void *) data;
	int i;

	for (i = 0; i < sizedwords; i++) {
		if (!(i % 8))
			printf("\t%08X:   ", (unsigned int) i*4);
		printf(" %08x", buf[i]);
		if ((i % 8) == 7)
			printf("\n");
	}

	if (i % 8)
		printf("\n");
}

static inline uint32_t
env2u(const char *envvar)
{
	char *str = getenv(envvar);
	if (str)
		return strtoul(str, NULL, 0);
	return 0;
}

#endif /* COMMON_H */
