/*
 * Copyright (c) 2012 Rob Clark <robdclark@gmail.com>
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
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Return float bits.
 */
static inline uint32_t fui(float f)
{
	union {
		float f;
		uint32_t ui;
	} fi;
	fi.f = f;
	return fi.ui;
}

union fi {
	float f;
	int32_t i;
	uint32_t ui;
};

static inline uint16_t
util_float_to_half(float f)
{
	uint32_t sign_mask  = 0x80000000;
	uint32_t round_mask = ~0xfff;
	uint32_t f32inf = 0xff << 23;
	uint32_t f16inf = 0x1f << 23;
	uint32_t sign;
	union fi magic;
	union fi f32;
	uint16_t f16;

	magic.ui = 0xf << 23;

	f32.f = f;

	/* Sign */
	sign = f32.ui & sign_mask;
	f32.ui ^= sign;

	if (f32.ui == f32inf) {
		/* Inf */
		f16 = 0x7c00;
	} else if (f32.ui > f32inf) {
		/* NaN */
		f16 = 0x7e00;
	} else {
		/* Number */
		f32.ui &= round_mask;
		f32.f  *= magic.f;
		f32.ui -= round_mask;
		/*
		 * XXX: The magic mul relies on denorms being available, otherwise
		 * all f16 denorms get flushed to zero - hence when this is used
		 * for tgsi_exec in softpipe we won't get f16 denorms.
		 */
		/*
		 * Clamp to max finite value if overflowed.
		 * OpenGL has completely undefined rounding behavior for float to
		 * half-float conversions, and this matches what is mandated for float
		 * to fp11/fp10, which recommend round-to-nearest-finite too.
		 * (d3d10 is deeply unhappy about flushing such values to infinity, and
		 * while it also mandates round-to-zero it doesn't care nearly as much
		 * about that.)
		 */
		if (f32.ui > f16inf)
			f32.ui = f16inf - 1;

		f16 = f32.ui >> 13;
	}

	/* Sign */
	f16 |= sign >> 16;

	return f16;
}

#include "adreno_common.xml.h"
#include "adreno_pm4.xml.h"

#define CP_REG(reg) ((0x4 << 16) | ((unsigned int)((reg) - (0x2000))))

/* for conditionally setting boolean flag(s): */
#define COND(bool, val) ((bool) ? (val) : 0)

static inline uint32_t DRAW(enum pc_di_primtype prim_type,
		enum pc_di_src_sel source_select, enum pc_di_index_size index_size,
		enum pc_di_vis_cull_mode vis_cull_mode)
{
	return (prim_type         << 0) |
			(source_select     << 6) |
			((index_size & 1)  << 11) |
			((index_size >> 1) << 13) |
			(vis_cull_mode     << 9) |
			(1                 << 14);
}

#define enable_debug 1  /* TODO make dynamic */

#define ALIGN(v,a) (((v) + (a) - 1) & ~((a) - 1))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define INFO_MSG(fmt, ...) \
		do { printf("[I] "fmt " (%s:%d)\n", \
				##__VA_ARGS__, __FUNCTION__, __LINE__); } while (0)
#define DEBUG_MSG(fmt, ...) \
		do if (enable_debug) { printf("[D] "fmt " (%s:%d)\n", \
				##__VA_ARGS__, __FUNCTION__, __LINE__); } while (0)
#define WARN_MSG(fmt, ...) \
		do { printf("[W] "fmt " (%s:%d)\n", \
				##__VA_ARGS__, __FUNCTION__, __LINE__); } while (0)
#define ERROR_MSG(fmt, ...) \
		do { printf("[E] " fmt " (%s:%d)\n", \
				##__VA_ARGS__, __FUNCTION__, __LINE__); } while (0)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))


#endif /* UTIL_H_ */
