/*
 * Copyright (C) 2018 Rob Clark <robclark@freedesktop.org>
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
#include "a5xx.xml.h"

static inline uint32_t REG_A6XX_CP_SCRATCH_REG(uint32_t i0) { return 0x00000883 + 0x1*i0; }

int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct fd_ringbuffer *ring;
	struct fd_bo *bo;
	int i;

	dev = msm_device_open();
	if (!dev)
		return -1;

	bo = fd_bo_new(dev->dev, 0x1000, 0);

	ring = fd_ringbuffer_new(dev->pipe, 0x1000);

	OUT_PKT7(ring, 0x6d, 3);
	OUT_RING(ring, 0x2);
	OUT_RING(ring, REG_A6XX_CP_SCRATCH_REG(4)); //0x8801);
	OUT_RING(ring, 0x4010);

	OUT_PKT7(ring, CP_WAIT_FOR_IDLE, 0);

	OUT_PKT7(ring, CP_REG_TO_MEM, 3);
	OUT_RING(ring, CP_REG_TO_MEM_0_REG(REG_A6XX_CP_SCRATCH_REG(4)));
	OUT_RELOCW(ring, bo, 0, 0, 0);

	fd_ringbuffer_flush(ring);

	fd_bo_cpu_prep(bo, dev->pipe, DRM_FREEDRENO_PREP_READ);

	hexdump_dwords(fd_bo_map(bo), 4);

	return 0;
}
