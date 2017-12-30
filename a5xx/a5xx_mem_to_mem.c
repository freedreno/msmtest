/*
 * Copyright (C) 2017 Rob Clark <robclark@freedesktop.org>
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

/* could be this is not so much a5xx specific.. */

#include "common.h"
#include "a5xx.xml.h"


int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct fd_ringbuffer *ring;
	struct fd_bo *bo;
	int i;

	dev = msm_device_open();
	if (!dev)
		return -1;
	ring = dev->ring;

	bo = fd_bo_new(dev->dev, 0x1000, 0);

	uint32_t *ptr = fd_bo_map(bo);
	for (i = 0; i < 32; i++)
		ptr[i] = i;

	OUT_PKT7(ring, CP_MEM_TO_MEM, 9);
	OUT_RING(ring, 0x20000004);
	OUT_RELOCW(ring, bo,  0, 0, 0);
	OUT_RELOCW(ring, bo,  4, 0, 0);
	OUT_RELOCW(ring, bo,  8, 0, 0);
	OUT_RELOCW(ring, bo, 12, 0, 0);

	fd_ringbuffer_flush(dev->ring);

	fd_bo_cpu_prep(bo, dev->pipe, DRM_FREEDRENO_PREP_READ);

	hexdump_dwords(ptr, 32);

	return 0;
}
