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

enum a5xx_color_fmt bo_fmt(struct msm_bo *bo)
{
	switch (bo->format) {
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_BGRA8888:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_BGRX8888:
		return RB5_R8G8B8A8_UNORM;
	default:
		// TODO maybe more formats someday
		printf("unknown format\n");
		return 0;
	}
}

enum a3xx_color_swap bo_swap(struct msm_bo *bo)
{
	switch (bo->format) {
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_XRGB8888:
		return WZYX;
	case DRM_FORMAT_ABGR8888:
	case DRM_FORMAT_XBGR8888:
		return WXYZ;
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_RGBX8888:
		return ZYXW;
	case DRM_FORMAT_BGRA8888:
	case DRM_FORMAT_BGRX8888:
		return XYZW;
	default:
		// TODO maybe more formats someday
		printf("unknown format\n");
		return 0;
	}
}

void
a5xx_emit_marker(struct fd_ringbuffer *ring, int scratch_idx)
{
	static unsigned marker_cnt;
	unsigned reg = REG_A5XX_CP_SCRATCH_REG(scratch_idx);
	OUT_WFI5(ring);
	OUT_PKT4(ring, reg, 1);
	OUT_RING(ring, ++marker_cnt);
	OUT_WFI5(ring);
}

void
a5xx_cache_flush(struct fd_ringbuffer *ring)
{
	OUT_PKT4(ring, REG_A5XX_UCHE_CACHE_INVALIDATE_MIN_LO, 5);
	OUT_RING(ring, 0x00000000);   /* UCHE_CACHE_INVALIDATE_MIN_LO */
	OUT_RING(ring, 0x00000000);   /* UCHE_CACHE_INVALIDATE_MIN_HI */
	OUT_RING(ring, 0x00000000);   /* UCHE_CACHE_INVALIDATE_MAX_LO */
	OUT_RING(ring, 0x00000000);   /* UCHE_CACHE_INVALIDATE_MAX_HI */
	OUT_RING(ring, 0x00000012);   /* UCHE_CACHE_INVALIDATE */
	OUT_WFI5(ring);
}

void
a5xx_set_render_mode(struct fd_ringbuffer *ring,
		enum render_mode_cmd mode)
{
	/* TODO add preemption support, gmem bypass, etc */
	a5xx_emit_marker(ring, 7);
	OUT_PKT7(ring, CP_SET_RENDER_MODE, 5);
	OUT_RING(ring, CP_SET_RENDER_MODE_0_MODE(mode));
	OUT_RING(ring, 0x00000000);   /* ADDR_LO */
	OUT_RING(ring, 0x00000000);   /* ADDR_HI */
	OUT_RING(ring, COND(mode == GMEM, CP_SET_RENDER_MODE_3_GMEM_ENABLE));
	OUT_RING(ring, 0x00000000);
	a5xx_emit_marker(ring, 7);
}

/* emit setup at begin of new cmdstream buffer (don't rely on previous
 * state, there could have been a context switch between ioctls):
 */
void
a5xx_emit_restore(struct fd_ringbuffer *ring)
{
	a5xx_set_render_mode(ring, BYPASS);
	a5xx_cache_flush(ring);

	OUT_PKT4(ring, REG_A5XX_HLSQ_UPDATE_CNTL, 1);
	OUT_RING(ring, 0xfffff);

/*
t7              opcode: CP_PERFCOUNTER_ACTION (50) (4 dwords)
0000000500024048:               70d08003 00000000 001c5000 00000005
t7              opcode: CP_PERFCOUNTER_ACTION (50) (4 dwords)
0000000500024058:               70d08003 00000010 001c7000 00000005

t7              opcode: CP_WAIT_FOR_IDLE (26) (1 dwords)
0000000500024068:               70268000
*/

	OUT_PKT4(ring, REG_A5XX_PC_RESTART_INDEX, 1);
	OUT_RING(ring, 0xffffffff);

	OUT_PKT4(ring, REG_A5XX_PC_RASTER_CNTL, 1);
	OUT_RING(ring, 0x00000012);

	OUT_PKT4(ring, REG_A5XX_GRAS_LRZ_CNTL, 1);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_GRAS_SU_POINT_MINMAX, 2);
	OUT_RING(ring, A5XX_GRAS_SU_POINT_MINMAX_MIN(1.0) |
			A5XX_GRAS_SU_POINT_MINMAX_MAX(4092.0));
	OUT_RING(ring, A5XX_GRAS_SU_POINT_SIZE(0.5));

	OUT_PKT4(ring, REG_A5XX_GRAS_SU_CONSERVATIVE_RAS_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* GRAS_SU_CONSERVATIVE_RAS_CNTL */

	OUT_PKT4(ring, REG_A5XX_GRAS_SC_SCREEN_SCISSOR_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* GRAS_SC_SCREEN_SCISSOR_CNTL */

	OUT_PKT4(ring, REG_A5XX_SP_VS_CONFIG_MAX_CONST, 1);
	OUT_RING(ring, 0);            /* SP_VS_CONFIG_MAX_CONST */

	OUT_PKT4(ring, REG_A5XX_SP_FS_CONFIG_MAX_CONST, 1);
	OUT_RING(ring, 0);            /* SP_FS_CONFIG_MAX_CONST */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E292, 2);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E292 */
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E293 */

	OUT_PKT4(ring, REG_A5XX_RB_MODE_CNTL, 1);
	OUT_RING(ring, 0x00000044);   /* RB_MODE_CNTL */

	OUT_PKT4(ring, REG_A5XX_RB_DBG_ECO_CNTL, 1);
	OUT_RING(ring, 0x00100000);   /* RB_DBG_ECO_CNTL */

	OUT_PKT4(ring, REG_A5XX_VFD_MODE_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* VFD_MODE_CNTL */

	OUT_PKT4(ring, REG_A5XX_PC_MODE_CNTL, 1);
	OUT_RING(ring, 0x0000001f);   /* PC_MODE_CNTL */

	OUT_PKT4(ring, REG_A5XX_SP_MODE_CNTL, 1);
	OUT_RING(ring, 0x0000001e);   /* SP_MODE_CNTL */

	OUT_PKT4(ring, REG_A5XX_SP_DBG_ECO_CNTL, 1);
	OUT_RING(ring, 0x40000800);   /* SP_DBG_ECO_CNTL */

	OUT_PKT4(ring, REG_A5XX_TPL1_MODE_CNTL, 1);
	OUT_RING(ring, 0x00000544);   /* TPL1_MODE_CNTL */

	OUT_PKT4(ring, REG_A5XX_HLSQ_TIMEOUT_THRESHOLD_0, 2);
	OUT_RING(ring, 0x00000080);   /* HLSQ_TIMEOUT_THRESHOLD_0 */
	OUT_RING(ring, 0x00000000);   /* HLSQ_TIMEOUT_THRESHOLD_1 */

	OUT_PKT4(ring, REG_A5XX_VPC_DBG_ECO_CNTL, 1);
	OUT_RING(ring, 0x00000400);   /* VPC_DBG_ECO_CNTL */

	OUT_PKT4(ring, REG_A5XX_HLSQ_MODE_CNTL, 1);
	OUT_RING(ring, 0x00000001);   /* HLSQ_MODE_CNTL */

	OUT_PKT4(ring, REG_A5XX_VPC_MODE_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* VPC_MODE_CNTL */

	/* we don't use this yet.. probably best to disable.. */
	OUT_PKT7(ring, CP_SET_DRAW_STATE, 3);
	OUT_RING(ring, CP_SET_DRAW_STATE__0_COUNT(0) |
			CP_SET_DRAW_STATE__0_DISABLE_ALL_GROUPS |
			CP_SET_DRAW_STATE__0_GROUP_ID(0));
	OUT_RING(ring, CP_SET_DRAW_STATE__1_ADDR_LO(0));
	OUT_RING(ring, CP_SET_DRAW_STATE__2_ADDR_HI(0));

	/* other regs not used (yet?) and always seem to have same value: */
	OUT_PKT4(ring, REG_A5XX_GRAS_CL_CNTL, 1);
	OUT_RING(ring, 0x00000080);   /* GRAS_CL_CNTL */

	OUT_PKT4(ring, REG_A5XX_GRAS_SU_CONSERVATIVE_RAS_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* GRAS_SU_CONSERVATIVE_RAS_CNTL */

	OUT_PKT4(ring, REG_A5XX_GRAS_SC_BIN_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* GRAS_SC_BIN_CNTL */

	OUT_PKT4(ring, REG_A5XX_GRAS_SC_BIN_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* GRAS_SC_BIN_CNTL */

	OUT_PKT4(ring, REG_A5XX_VPC_FS_PRIMITIVEID_CNTL, 1);
	OUT_RING(ring, 0x000000ff);   /* VPC_FS_PRIMITIVEID_CNTL */

	OUT_PKT4(ring, REG_A5XX_VPC_SO_OVERRIDE, 1);
	OUT_RING(ring, 0x00000001);   /* VPC_SO_OVERRIDE */

	OUT_PKT4(ring, REG_A5XX_VPC_SO_BUFFER_BASE_LO_0, 3);
	OUT_RING(ring, 0x00000000);   /* VPC_SO_BUFFER_BASE_LO_0 */
	OUT_RING(ring, 0x00000000);   /* VPC_SO_BUFFER_BASE_HI_0 */
	OUT_RING(ring, 0x00000000);   /* VPC_SO_BUFFER_SIZE_0 */

	OUT_PKT4(ring, REG_A5XX_VPC_SO_FLUSH_BASE_LO_0, 2);
	OUT_RING(ring, 0x00000000);   /* VPC_SO_FLUSH_BASE_LO_0 */
	OUT_RING(ring, 0x00000000);   /* VPC_SO_FLUSH_BASE_HI_0 */

	OUT_PKT4(ring, REG_A5XX_PC_GS_PARAM, 1);
	OUT_RING(ring, 0x00000000);   /* PC_GS_PARAM */

	OUT_PKT4(ring, REG_A5XX_PC_HS_PARAM, 1);
	OUT_RING(ring, 0x00000000);   /* PC_HS_PARAM */

	OUT_PKT4(ring, REG_A5XX_TPL1_TP_FS_ROTATION_CNTL, 1);
	OUT_RING(ring, 0x00000000);   /* TPL1_TP_FS_ROTATION_CNTL */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E001, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E001 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E004, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E004 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E093, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E093 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E1C7, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E1C7 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E29A, 1);
	OUT_RING(ring, 0x00ffff00);   /* UNKNOWN_E29A */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E2A1, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E2A1 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E2AB, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E2AB */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E389, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E389 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E38D, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E38D */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E5AB, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E5AB */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E5C2, 1);
	OUT_RING(ring, 0x00000000);   /* UNKNOWN_E5C2 */

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E2AE, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E2B2, 6);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E2B9, 6);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E2C0, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E5DB, 1);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E600, 1);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E640, 1);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_TPL1_VS_TEX_COUNT, 4);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_TPL1_FS_TEX_COUNT, 2);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E7C0, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E7C5, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E7CA, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E7CF, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E7D4, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	OUT_PKT4(ring, REG_A5XX_UNKNOWN_E7D9, 3);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	// TODO hacks.. these should not be hardcoded:
	OUT_PKT4(ring, REG_A5XX_GRAS_SC_CNTL, 1);
	OUT_RING(ring, 0x00000008);   /* GRAS_SC_CNTL */
}
