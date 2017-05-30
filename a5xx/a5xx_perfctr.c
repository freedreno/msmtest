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

struct sample {
	uint64_t alwayson;
	uint64_t timestamp;
};

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

	OUT_PKT4(ring, REG_A5XX_CP_PERFCTR_CP_SEL_0, 1);
	OUT_RING(ring, PERF_CP_ALWAYS_COUNT);

	OUT_PKT7(ring, CP_WAIT_FOR_IDLE, 0);

#define COUNT 9

	for (i = 0; i < COUNT; i++) {
		OUT_PKT7(ring, CP_REG_TO_MEM, 3);
		OUT_RING(ring, REG_A5XX_RBBM_PERFCTR_CP_0_LO);
		OUT_RELOCW(ring, bo, i * sizeof(struct sample) + 0, 0, 0);

		OUT_PKT7(ring, CP_REG_TO_MEM, 3);
		OUT_RING(ring, REG_A5XX_RBBM_PERFCTR_CP_0_HI);
		OUT_RELOCW(ring, bo, i * sizeof(struct sample) + 4, 0, 0);

		OUT_PKT7(ring, CP_EVENT_WRITE, 4);
		OUT_RING(ring, CP_EVENT_WRITE_0_EVENT(CACHE_FLUSH_AND_INV_EVENT) |CP_EVENT_WRITE_0_TIMESTAMP);
		OUT_RELOCW(ring, bo, i * sizeof(struct sample) + 8, 0, 0);
		OUT_RING(ring, 0x00000000);
	}

	fd_ringbuffer_flush(dev->ring);

	fd_bo_cpu_prep(bo, dev->pipe, DRM_FREEDRENO_PREP_READ);

	struct sample *samples = fd_bo_map(bo);

	for (i = 0; i < COUNT; i++) {
		printf("samples[%u].alwayson:  %llu", i, samples[i].alwayson);
		if (i > 0)
			printf("   (delta: %llu)", samples[i].alwayson - samples[i-1].alwayson);
		printf("\n");
		printf("samples[%u].timestamp: %llu", i, samples[i].timestamp);
		if (i > 0)
			printf("   (delta: %llu)", samples[i].timestamp - samples[i-1].timestamp);
		printf("\n");
	}

	return 0;
}
