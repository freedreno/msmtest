/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2013 Rob Clark <robclark@freedesktop.org>
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

int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct msm_screen *screen;
	struct msm_bo *bo;
	int i;

	dev = msm_device_open();
	if (!dev)
		return -1;

	screen = msm_screen_setup(dev);
	if (!screen)
		return -1;

	/* something simple.. try to write some data into the buffer: */
	bo = screen->scanout;
	for (i = 0; i < 32 /*fb->height*/; i++) {
		uint32_t sizedwords = 256;
		if (dev->gpu_id >= 500) {
			/* NOTE: OUT_RELOC is 2 dwords on 64b devices (a5xx+) */
			OUT_PKT7(dev->ring, CP_MEM_WRITE, sizedwords+2);
		} else {
			OUT_PKT3(dev->ring, CP_MEM_WRITE, sizedwords+1);
		}
		msm_bo_emit(bo, dev->ring, i * bo->stride);
		while (sizedwords--) {
			OUT_RING(dev->ring,
				(sizedwords << 24) |
				(sizedwords << 16) |
				(sizedwords <<  8) |
				(sizedwords <<  0));
		}
	}

	fd_ringbuffer_flush(dev->ring);

	sleep(20);

	return 0;
}
