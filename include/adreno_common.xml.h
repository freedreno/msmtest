#ifndef ADRENO_COMMON_XML
#define ADRENO_COMMON_XML

/* Autogenerated file, DO NOT EDIT manually!

This file was generated by the rules-ng-ng headergen tool in this git repository:
http://github.com/freedreno/envytools/
git clone https://github.com/freedreno/envytools.git

The rules-ng-ng source files this header was generated from are:
- /home/robclark/src/freedreno/envytools/rnndb/adreno.xml               (    431 bytes, from 2017-05-17 13:21:27)
- /home/robclark/src/freedreno/envytools/rnndb/freedreno_copyright.xml  (   1572 bytes, from 2017-05-17 13:21:27)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a2xx.xml          (  37162 bytes, from 2017-05-17 13:21:27)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/adreno_common.xml (  13324 bytes, from 2017-05-17 13:21:27)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/adreno_pm4.xml    (  31668 bytes, from 2017-05-30 16:52:40)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a3xx.xml          (  83840 bytes, from 2017-05-17 13:21:27)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a4xx.xml          ( 111898 bytes, from 2017-05-30 19:25:27)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/a5xx.xml          ( 136835 bytes, from 2017-05-30 20:06:17)
- /home/robclark/src/freedreno/envytools/rnndb/adreno/ocmem.xml         (   1773 bytes, from 2017-05-17 13:21:27)

Copyright (C) 2013-2017 by the following authors:
- Rob Clark <robdclark@gmail.com> (robclark)
- Ilia Mirkin <imirkin@alum.mit.edu> (imirkin)

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


enum adreno_pa_su_sc_draw {
	PC_DRAW_POINTS = 0,
	PC_DRAW_LINES = 1,
	PC_DRAW_TRIANGLES = 2,
};

enum adreno_compare_func {
	FUNC_NEVER = 0,
	FUNC_LESS = 1,
	FUNC_EQUAL = 2,
	FUNC_LEQUAL = 3,
	FUNC_GREATER = 4,
	FUNC_NOTEQUAL = 5,
	FUNC_GEQUAL = 6,
	FUNC_ALWAYS = 7,
};

enum adreno_stencil_op {
	STENCIL_KEEP = 0,
	STENCIL_ZERO = 1,
	STENCIL_REPLACE = 2,
	STENCIL_INCR_CLAMP = 3,
	STENCIL_DECR_CLAMP = 4,
	STENCIL_INVERT = 5,
	STENCIL_INCR_WRAP = 6,
	STENCIL_DECR_WRAP = 7,
};

enum adreno_rb_blend_factor {
	FACTOR_ZERO = 0,
	FACTOR_ONE = 1,
	FACTOR_SRC_COLOR = 4,
	FACTOR_ONE_MINUS_SRC_COLOR = 5,
	FACTOR_SRC_ALPHA = 6,
	FACTOR_ONE_MINUS_SRC_ALPHA = 7,
	FACTOR_DST_COLOR = 8,
	FACTOR_ONE_MINUS_DST_COLOR = 9,
	FACTOR_DST_ALPHA = 10,
	FACTOR_ONE_MINUS_DST_ALPHA = 11,
	FACTOR_CONSTANT_COLOR = 12,
	FACTOR_ONE_MINUS_CONSTANT_COLOR = 13,
	FACTOR_CONSTANT_ALPHA = 14,
	FACTOR_ONE_MINUS_CONSTANT_ALPHA = 15,
	FACTOR_SRC_ALPHA_SATURATE = 16,
	FACTOR_SRC1_COLOR = 20,
	FACTOR_ONE_MINUS_SRC1_COLOR = 21,
	FACTOR_SRC1_ALPHA = 22,
	FACTOR_ONE_MINUS_SRC1_ALPHA = 23,
};

enum adreno_rb_surface_endian {
	ENDIAN_NONE = 0,
	ENDIAN_8IN16 = 1,
	ENDIAN_8IN32 = 2,
	ENDIAN_16IN32 = 3,
	ENDIAN_8IN64 = 4,
	ENDIAN_8IN128 = 5,
};

enum adreno_rb_dither_mode {
	DITHER_DISABLE = 0,
	DITHER_ALWAYS = 1,
	DITHER_IF_ALPHA_OFF = 2,
};

enum adreno_rb_depth_format {
	DEPTHX_16 = 0,
	DEPTHX_24_8 = 1,
	DEPTHX_32 = 2,
};

enum adreno_rb_copy_control_mode {
	RB_COPY_RESOLVE = 1,
	RB_COPY_CLEAR = 2,
	RB_COPY_DEPTH_STENCIL = 5,
};

enum a3xx_rop_code {
	ROP_CLEAR = 0,
	ROP_NOR = 1,
	ROP_AND_INVERTED = 2,
	ROP_COPY_INVERTED = 3,
	ROP_AND_REVERSE = 4,
	ROP_INVERT = 5,
	ROP_XOR = 6,
	ROP_NAND = 7,
	ROP_AND = 8,
	ROP_EQUIV = 9,
	ROP_NOOP = 10,
	ROP_OR_INVERTED = 11,
	ROP_COPY = 12,
	ROP_OR_REVERSE = 13,
	ROP_OR = 14,
	ROP_SET = 15,
};

enum a3xx_render_mode {
	RB_RENDERING_PASS = 0,
	RB_TILING_PASS = 1,
	RB_RESOLVE_PASS = 2,
	RB_COMPUTE_PASS = 3,
};

enum a3xx_msaa_samples {
	MSAA_ONE = 0,
	MSAA_TWO = 1,
	MSAA_FOUR = 2,
};

enum a3xx_threadmode {
	MULTI = 0,
	SINGLE = 1,
};

enum a3xx_instrbuffermode {
	CACHE = 0,
	BUFFER = 1,
};

enum a3xx_threadsize {
	TWO_QUADS = 0,
	FOUR_QUADS = 1,
};

enum a3xx_color_swap {
	WZYX = 0,
	WXYZ = 1,
	ZYXW = 2,
	XYZW = 3,
};

enum a3xx_rb_blend_opcode {
	BLEND_DST_PLUS_SRC = 0,
	BLEND_SRC_MINUS_DST = 1,
	BLEND_DST_MINUS_SRC = 2,
	BLEND_MIN_DST_SRC = 3,
	BLEND_MAX_DST_SRC = 4,
};

#define REG_AXXX_CP_RB_BASE					0x000001c0

#define REG_AXXX_CP_RB_CNTL					0x000001c1
#define AXXX_CP_RB_CNTL_BUFSZ__MASK				0x0000003f
#define AXXX_CP_RB_CNTL_BUFSZ__SHIFT				0
static inline uint32_t AXXX_CP_RB_CNTL_BUFSZ(uint32_t val)
{
	return ((val) << AXXX_CP_RB_CNTL_BUFSZ__SHIFT) & AXXX_CP_RB_CNTL_BUFSZ__MASK;
}
#define AXXX_CP_RB_CNTL_BLKSZ__MASK				0x00003f00
#define AXXX_CP_RB_CNTL_BLKSZ__SHIFT				8
static inline uint32_t AXXX_CP_RB_CNTL_BLKSZ(uint32_t val)
{
	return ((val) << AXXX_CP_RB_CNTL_BLKSZ__SHIFT) & AXXX_CP_RB_CNTL_BLKSZ__MASK;
}
#define AXXX_CP_RB_CNTL_BUF_SWAP__MASK				0x00030000
#define AXXX_CP_RB_CNTL_BUF_SWAP__SHIFT				16
static inline uint32_t AXXX_CP_RB_CNTL_BUF_SWAP(uint32_t val)
{
	return ((val) << AXXX_CP_RB_CNTL_BUF_SWAP__SHIFT) & AXXX_CP_RB_CNTL_BUF_SWAP__MASK;
}
#define AXXX_CP_RB_CNTL_POLL_EN					0x00100000
#define AXXX_CP_RB_CNTL_NO_UPDATE				0x08000000
#define AXXX_CP_RB_CNTL_RPTR_WR_EN				0x80000000

#define REG_AXXX_CP_RB_RPTR_ADDR				0x000001c3
#define AXXX_CP_RB_RPTR_ADDR_SWAP__MASK				0x00000003
#define AXXX_CP_RB_RPTR_ADDR_SWAP__SHIFT			0
static inline uint32_t AXXX_CP_RB_RPTR_ADDR_SWAP(uint32_t val)
{
	return ((val) << AXXX_CP_RB_RPTR_ADDR_SWAP__SHIFT) & AXXX_CP_RB_RPTR_ADDR_SWAP__MASK;
}
#define AXXX_CP_RB_RPTR_ADDR_ADDR__MASK				0xfffffffc
#define AXXX_CP_RB_RPTR_ADDR_ADDR__SHIFT			2
static inline uint32_t AXXX_CP_RB_RPTR_ADDR_ADDR(uint32_t val)
{
	assert(!(val & 0x3));
	return ((val >> 2) << AXXX_CP_RB_RPTR_ADDR_ADDR__SHIFT) & AXXX_CP_RB_RPTR_ADDR_ADDR__MASK;
}

#define REG_AXXX_CP_RB_RPTR					0x000001c4

#define REG_AXXX_CP_RB_WPTR					0x000001c5

#define REG_AXXX_CP_RB_WPTR_DELAY				0x000001c6

#define REG_AXXX_CP_RB_RPTR_WR					0x000001c7

#define REG_AXXX_CP_RB_WPTR_BASE				0x000001c8

#define REG_AXXX_CP_QUEUE_THRESHOLDS				0x000001d5
#define AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB1_START__MASK		0x0000000f
#define AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB1_START__SHIFT		0
static inline uint32_t AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB1_START(uint32_t val)
{
	return ((val) << AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB1_START__SHIFT) & AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB1_START__MASK;
}
#define AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB2_START__MASK		0x00000f00
#define AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB2_START__SHIFT		8
static inline uint32_t AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB2_START(uint32_t val)
{
	return ((val) << AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB2_START__SHIFT) & AXXX_CP_QUEUE_THRESHOLDS_CSQ_IB2_START__MASK;
}
#define AXXX_CP_QUEUE_THRESHOLDS_CSQ_ST_START__MASK		0x000f0000
#define AXXX_CP_QUEUE_THRESHOLDS_CSQ_ST_START__SHIFT		16
static inline uint32_t AXXX_CP_QUEUE_THRESHOLDS_CSQ_ST_START(uint32_t val)
{
	return ((val) << AXXX_CP_QUEUE_THRESHOLDS_CSQ_ST_START__SHIFT) & AXXX_CP_QUEUE_THRESHOLDS_CSQ_ST_START__MASK;
}

#define REG_AXXX_CP_MEQ_THRESHOLDS				0x000001d6
#define AXXX_CP_MEQ_THRESHOLDS_MEQ_END__MASK			0x001f0000
#define AXXX_CP_MEQ_THRESHOLDS_MEQ_END__SHIFT			16
static inline uint32_t AXXX_CP_MEQ_THRESHOLDS_MEQ_END(uint32_t val)
{
	return ((val) << AXXX_CP_MEQ_THRESHOLDS_MEQ_END__SHIFT) & AXXX_CP_MEQ_THRESHOLDS_MEQ_END__MASK;
}
#define AXXX_CP_MEQ_THRESHOLDS_ROQ_END__MASK			0x1f000000
#define AXXX_CP_MEQ_THRESHOLDS_ROQ_END__SHIFT			24
static inline uint32_t AXXX_CP_MEQ_THRESHOLDS_ROQ_END(uint32_t val)
{
	return ((val) << AXXX_CP_MEQ_THRESHOLDS_ROQ_END__SHIFT) & AXXX_CP_MEQ_THRESHOLDS_ROQ_END__MASK;
}

#define REG_AXXX_CP_CSQ_AVAIL					0x000001d7
#define AXXX_CP_CSQ_AVAIL_RING__MASK				0x0000007f
#define AXXX_CP_CSQ_AVAIL_RING__SHIFT				0
static inline uint32_t AXXX_CP_CSQ_AVAIL_RING(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_AVAIL_RING__SHIFT) & AXXX_CP_CSQ_AVAIL_RING__MASK;
}
#define AXXX_CP_CSQ_AVAIL_IB1__MASK				0x00007f00
#define AXXX_CP_CSQ_AVAIL_IB1__SHIFT				8
static inline uint32_t AXXX_CP_CSQ_AVAIL_IB1(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_AVAIL_IB1__SHIFT) & AXXX_CP_CSQ_AVAIL_IB1__MASK;
}
#define AXXX_CP_CSQ_AVAIL_IB2__MASK				0x007f0000
#define AXXX_CP_CSQ_AVAIL_IB2__SHIFT				16
static inline uint32_t AXXX_CP_CSQ_AVAIL_IB2(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_AVAIL_IB2__SHIFT) & AXXX_CP_CSQ_AVAIL_IB2__MASK;
}

#define REG_AXXX_CP_STQ_AVAIL					0x000001d8
#define AXXX_CP_STQ_AVAIL_ST__MASK				0x0000007f
#define AXXX_CP_STQ_AVAIL_ST__SHIFT				0
static inline uint32_t AXXX_CP_STQ_AVAIL_ST(uint32_t val)
{
	return ((val) << AXXX_CP_STQ_AVAIL_ST__SHIFT) & AXXX_CP_STQ_AVAIL_ST__MASK;
}

#define REG_AXXX_CP_MEQ_AVAIL					0x000001d9
#define AXXX_CP_MEQ_AVAIL_MEQ__MASK				0x0000001f
#define AXXX_CP_MEQ_AVAIL_MEQ__SHIFT				0
static inline uint32_t AXXX_CP_MEQ_AVAIL_MEQ(uint32_t val)
{
	return ((val) << AXXX_CP_MEQ_AVAIL_MEQ__SHIFT) & AXXX_CP_MEQ_AVAIL_MEQ__MASK;
}

#define REG_AXXX_SCRATCH_UMSK					0x000001dc
#define AXXX_SCRATCH_UMSK_UMSK__MASK				0x000000ff
#define AXXX_SCRATCH_UMSK_UMSK__SHIFT				0
static inline uint32_t AXXX_SCRATCH_UMSK_UMSK(uint32_t val)
{
	return ((val) << AXXX_SCRATCH_UMSK_UMSK__SHIFT) & AXXX_SCRATCH_UMSK_UMSK__MASK;
}
#define AXXX_SCRATCH_UMSK_SWAP__MASK				0x00030000
#define AXXX_SCRATCH_UMSK_SWAP__SHIFT				16
static inline uint32_t AXXX_SCRATCH_UMSK_SWAP(uint32_t val)
{
	return ((val) << AXXX_SCRATCH_UMSK_SWAP__SHIFT) & AXXX_SCRATCH_UMSK_SWAP__MASK;
}

#define REG_AXXX_SCRATCH_ADDR					0x000001dd

#define REG_AXXX_CP_ME_RDADDR					0x000001ea

#define REG_AXXX_CP_STATE_DEBUG_INDEX				0x000001ec

#define REG_AXXX_CP_STATE_DEBUG_DATA				0x000001ed

#define REG_AXXX_CP_INT_CNTL					0x000001f2

#define REG_AXXX_CP_INT_STATUS					0x000001f3

#define REG_AXXX_CP_INT_ACK					0x000001f4

#define REG_AXXX_CP_ME_CNTL					0x000001f6
#define AXXX_CP_ME_CNTL_BUSY					0x20000000
#define AXXX_CP_ME_CNTL_HALT					0x10000000

#define REG_AXXX_CP_ME_STATUS					0x000001f7

#define REG_AXXX_CP_ME_RAM_WADDR				0x000001f8

#define REG_AXXX_CP_ME_RAM_RADDR				0x000001f9

#define REG_AXXX_CP_ME_RAM_DATA					0x000001fa

#define REG_AXXX_CP_DEBUG					0x000001fc
#define AXXX_CP_DEBUG_PREDICATE_DISABLE				0x00800000
#define AXXX_CP_DEBUG_PROG_END_PTR_ENABLE			0x01000000
#define AXXX_CP_DEBUG_MIU_128BIT_WRITE_ENABLE			0x02000000
#define AXXX_CP_DEBUG_PREFETCH_PASS_NOPS			0x04000000
#define AXXX_CP_DEBUG_DYNAMIC_CLK_DISABLE			0x08000000
#define AXXX_CP_DEBUG_PREFETCH_MATCH_DISABLE			0x10000000
#define AXXX_CP_DEBUG_SIMPLE_ME_FLOW_CONTROL			0x40000000
#define AXXX_CP_DEBUG_MIU_WRITE_PACK_DISABLE			0x80000000

#define REG_AXXX_CP_CSQ_RB_STAT					0x000001fd
#define AXXX_CP_CSQ_RB_STAT_RPTR__MASK				0x0000007f
#define AXXX_CP_CSQ_RB_STAT_RPTR__SHIFT				0
static inline uint32_t AXXX_CP_CSQ_RB_STAT_RPTR(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_RB_STAT_RPTR__SHIFT) & AXXX_CP_CSQ_RB_STAT_RPTR__MASK;
}
#define AXXX_CP_CSQ_RB_STAT_WPTR__MASK				0x007f0000
#define AXXX_CP_CSQ_RB_STAT_WPTR__SHIFT				16
static inline uint32_t AXXX_CP_CSQ_RB_STAT_WPTR(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_RB_STAT_WPTR__SHIFT) & AXXX_CP_CSQ_RB_STAT_WPTR__MASK;
}

#define REG_AXXX_CP_CSQ_IB1_STAT				0x000001fe
#define AXXX_CP_CSQ_IB1_STAT_RPTR__MASK				0x0000007f
#define AXXX_CP_CSQ_IB1_STAT_RPTR__SHIFT			0
static inline uint32_t AXXX_CP_CSQ_IB1_STAT_RPTR(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_IB1_STAT_RPTR__SHIFT) & AXXX_CP_CSQ_IB1_STAT_RPTR__MASK;
}
#define AXXX_CP_CSQ_IB1_STAT_WPTR__MASK				0x007f0000
#define AXXX_CP_CSQ_IB1_STAT_WPTR__SHIFT			16
static inline uint32_t AXXX_CP_CSQ_IB1_STAT_WPTR(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_IB1_STAT_WPTR__SHIFT) & AXXX_CP_CSQ_IB1_STAT_WPTR__MASK;
}

#define REG_AXXX_CP_CSQ_IB2_STAT				0x000001ff
#define AXXX_CP_CSQ_IB2_STAT_RPTR__MASK				0x0000007f
#define AXXX_CP_CSQ_IB2_STAT_RPTR__SHIFT			0
static inline uint32_t AXXX_CP_CSQ_IB2_STAT_RPTR(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_IB2_STAT_RPTR__SHIFT) & AXXX_CP_CSQ_IB2_STAT_RPTR__MASK;
}
#define AXXX_CP_CSQ_IB2_STAT_WPTR__MASK				0x007f0000
#define AXXX_CP_CSQ_IB2_STAT_WPTR__SHIFT			16
static inline uint32_t AXXX_CP_CSQ_IB2_STAT_WPTR(uint32_t val)
{
	return ((val) << AXXX_CP_CSQ_IB2_STAT_WPTR__SHIFT) & AXXX_CP_CSQ_IB2_STAT_WPTR__MASK;
}

#define REG_AXXX_CP_NON_PREFETCH_CNTRS				0x00000440

#define REG_AXXX_CP_STQ_ST_STAT					0x00000443

#define REG_AXXX_CP_ST_BASE					0x0000044d

#define REG_AXXX_CP_ST_BUFSZ					0x0000044e

#define REG_AXXX_CP_MEQ_STAT					0x0000044f

#define REG_AXXX_CP_MIU_TAG_STAT				0x00000452

#define REG_AXXX_CP_BIN_MASK_LO					0x00000454

#define REG_AXXX_CP_BIN_MASK_HI					0x00000455

#define REG_AXXX_CP_BIN_SELECT_LO				0x00000456

#define REG_AXXX_CP_BIN_SELECT_HI				0x00000457

#define REG_AXXX_CP_IB1_BASE					0x00000458

#define REG_AXXX_CP_IB1_BUFSZ					0x00000459

#define REG_AXXX_CP_IB2_BASE					0x0000045a

#define REG_AXXX_CP_IB2_BUFSZ					0x0000045b

#define REG_AXXX_CP_STAT					0x0000047f
#define AXXX_CP_STAT_CP_BUSY					0x80000000
#define AXXX_CP_STAT_VS_EVENT_FIFO_BUSY				0x40000000
#define AXXX_CP_STAT_PS_EVENT_FIFO_BUSY				0x20000000
#define AXXX_CP_STAT_CF_EVENT_FIFO_BUSY				0x10000000
#define AXXX_CP_STAT_RB_EVENT_FIFO_BUSY				0x08000000
#define AXXX_CP_STAT_ME_BUSY					0x04000000
#define AXXX_CP_STAT_MIU_WR_C_BUSY				0x02000000
#define AXXX_CP_STAT_CP_3D_BUSY					0x00800000
#define AXXX_CP_STAT_CP_NRT_BUSY				0x00400000
#define AXXX_CP_STAT_RBIU_SCRATCH_BUSY				0x00200000
#define AXXX_CP_STAT_RCIU_ME_BUSY				0x00100000
#define AXXX_CP_STAT_RCIU_PFP_BUSY				0x00080000
#define AXXX_CP_STAT_MEQ_RING_BUSY				0x00040000
#define AXXX_CP_STAT_PFP_BUSY					0x00020000
#define AXXX_CP_STAT_ST_QUEUE_BUSY				0x00010000
#define AXXX_CP_STAT_INDIRECT2_QUEUE_BUSY			0x00002000
#define AXXX_CP_STAT_INDIRECTS_QUEUE_BUSY			0x00001000
#define AXXX_CP_STAT_RING_QUEUE_BUSY				0x00000800
#define AXXX_CP_STAT_CSF_BUSY					0x00000400
#define AXXX_CP_STAT_CSF_ST_BUSY				0x00000200
#define AXXX_CP_STAT_EVENT_BUSY					0x00000100
#define AXXX_CP_STAT_CSF_INDIRECT2_BUSY				0x00000080
#define AXXX_CP_STAT_CSF_INDIRECTS_BUSY				0x00000040
#define AXXX_CP_STAT_CSF_RING_BUSY				0x00000020
#define AXXX_CP_STAT_RCIU_BUSY					0x00000010
#define AXXX_CP_STAT_RBIU_BUSY					0x00000008
#define AXXX_CP_STAT_MIU_RD_RETURN_BUSY				0x00000004
#define AXXX_CP_STAT_MIU_RD_REQ_BUSY				0x00000002
#define AXXX_CP_STAT_MIU_WR_BUSY				0x00000001

#define REG_AXXX_CP_SCRATCH_REG0				0x00000578

#define REG_AXXX_CP_SCRATCH_REG1				0x00000579

#define REG_AXXX_CP_SCRATCH_REG2				0x0000057a

#define REG_AXXX_CP_SCRATCH_REG3				0x0000057b

#define REG_AXXX_CP_SCRATCH_REG4				0x0000057c

#define REG_AXXX_CP_SCRATCH_REG5				0x0000057d

#define REG_AXXX_CP_SCRATCH_REG6				0x0000057e

#define REG_AXXX_CP_SCRATCH_REG7				0x0000057f

#define REG_AXXX_CP_ME_VS_EVENT_SRC				0x00000600

#define REG_AXXX_CP_ME_VS_EVENT_ADDR				0x00000601

#define REG_AXXX_CP_ME_VS_EVENT_DATA				0x00000602

#define REG_AXXX_CP_ME_VS_EVENT_ADDR_SWM			0x00000603

#define REG_AXXX_CP_ME_VS_EVENT_DATA_SWM			0x00000604

#define REG_AXXX_CP_ME_PS_EVENT_SRC				0x00000605

#define REG_AXXX_CP_ME_PS_EVENT_ADDR				0x00000606

#define REG_AXXX_CP_ME_PS_EVENT_DATA				0x00000607

#define REG_AXXX_CP_ME_PS_EVENT_ADDR_SWM			0x00000608

#define REG_AXXX_CP_ME_PS_EVENT_DATA_SWM			0x00000609

#define REG_AXXX_CP_ME_CF_EVENT_SRC				0x0000060a

#define REG_AXXX_CP_ME_CF_EVENT_ADDR				0x0000060b

#define REG_AXXX_CP_ME_CF_EVENT_DATA				0x0000060c

#define REG_AXXX_CP_ME_NRT_ADDR					0x0000060d

#define REG_AXXX_CP_ME_NRT_DATA					0x0000060e

#define REG_AXXX_CP_ME_VS_FETCH_DONE_SRC			0x00000612

#define REG_AXXX_CP_ME_VS_FETCH_DONE_ADDR			0x00000613

#define REG_AXXX_CP_ME_VS_FETCH_DONE_DATA			0x00000614


#endif /* ADRENO_COMMON_XML */
