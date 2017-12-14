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


#include "common.h"
#include "a5xx.xml.h"


int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct fd_ringbuffer *ring;
	struct fd_bo *indirect;  /* indirect command buffer */
	struct fd_bo *index;     /* index buffer (for glDrawElementsIndirect() case) */
	int elements = 0;
	int i;

	if ((argc > 1) && !strcmp(argv[1], "elements"))
		elements = 1;

	dev = msm_device_open();
	if (!dev)
		return -1;
	ring = dev->ring;

	indirect = fd_bo_new(dev->dev, 0x1000, 0);

	uint32_t *ptr = fd_bo_map(indirect);

	if (elements) {
		printf("draw-elements-indirect");

		// DrawElementsIndirectCommand
		ptr[0] = 0x7;     // count
		ptr[1] = 0x9;     // instance_count
		ptr[2] = 0xb;     // start
		ptr[3] = 0xa;     // index_bias
		ptr[4] = 0xc;     // start_instance

		index = fd_bo_new(dev->dev, 0x1000, 0);

		ptr = fd_bo_map(index);

		for (i = 0; i < 0x1000/4; i++)
			ptr[i] = i;

		OUT_PKT7(ring, CP_DRAW_INDX_INDIRECT, 6);
		OUT_RING(ring, CP_DRAW_INDX_OFFSET_0_PRIM_TYPE(DI_PT_TRILIST) |
				CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT(DI_SRC_SEL_DMA) |
				CP_DRAW_INDX_OFFSET_0_INDEX_SIZE(INDEX4_SIZE_32_BIT) |
				CP_DRAW_INDX_OFFSET_0_VIS_CULL(0));
		OUT_RELOC(ring, index, 0, 0, 0);
		OUT_RING(ring, A5XX_CP_DRAW_INDX_INDIRECT_3_MAX_INDICES(0x1000/4));
		OUT_RELOC(ring, indirect, 0, 0, 0);

	} else {
		printf("draw-arrays-indirect!\n");

		// DrawArraysIndirectCommand:
		ptr[0] = 0x7;     // count
		ptr[1] = 0x9;     // instance_count
		ptr[2] = 0xb;     // start
		ptr[3] = 0xc;     // start_instance

		OUT_PKT7(ring, CP_DRAW_INDIRECT, 3);
		OUT_RING(ring, CP_DRAW_INDX_OFFSET_0_PRIM_TYPE(DI_PT_TRILIST) |
				CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT(DI_SRC_SEL_AUTO_INDEX) |
				CP_DRAW_INDX_OFFSET_0_INDEX_SIZE(0) |
				CP_DRAW_INDX_OFFSET_0_VIS_CULL(0));
		OUT_RELOC(ring, indirect, 0, 0, 0);
	}

	fd_ringbuffer_flush(dev->ring);

	return 0;
}
