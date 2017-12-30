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

#include "a5xx_common.h"

static struct fd_bo *blit_mem;

static void
blit_copy(struct fd_ringbuffer *ring, struct msm_bo *dst, int dx1, int dy1, int dx2, int dy2,
		struct msm_bo *src, int sx1, int sy1, int sx2, int sy2)
{
	OUT_PKT4(ring, REG_A5XX_UNKNOWN_2100, 1);
	OUT_RING(ring, 0x86000000);   /* UNKNOWN_2100 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_2180, 1);
	OUT_RING(ring, 0x86000000);   /* UNKNOWN_2180 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_2184, 1);
	OUT_RING(ring, 0x00000009);   /* UNKNOWN_2184 */

	/* emit dst: */
	OUT_PKT4(ring, REG_A5XX_RB_2D_DST_INFO, 9);
	OUT_RING(ring, A5XX_RB_2D_DST_INFO_COLOR_FORMAT(bo_fmt(dst)) |
			A5XX_RB_2D_DST_INFO_TILE_MODE(env2u("TILE")) |
			A5XX_RB_2D_DST_INFO_COLOR_SWAP(bo_swap(dst)));
	msm_bo_emit(dst, ring, 0);    /* RB_2D_DST_LO/HI */
	OUT_RING(ring, A5XX_RB_2D_DST_SIZE_PITCH(dst->stride) |
			A5XX_RB_2D_DST_SIZE_ARRAY_PITCH(dst->stride * dst->height));
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_GRAS_2D_DST_INFO, 1);
	OUT_RING(ring, A5XX_GRAS_2D_DST_INFO_COLOR_FORMAT(bo_fmt(dst)) |
			A5XX_GRAS_2D_DST_INFO_COLOR_SWAP(bo_swap(dst)));

	/* emit src: */
	OUT_PKT4(ring, REG_A5XX_RB_2D_SRC_INFO, 9);
	OUT_RING(ring, A5XX_RB_2D_SRC_INFO_COLOR_FORMAT(bo_fmt(src)) |
//			A5XX_RB_2D_SRC_INFO_TILE_MODE(env2u("TILE")) |
			A5XX_RB_2D_SRC_INFO_COLOR_SWAP(bo_swap(src)));
	msm_bo_emit(src, ring, 0);    /* RB_2D_SRC_LO/HI */
	OUT_RING(ring, A5XX_RB_2D_SRC_SIZE_PITCH(src->stride) |
			A5XX_RB_2D_SRC_SIZE_ARRAY_PITCH(src->stride * src->height));
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_GRAS_2D_SRC_INFO, 1);
	OUT_RING(ring, A5XX_GRAS_2D_SRC_INFO_COLOR_FORMAT(bo_fmt(src)) |
			A5XX_GRAS_2D_SRC_INFO_COLOR_SWAP(bo_swap(src)));

	/* emit blit: */
	OUT_PKT7(ring, CP_BLIT, 5);
	OUT_RING(ring, CP_BLIT_0_OP(BLIT_OP_COPY));
	OUT_RING(ring, CP_BLIT_1_SRC_X1(sx1) | CP_BLIT_1_SRC_Y1(sy1));
	OUT_RING(ring, CP_BLIT_2_SRC_X2(sx2) | CP_BLIT_2_SRC_Y2(sy2));
	OUT_RING(ring, CP_BLIT_3_DST_X1(dx1) | CP_BLIT_3_DST_Y1(dy1));
	OUT_RING(ring, CP_BLIT_4_DST_X2(dx2) | CP_BLIT_4_DST_Y2(dy2));
}

static void
blit_setup(struct fd_ringbuffer *ring)
{
	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, LRZ_FLUSH);

	OUT_PKT7(ring, CP_SKIP_IB2_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x0);

	OUT_PKT4(ring, REG_A5XX_PC_POWER_CNTL, 1);
	OUT_RING(ring, 0x00000003);   /* PC_POWER_CNTL */

	OUT_PKT4(ring, REG_A5XX_VFD_POWER_CNTL, 1);
	OUT_RING(ring, 0x00000003);   /* VFD_POWER_CNTL */

	/* 0x10000000 for BYPASS.. 0x7c13c080 for GMEM: */
	OUT_WFI5(ring);
	OUT_PKT4(ring, REG_A5XX_RB_CCU_CNTL, 1);
	OUT_RING(ring, 0x10000000);   /* RB_CCU_CNTL */

	OUT_PKT4(ring, REG_A5XX_RB_RENDER_CNTL, 1);
	OUT_RING(ring, 0x00000008);

	OUT_PKT4(ring, REG_A5XX_RB_CNTL, 1);
	OUT_RING(ring, A5XX_RB_CNTL_BYPASS);

	a5xx_set_render_mode(ring, BLIT2D);
}

static void
dma_copy(struct fd_ringbuffer *ring, struct msm_bo *dst, struct msm_bo *src,
		int w, int h)
{
	OUT_PKT4(ring, REG_A5XX_RB_CNTL, 1);
	OUT_RING(ring, A5XX_RB_CNTL_WIDTH(w) |
			A5XX_RB_CNTL_HEIGHT(h) |
			A5XX_RB_CNTL_BYPASS);

	OUT_PKT4(ring, REG_A5XX_RB_WINDOW_OFFSET, 1);
	OUT_RING(ring, A5XX_RB_WINDOW_OFFSET_X(0) |
			A5XX_RB_WINDOW_OFFSET_Y(0));

	OUT_PKT4(ring, REG_A5XX_GRAS_SC_WINDOW_SCISSOR_TL, 2);
	OUT_RING(ring, A5XX_GRAS_SC_WINDOW_SCISSOR_TL_X(0) |
			A5XX_GRAS_SC_WINDOW_SCISSOR_TL_Y(0));
	OUT_RING(ring, A5XX_GRAS_SC_WINDOW_SCISSOR_BR_X(w - 1) |
			A5XX_GRAS_SC_WINDOW_SCISSOR_BR_Y(h - 1));

	OUT_PKT4(ring, REG_A5XX_RB_RESOLVE_CNTL_1, 2);
	OUT_RING(ring, A5XX_RB_RESOLVE_CNTL_1_X(0) |
			A5XX_RB_RESOLVE_CNTL_1_Y(0));
	OUT_RING(ring, A5XX_RB_RESOLVE_CNTL_2_X(w - 1) |
			A5XX_RB_RESOLVE_CNTL_2_Y(h - 1));

	OUT_PKT4(ring, REG_A5XX_RB_MRT_BUF_INFO(0), 5);
	OUT_RING(ring, A5XX_RB_MRT_BUF_INFO_COLOR_FORMAT(bo_fmt(src)) |
			A5XX_RB_MRT_BUF_INFO_COLOR_TILE_MODE(TILE5_LINEAR) |
			A5XX_RB_MRT_BUF_INFO_COLOR_SWAP(bo_swap(src)));
	OUT_RING(ring, A5XX_RB_MRT_PITCH(src->stride));
	OUT_RING(ring, A5XX_RB_MRT_ARRAY_PITCH(src->stride * src->height));
	msm_bo_emit(src, ring, 0);    /* RB_MRT[i].BASE_LO/HI */

	OUT_PKT4(ring, REG_A5XX_SP_FS_MRT_REG(0), 1);
	OUT_RING(ring, A5XX_SP_FS_MRT_REG_COLOR_FORMAT(bo_fmt(dst)));

	OUT_PKT4(ring, REG_A5XX_RB_RESOLVE_CNTL_3, 5);
	OUT_RING(ring, 0x00000004);   /* XXX RB_RESOLVE_CNTL_3 */
	msm_bo_emit(dst, ring, 0);    /* RB_BLIT_DST_LO/HI */
	OUT_RING(ring, A5XX_RB_BLIT_DST_PITCH(dst->stride));
	OUT_RING(ring, A5XX_RB_BLIT_DST_ARRAY_PITCH(dst->stride * dst->height));

	OUT_PKT4(ring, REG_A5XX_RB_BLIT_CNTL, 1);
	OUT_RING(ring, A5XX_RB_BLIT_CNTL_BUF(BLIT_MRT0));

	OUT_PKT4(ring, REG_A5XX_RB_CLEAR_CNTL, 1);
	OUT_RING(ring, 0x00000000);

	OUT_PKT7(ring, CP_EVENT_WRITE, 4);
	OUT_RING(ring, CP_EVENT_WRITE_0_EVENT(BLIT));
	OUT_RELOCW(ring, blit_mem, 0, 0, 0);    /* ADDR_LO/HI */
	OUT_RING(ring, 0x00000000);
}

static void
dma_setup(struct fd_ringbuffer *ring)
{
	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, LRZ_FLUSH);

	OUT_PKT7(ring, CP_SKIP_IB2_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x0);

	OUT_PKT4(ring, REG_A5XX_PC_POWER_CNTL, 1);
	OUT_RING(ring, 0x00000003);   /* PC_POWER_CNTL */

	OUT_PKT4(ring, REG_A5XX_VFD_POWER_CNTL, 1);
	OUT_RING(ring, 0x00000003);   /* VFD_POWER_CNTL */

	/* 0x10000000 for BYPASS.. 0x7c13c080 for GMEM: */
	OUT_WFI5(ring);
	OUT_PKT4(ring, REG_A5XX_RB_CCU_CNTL, 1);
	OUT_RING(ring, 0x10000000);   /* RB_CCU_CNTL */

	OUT_PKT4(ring, REG_A5XX_RB_RENDER_CNTL, 1);
	OUT_RING(ring, 0x00000008);
}

int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct msm_bo *src, *dst;
	struct fd_ringbuffer *ring;
	const uint32_t format = DRM_FORMAT_ARGB8888;
	const int cpp = fourcc2cpp(format);
	const int w = 128, h = 16;
	const int p = ALIGN(w, 256);
	uint32_t *ptr;
	int i, j;

	printf("%dx%d pitch=%d\n", w, h, p);

	dev = msm_device_open();
	if (!dev)
		return -1;
	ring = dev->ring;

	blit_mem = fd_bo_new(dev->dev, 0x1000, 0);

	src = msm_bo_new(dev, p, h, format);
	dst = msm_bo_new(dev, p, h, format);

	ptr = fd_bo_map(src->bo);
	memset(ptr, ~0, fd_bo_size(src->bo));

	for (j = 0; j < h; j++) {
		for (i = 0; i < p; i++) {
			ptr[i + (j * p)] = (j << 16) | i;
		}
	}

//	for (j = h; j < (fd_bo_size(src->bo)/cpp)/w; j++) {
//		for (i = 0; i < w; i++) {
//			ptr[i + (j * p)] = 0x80000000 | (i << 16) | j;
//		}
//	}

	a5xx_emit_restore(dev->ring);

	if (env2u("BLIT")) {
		blit_setup(ring);
		blit_copy(ring, dst, 0, 0, w-1, h-1,
				src, 0, 0, w-1, h-1);
	} else {
		dma_setup(ring);
		dma_copy(ring, dst,  src, w, h);
	}

	a5xx_set_render_mode(ring, 0x8);
	a5xx_set_render_mode(ring, GMEM);

	fd_ringbuffer_flush(dev->ring);

	fd_bo_cpu_prep(dst->bo, dev->pipe, DRM_FREEDRENO_PREP_READ);

	ptr = fd_bo_map(dst->bo);

	if (0) {
		for (j = 0; j < h; j++) {
			hexdump_dwords(&ptr[j * p * cpp / 4], p * cpp / 4);
			printf("\n");
		}
	} else {
		hexdump_dwords(ptr, fd_bo_size(dst->bo)/4);
	}

	return 0;
}
