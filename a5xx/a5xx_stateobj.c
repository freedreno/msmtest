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


int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct fd_ringbuffer *stateobj;
	struct fd_bo *bo;
	int i;

	dev = msm_device_open();
	if (!dev)
		return -1;

	bo = fd_bo_new(dev->dev, 0x1000, 0);

	/*
	 * Setup a "stateobj" to copy the contents of SCRATCH[4]-SCRATCH[6]
	 * to memory:
	 */
	stateobj = fd_ringbuffer_new_object(dev->pipe, 0x1000);

	OUT_PKT7(stateobj, CP_REG_TO_MEM, 3);
	OUT_RING(stateobj, CP_REG_TO_MEM_0_REG(REG_A5XX_CP_SCRATCH_REG(4)));
	OUT_RELOCW(stateobj, bo, 0, 0, 0);

	OUT_PKT7(stateobj, CP_REG_TO_MEM, 3);
	OUT_RING(stateobj, CP_REG_TO_MEM_0_REG(REG_A5XX_CP_SCRATCH_REG(5)));
	OUT_RELOCW(stateobj, bo, 4, 0, 0);

	OUT_PKT7(stateobj, CP_REG_TO_MEM, 3);
	OUT_RING(stateobj, CP_REG_TO_MEM_0_REG(REG_A5XX_CP_SCRATCH_REG(6)));
	OUT_RELOCW(stateobj, bo, 8, 0, 0);

	for (i = 0; i < 4; i++) {
		struct fd_ringbuffer *ib1, *ib2;

		ib1 = fd_ringbuffer_new(dev->pipe, 0);
		ib2 = fd_ringbuffer_new(dev->pipe, 0);

		fd_ringbuffer_set_parent(ib2, ib1);

		OUT_PKT4(ib1, REG_A5XX_CP_SCRATCH_REG(4), 1);
		OUT_RING(ib1, 0x01 + 2 * i);

		OUT_PKT4(ib1, REG_A5XX_CP_SCRATCH_REG(5), 2);
		OUT_RELOC(ib1, bo, 0, 0, 0);

		OUT_PKT7(ib1, CP_SET_DRAW_STATE, 3);
		OUT_RING(ib1, CP_SET_DRAW_STATE__0_DISABLE_ALL_GROUPS);
		OUT_RING(ib1, 0);
		OUT_RING(ib1, 0);

		unsigned n = fd_ringbuffer_size(stateobj) / 4;
		OUT_PKT7(ib1, CP_SET_DRAW_STATE, 3);
		OUT_RING(ib1, CP_SET_DRAW_STATE__0_COUNT(n) |
			CP_SET_DRAW_STATE__0_GROUP_ID(0) |
			CP_SET_DRAW_STATE__0_LOAD_IMMED);
		OUT_RB(ib1, stateobj);

		OUT_PKT7(ib2, CP_SET_DRAW_STATE, 3);
		OUT_RING(ib2, CP_SET_DRAW_STATE__0_DISABLE_ALL_GROUPS);
		OUT_RING(ib2, 0);
		OUT_RING(ib2, 0);

		OUT_PKT4(ib2, REG_A5XX_CP_SCRATCH_REG(4), 1);
		OUT_RING(ib2, 0x02 + 2 * i);

		OUT_PKT7(ib2, CP_SET_DRAW_STATE, 3);
		OUT_RING(ib2, CP_SET_DRAW_STATE__0_COUNT(n) |
			CP_SET_DRAW_STATE__0_GROUP_ID(0) |
			CP_SET_DRAW_STATE__0_LOAD_IMMED);
		OUT_RB(ib2, stateobj);

		OUT_IB5(ib1, ib2);

		fd_ringbuffer_flush(ib1);

		fd_ringbuffer_del(ib1);
		fd_ringbuffer_del(ib2);

		fd_bo_cpu_prep(bo, dev->pipe, DRM_FREEDRENO_PREP_READ);

		hexdump_dwords(fd_bo_map(bo), 4);
	}


	return 0;
}
