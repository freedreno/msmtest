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

#ifndef A5XX_COMMON_H
#define A5XX_COMMON_H

#include "common.h"
#include "a5xx.xml.h"


enum a5xx_color_fmt bo_fmt(struct msm_bo *bo);
enum a3xx_color_swap bo_swap(struct msm_bo *bo);

void a5xx_emit_marker(struct fd_ringbuffer *ring, int scratch_idx);
void a5xx_cache_flush(struct fd_ringbuffer *ring);
void a5xx_set_render_mode(struct fd_ringbuffer *ring,
		enum render_mode_cmd mode);
void a5xx_emit_restore(struct fd_ringbuffer *ring);


static inline void
OUT_WFI5(struct fd_ringbuffer *ring)
{
	OUT_PKT7(ring, CP_WAIT_FOR_IDLE, 0);
}


#endif /*  A5XX_COMMON_H */
