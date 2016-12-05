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

static void
emit_dst(struct fd_ringbuffer *ring, struct msm_bo *dst)
{
	OUT_PKT4(ring, REG_A5XX_RB_2D_DST_INFO, 9);
	OUT_RING(ring, A5XX_RB_2D_DST_INFO_COLOR_FORMAT(bo_fmt(dst)) |
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
}

static void
emit_src(struct fd_ringbuffer *ring, struct msm_bo *src)
{
	OUT_PKT4(ring, REG_A5XX_RB_2D_SRC_INFO, 9);
	OUT_RING(ring, A5XX_RB_2D_SRC_INFO_COLOR_FORMAT(bo_fmt(src)) |
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
}

static void
blit_fill(struct fd_ringbuffer *ring, struct msm_bo *dst, uint32_t color,
		int x1, int y1, int x2, int y2)
{
	OUT_PKT4(ring, REG_A5XX_UNKNOWN_2100, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_2100 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_2180, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_2180 */

	OUT_PKT4(ring, REG_A5XX_RB_2D_SRC_SOLID_DW0, 4);
	OUT_RING(ring, color);        /* RB_2D_SRC_SOLID_DW0 */
	OUT_RING(ring, 0x00000000);   /* RB_2D_SRC_SOLID_DW1 */
	OUT_RING(ring, 0x00000000);   /* RB_2D_SRC_SOLID_DW2 */
	OUT_RING(ring, 0x00000000);   /* RB_2D_SRC_SOLID_DW3 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_2184, 1);
	OUT_RING(ring, 0x00000001);   /* UNKNOWN_2184 */

	emit_dst(ring, dst);

	OUT_PKT7(ring, CP_BLIT, 5);
	OUT_RING(ring, CP_BLIT_0_OP(BLIT_OP_FILL));
	OUT_RING(ring, CP_BLIT_1_SRC_X1(0)  | CP_BLIT_1_SRC_Y1(0));
	OUT_RING(ring, CP_BLIT_2_SRC_X2(0)  | CP_BLIT_2_SRC_Y2(0));
	OUT_RING(ring, CP_BLIT_3_DST_X1(x1) | CP_BLIT_3_DST_Y1(y1));
	OUT_RING(ring, CP_BLIT_4_DST_X2(x2) | CP_BLIT_4_DST_Y2(y2));
}

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

	emit_dst(ring, dst);
	emit_src(ring, src);

	OUT_PKT7(ring, CP_BLIT, 5);
	OUT_RING(ring, CP_BLIT_0_OP(BLIT_OP_COPY));
	OUT_RING(ring, CP_BLIT_1_SRC_X1(sx1) | CP_BLIT_1_SRC_Y1(sy1));
	OUT_RING(ring, CP_BLIT_2_SRC_X2(sx2) | CP_BLIT_2_SRC_Y2(sy2));
	OUT_RING(ring, CP_BLIT_3_DST_X1(dx1) | CP_BLIT_3_DST_Y1(dy1));
	OUT_RING(ring, CP_BLIT_4_DST_X2(dx2) | CP_BLIT_4_DST_Y2(dy2));
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

	a5xx_set_render_mode(ring, BLIT2D);

	blit_fill(ring, screen->scanout, 0xff666666, 0, 0,
			screen->mode->hdisplay - 1, screen->mode->vdisplay - 1);

	blit_fill(ring, screen->scanout, 0xff884422, 10, 10, 265, 265);
	blit_fill(ring, screen->scanout, 0xff224488, 276, 20, 531, 275);
	blit_copy(ring, screen->scanout, 512, 512, 767, 767,
			screen->scanout, 10, 10, 265, 265);

	a5xx_set_render_mode(ring, 0x8);

	fd_ringbuffer_flush(dev->ring);

	sleep(20);

	return 0;
}
