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
blit_event(struct fd_ringbuffer *ring)
{
	OUT_PKT7(ring, CP_EVENT_WRITE, 4);
	OUT_RING(ring, CP_EVENT_WRITE_0_EVENT(BLIT));
	OUT_RELOCW(ring, blit_mem, 0, 0, 0);    /* ADDR_LO/HI */
	OUT_RING(ring, 0x00000000);
}

static void
dma_fill(struct fd_ringbuffer *ring, struct msm_bo *dst, uint32_t color)
{
	OUT_PKT4(ring, REG_A5XX_RB_MRT_BUF_INFO(0), 5);
	OUT_RING(ring, A5XX_RB_MRT_BUF_INFO_COLOR_FORMAT(bo_fmt(dst)) |
			A5XX_RB_MRT_BUF_INFO_COLOR_TILE_MODE(TILE5_LINEAR) |
			A5XX_RB_MRT_BUF_INFO_COLOR_SWAP(bo_swap(dst)));
	OUT_RING(ring, A5XX_RB_MRT_PITCH(dst->stride));
	OUT_RING(ring, A5XX_RB_MRT_ARRAY_PITCH(dst->stride * dst->height));
	msm_bo_emit(dst, ring, 0);    /* RB_MRT[i].BASE_LO/HI */

	OUT_PKT4(ring, REG_A5XX_SP_FS_MRT_REG(0), 1);
	OUT_RING(ring, A5XX_SP_FS_MRT_REG_COLOR_FORMAT(bo_fmt(dst)));

	OUT_PKT4(ring, REG_A5XX_RB_BLIT_CNTL, 1);
	OUT_RING(ring, A5XX_RB_BLIT_CNTL_BUF(BLIT_MRT0));

	OUT_PKT4(ring, REG_A5XX_RB_CLEAR_CNTL, 1);
	OUT_RING(ring, A5XX_RB_CLEAR_CNTL_FAST_CLEAR |
			A5XX_RB_CLEAR_CNTL_MASK(0xf));

	OUT_PKT4(ring, REG_A5XX_RB_CLEAR_COLOR_DW0, 4);
	OUT_RING(ring, color);        /* RB_CLEAR_COLOR_DW0 */
	OUT_RING(ring, 0x00000000);   /* RB_CLEAR_COLOR_DW1 */
	OUT_RING(ring, 0x00000000);   /* RB_CLEAR_COLOR_DW2 */
	OUT_RING(ring, 0x00000000);   /* RB_CLEAR_COLOR_DW3 */

	blit_event(ring);
}

static int
dma_offset(struct msm_bo *bo, int x, int y)
{
	return (bo->stride * y) + (bo->cpp * x);
}

/* src coords, set dest coords via set_scissor() */
static void
dma_copy(struct fd_ringbuffer *ring, struct msm_bo *dst, struct msm_bo *src,
		int dstx, int dsty, int srcx, int srcy)
{
	OUT_PKT4(ring, REG_A5XX_RB_MRT_BUF_INFO(0), 5);
	OUT_RING(ring, A5XX_RB_MRT_BUF_INFO_COLOR_FORMAT(bo_fmt(src)) |
			A5XX_RB_MRT_BUF_INFO_COLOR_TILE_MODE(TILE5_LINEAR) |
			A5XX_RB_MRT_BUF_INFO_COLOR_SWAP(bo_swap(src)));
	OUT_RING(ring, A5XX_RB_MRT_PITCH(src->stride));
	OUT_RING(ring, A5XX_RB_MRT_ARRAY_PITCH(src->stride * src->height));
	msm_bo_emit(src, ring, dma_offset(src, srcx, srcy));   /* RB_MRT[i].BASE_LO/HI */

	OUT_PKT4(ring, REG_A5XX_SP_FS_MRT_REG(0), 1);
	OUT_RING(ring, A5XX_SP_FS_MRT_REG_COLOR_FORMAT(bo_fmt(dst)));

	OUT_PKT4(ring, REG_A5XX_RB_RESOLVE_CNTL_3, 5);
	OUT_RING(ring, 0x00000004);   /* XXX RB_RESOLVE_CNTL_3 */
	msm_bo_emit(dst, ring, dma_offset(dst, dstx, dsty));   /* RB_BLIT_DST_LO/HI */
	OUT_RING(ring, A5XX_RB_BLIT_DST_PITCH(dst->stride));
	OUT_RING(ring, A5XX_RB_BLIT_DST_ARRAY_PITCH(dst->stride * dst->height));

	OUT_PKT4(ring, REG_A5XX_RB_BLIT_CNTL, 1);
	OUT_RING(ring, A5XX_RB_BLIT_CNTL_BUF(BLIT_MRT0));

	OUT_PKT4(ring, REG_A5XX_RB_CLEAR_CNTL, 1);
	OUT_RING(ring, 0x00000000);

	blit_event(ring);
}

static void
set_scissor(struct fd_ringbuffer *ring, int x1, int y1, int x2, int y2)
{

	OUT_PKT4(ring, REG_A5XX_GRAS_SC_WINDOW_SCISSOR_TL, 2);
	OUT_RING(ring, A5XX_GRAS_SC_WINDOW_SCISSOR_TL_X(x1) |
			A5XX_GRAS_SC_WINDOW_SCISSOR_TL_Y(y1));
	OUT_RING(ring, A5XX_GRAS_SC_WINDOW_SCISSOR_BR_X(x2 - 1) |
			A5XX_GRAS_SC_WINDOW_SCISSOR_BR_Y(y2 - 1));

	OUT_PKT4(ring, REG_A5XX_RB_RESOLVE_CNTL_1, 2);
	OUT_RING(ring, A5XX_RB_RESOLVE_CNTL_1_X(x1) |
			A5XX_RB_RESOLVE_CNTL_1_Y(y1));
	OUT_RING(ring, A5XX_RB_RESOLVE_CNTL_2_X(x2 - 1) |
			A5XX_RB_RESOLVE_CNTL_2_Y(y2 - 1));

	OUT_PKT4(ring, REG_A5XX_RB_WINDOW_OFFSET, 1);
	OUT_RING(ring, A5XX_RB_WINDOW_OFFSET_X(x1) |
			A5XX_RB_WINDOW_OFFSET_Y(y1));
}

int main(int argc, char *argv[])
{
	struct msm_device *dev;
	struct msm_screen *screen;
	struct fd_ringbuffer *ring;
	int i;

	dev = msm_device_open();
	if (!dev)
		return -1;
	ring = dev->ring;

	screen = msm_screen_setup(dev);
	if (!screen)
		return -1;

	blit_mem = fd_bo_new(dev->dev, 0x1000, 0);

	sleep(2); /* give a chance for monitor to come in sync */

	a5xx_emit_restore(dev->ring);

	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, UNK_26);

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
	OUT_RING(ring, A5XX_RB_CNTL_WIDTH(screen->mode->hdisplay) |
			A5XX_RB_CNTL_HEIGHT(screen->mode->vdisplay) |
			A5XX_RB_CNTL_BYPASS);

	set_scissor(ring, 0, 0, screen->mode->hdisplay, screen->mode->vdisplay);
	dma_fill(ring, screen->scanout, 0xff666666);

	set_scissor(ring, 10, 10, 266, 266);
	dma_fill(ring, screen->scanout, 0xff884422);

	set_scissor(ring, 276, 20, 532, 276);
	dma_fill(ring, screen->scanout, 0xff224488);

	set_scissor(ring, 0, 0, 256, 256);
	dma_copy(ring, screen->scanout, screen->scanout, 512, 512, 10, 10);

#if 0
	/* blit from hyperspace! */
	dma_copy(ring, screen->scanout, screen->scanout, 512, 512,
			screen->mode->hdisplay - 10, screen->mode->vdisplay - 10);

#define CNT   100
#define NOPSZ 100
	for (int i = 0; i < CNT; i++) {
		OUT_PKT4(ring, REG_A5XX_CP_SCRATCH_REG(4), 1);
		OUT_RING(ring, i);
		OUT_PKT7(ring, CP_NOP, NOPSZ);
		for (int j = 0; j < NOPSZ; j++)
			OUT_RING(ring, 0x00000000);
	}
	set_scissor(ring, 532, 276, 788, 532);
	dma_fill(ring, screen->scanout, 0xffff0000);
#endif

	fd_ringbuffer_flush(dev->ring);

	sleep(20);

	return 0;
}
