#ifndef ADRENO_PM4_XML
#define ADRENO_PM4_XML

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


enum vgt_event_type {
	VS_DEALLOC = 0,
	PS_DEALLOC = 1,
	VS_DONE_TS = 2,
	PS_DONE_TS = 3,
	CACHE_FLUSH_TS = 4,
	CONTEXT_DONE = 5,
	CACHE_FLUSH = 6,
	HLSQ_FLUSH = 7,
	VIZQUERY_START = 7,
	VIZQUERY_END = 8,
	SC_WAIT_WC = 9,
	RST_PIX_CNT = 13,
	RST_VTX_CNT = 14,
	TILE_FLUSH = 15,
	STAT_EVENT = 16,
	CACHE_FLUSH_AND_INV_TS_EVENT = 20,
	ZPASS_DONE = 21,
	CACHE_FLUSH_AND_INV_EVENT = 22,
	PERFCOUNTER_START = 23,
	PERFCOUNTER_STOP = 24,
	VS_FETCH_DONE = 27,
	FACENESS_FLUSH = 28,
	FLUSH_SO_0 = 17,
	FLUSH_SO_1 = 18,
	FLUSH_SO_2 = 19,
	FLUSH_SO_3 = 20,
	UNK_19 = 25,
	UNK_1C = 28,
	UNK_1D = 29,
	BLIT = 30,
	UNK_25 = 37,
	UNK_26 = 38,
	UNK_2C = 44,
	UNK_2D = 45,
};

enum pc_di_primtype {
	DI_PT_NONE = 0,
	DI_PT_POINTLIST_PSIZE = 1,
	DI_PT_LINELIST = 2,
	DI_PT_LINESTRIP = 3,
	DI_PT_TRILIST = 4,
	DI_PT_TRIFAN = 5,
	DI_PT_TRISTRIP = 6,
	DI_PT_LINELOOP = 7,
	DI_PT_RECTLIST = 8,
	DI_PT_POINTLIST = 9,
	DI_PT_LINE_ADJ = 10,
	DI_PT_LINESTRIP_ADJ = 11,
	DI_PT_TRI_ADJ = 12,
	DI_PT_TRISTRIP_ADJ = 13,
};

enum pc_di_src_sel {
	DI_SRC_SEL_DMA = 0,
	DI_SRC_SEL_IMMEDIATE = 1,
	DI_SRC_SEL_AUTO_INDEX = 2,
	DI_SRC_SEL_RESERVED = 3,
};

enum pc_di_index_size {
	INDEX_SIZE_IGN = 0,
	INDEX_SIZE_16_BIT = 0,
	INDEX_SIZE_32_BIT = 1,
	INDEX_SIZE_8_BIT = 2,
	INDEX_SIZE_INVALID = 0,
};

enum pc_di_vis_cull_mode {
	IGNORE_VISIBILITY = 0,
	USE_VISIBILITY = 1,
};

enum adreno_pm4_packet_type {
	CP_TYPE0_PKT = 0,
	CP_TYPE1_PKT = 0x40000000,
	CP_TYPE2_PKT = 0x80000000,
	CP_TYPE3_PKT = 0xc0000000,
	CP_TYPE4_PKT = 0x40000000,
	CP_TYPE7_PKT = 0x70000000,
};

enum adreno_pm4_type3_packets {
	CP_ME_INIT = 72,
	CP_NOP = 16,
	CP_PREEMPT_ENABLE = 28,
	CP_PREEMPT_TOKEN = 30,
	CP_INDIRECT_BUFFER = 63,
	CP_INDIRECT_BUFFER_PFD = 55,
	CP_WAIT_FOR_IDLE = 38,
	CP_WAIT_REG_MEM = 60,
	CP_WAIT_REG_EQ = 82,
	CP_WAIT_REG_GTE = 83,
	CP_WAIT_UNTIL_READ = 92,
	CP_WAIT_IB_PFD_COMPLETE = 93,
	CP_REG_RMW = 33,
	CP_SET_BIN_DATA = 47,
	CP_SET_BIN_DATA5 = 47,
	CP_REG_TO_MEM = 62,
	CP_MEM_WRITE = 61,
	CP_MEM_WRITE_CNTR = 79,
	CP_COND_EXEC = 68,
	CP_COND_WRITE = 69,
	CP_COND_WRITE5 = 69,
	CP_EVENT_WRITE = 70,
	CP_EVENT_WRITE_SHD = 88,
	CP_EVENT_WRITE_CFL = 89,
	CP_EVENT_WRITE_ZPD = 91,
	CP_RUN_OPENCL = 49,
	CP_DRAW_INDX = 34,
	CP_DRAW_INDX_2 = 54,
	CP_DRAW_INDX_BIN = 52,
	CP_DRAW_INDX_2_BIN = 53,
	CP_VIZ_QUERY = 35,
	CP_SET_STATE = 37,
	CP_SET_CONSTANT = 45,
	CP_IM_LOAD = 39,
	CP_IM_LOAD_IMMEDIATE = 43,
	CP_LOAD_CONSTANT_CONTEXT = 46,
	CP_INVALIDATE_STATE = 59,
	CP_SET_SHADER_BASES = 74,
	CP_SET_BIN_MASK = 80,
	CP_SET_BIN_SELECT = 81,
	CP_CONTEXT_UPDATE = 94,
	CP_INTERRUPT = 64,
	CP_IM_STORE = 44,
	CP_SET_DRAW_INIT_FLAGS = 75,
	CP_SET_PROTECTED_MODE = 95,
	CP_BOOTSTRAP_UCODE = 111,
	CP_LOAD_STATE = 48,
	CP_LOAD_STATE4 = 48,
	CP_COND_INDIRECT_BUFFER_PFE = 58,
	CP_COND_INDIRECT_BUFFER_PFD = 50,
	CP_INDIRECT_BUFFER_PFE = 63,
	CP_SET_BIN = 76,
	CP_TEST_TWO_MEMS = 113,
	CP_REG_WR_NO_CTXT = 120,
	CP_RECORD_PFP_TIMESTAMP = 17,
	CP_SET_SECURE_MODE = 102,
	CP_WAIT_FOR_ME = 19,
	CP_SET_DRAW_STATE = 67,
	CP_DRAW_INDX_OFFSET = 56,
	CP_DRAW_INDIRECT = 40,
	CP_DRAW_INDX_INDIRECT = 41,
	CP_DRAW_AUTO = 36,
	CP_UNKNOWN_19 = 25,
	CP_UNKNOWN_1A = 26,
	CP_UNKNOWN_4E = 78,
	CP_WIDE_REG_WRITE = 116,
	CP_SCRATCH_TO_REG = 77,
	CP_REG_TO_SCRATCH = 74,
	CP_WAIT_MEM_WRITES = 18,
	CP_COND_REG_EXEC = 71,
	CP_MEM_TO_REG = 66,
	CP_EXEC_CS = 51,
	CP_PERFCOUNTER_ACTION = 80,
	CP_SMMU_TABLE_UPDATE = 83,
	CP_CONTEXT_REG_BUNCH = 92,
	CP_YIELD_ENABLE = 28,
	CP_SKIP_IB2_ENABLE_GLOBAL = 29,
	CP_SKIP_IB2_ENABLE_LOCAL = 35,
	CP_SET_SUBDRAW_SIZE = 53,
	CP_SET_VISIBILITY_OVERRIDE = 100,
	CP_PREEMPT_ENABLE_GLOBAL = 105,
	CP_PREEMPT_ENABLE_LOCAL = 106,
	CP_CONTEXT_SWITCH_YIELD = 107,
	CP_SET_RENDER_MODE = 108,
	CP_COMPUTE_CHECKPOINT = 110,
	CP_MEM_TO_MEM = 115,
	CP_BLIT = 44,
	CP_UNK_39 = 57,
	IN_IB_PREFETCH_END = 23,
	IN_SUBBLK_PREFETCH = 31,
	IN_INSTR_PREFETCH = 32,
	IN_INSTR_MATCH = 71,
	IN_CONST_PREFETCH = 73,
	IN_INCR_UPDT_STATE = 85,
	IN_INCR_UPDT_CONST = 86,
	IN_INCR_UPDT_INSTR = 87,
};

enum adreno_state_block {
	SB_VERT_TEX = 0,
	SB_VERT_MIPADDR = 1,
	SB_FRAG_TEX = 2,
	SB_FRAG_MIPADDR = 3,
	SB_VERT_SHADER = 4,
	SB_GEOM_SHADER = 5,
	SB_FRAG_SHADER = 6,
	SB_COMPUTE_SHADER = 7,
};

enum adreno_state_type {
	ST_SHADER = 0,
	ST_CONSTANTS = 1,
};

enum adreno_state_src {
	SS_DIRECT = 0,
	SS_INVALID_ALL_IC = 2,
	SS_INVALID_PART_IC = 3,
	SS_INDIRECT = 4,
	SS_INDIRECT_TCM = 5,
	SS_INDIRECT_STM = 6,
};

enum a4xx_state_block {
	SB4_VS_TEX = 0,
	SB4_HS_TEX = 1,
	SB4_DS_TEX = 2,
	SB4_GS_TEX = 3,
	SB4_FS_TEX = 4,
	SB4_CS_TEX = 5,
	SB4_VS_SHADER = 8,
	SB4_HS_SHADER = 9,
	SB4_DS_SHADER = 10,
	SB4_GS_SHADER = 11,
	SB4_FS_SHADER = 12,
	SB4_CS_SHADER = 13,
	SB4_SSBO = 14,
	SB4_CS_SSBO = 15,
};

enum a4xx_state_type {
	ST4_SHADER = 0,
	ST4_CONSTANTS = 1,
};

enum a4xx_state_src {
	SS4_DIRECT = 0,
	SS4_INDIRECT = 2,
};

enum a4xx_index_size {
	INDEX4_SIZE_8_BIT = 0,
	INDEX4_SIZE_16_BIT = 1,
	INDEX4_SIZE_32_BIT = 2,
};

enum cp_cond_function {
	WRITE_ALWAYS = 0,
	WRITE_LT = 1,
	WRITE_LE = 2,
	WRITE_EQ = 3,
	WRITE_NE = 4,
	WRITE_GE = 5,
	WRITE_GT = 6,
};

enum render_mode_cmd {
	BYPASS = 1,
	BINNING = 2,
	GMEM = 3,
	BLIT2D = 5,
};

enum cp_blit_cmd {
	BLIT_OP_FILL = 0,
	BLIT_OP_COPY = 1,
};

#define REG_CP_LOAD_STATE_0					0x00000000
#define CP_LOAD_STATE_0_DST_OFF__MASK				0x0000ffff
#define CP_LOAD_STATE_0_DST_OFF__SHIFT				0
static inline uint32_t CP_LOAD_STATE_0_DST_OFF(uint32_t val)
{
	return ((val) << CP_LOAD_STATE_0_DST_OFF__SHIFT) & CP_LOAD_STATE_0_DST_OFF__MASK;
}
#define CP_LOAD_STATE_0_STATE_SRC__MASK				0x00070000
#define CP_LOAD_STATE_0_STATE_SRC__SHIFT			16
static inline uint32_t CP_LOAD_STATE_0_STATE_SRC(enum adreno_state_src val)
{
	return ((val) << CP_LOAD_STATE_0_STATE_SRC__SHIFT) & CP_LOAD_STATE_0_STATE_SRC__MASK;
}
#define CP_LOAD_STATE_0_STATE_BLOCK__MASK			0x00380000
#define CP_LOAD_STATE_0_STATE_BLOCK__SHIFT			19
static inline uint32_t CP_LOAD_STATE_0_STATE_BLOCK(enum adreno_state_block val)
{
	return ((val) << CP_LOAD_STATE_0_STATE_BLOCK__SHIFT) & CP_LOAD_STATE_0_STATE_BLOCK__MASK;
}
#define CP_LOAD_STATE_0_NUM_UNIT__MASK				0xffc00000
#define CP_LOAD_STATE_0_NUM_UNIT__SHIFT				22
static inline uint32_t CP_LOAD_STATE_0_NUM_UNIT(uint32_t val)
{
	return ((val) << CP_LOAD_STATE_0_NUM_UNIT__SHIFT) & CP_LOAD_STATE_0_NUM_UNIT__MASK;
}

#define REG_CP_LOAD_STATE_1					0x00000001
#define CP_LOAD_STATE_1_STATE_TYPE__MASK			0x00000003
#define CP_LOAD_STATE_1_STATE_TYPE__SHIFT			0
static inline uint32_t CP_LOAD_STATE_1_STATE_TYPE(enum adreno_state_type val)
{
	return ((val) << CP_LOAD_STATE_1_STATE_TYPE__SHIFT) & CP_LOAD_STATE_1_STATE_TYPE__MASK;
}
#define CP_LOAD_STATE_1_EXT_SRC_ADDR__MASK			0xfffffffc
#define CP_LOAD_STATE_1_EXT_SRC_ADDR__SHIFT			2
static inline uint32_t CP_LOAD_STATE_1_EXT_SRC_ADDR(uint32_t val)
{
	assert(!(val & 0x3));
	return ((val >> 2) << CP_LOAD_STATE_1_EXT_SRC_ADDR__SHIFT) & CP_LOAD_STATE_1_EXT_SRC_ADDR__MASK;
}

#define REG_CP_LOAD_STATE4_0					0x00000000
#define CP_LOAD_STATE4_0_DST_OFF__MASK				0x0000ffff
#define CP_LOAD_STATE4_0_DST_OFF__SHIFT				0
static inline uint32_t CP_LOAD_STATE4_0_DST_OFF(uint32_t val)
{
	return ((val) << CP_LOAD_STATE4_0_DST_OFF__SHIFT) & CP_LOAD_STATE4_0_DST_OFF__MASK;
}
#define CP_LOAD_STATE4_0_STATE_SRC__MASK			0x00030000
#define CP_LOAD_STATE4_0_STATE_SRC__SHIFT			16
static inline uint32_t CP_LOAD_STATE4_0_STATE_SRC(enum a4xx_state_src val)
{
	return ((val) << CP_LOAD_STATE4_0_STATE_SRC__SHIFT) & CP_LOAD_STATE4_0_STATE_SRC__MASK;
}
#define CP_LOAD_STATE4_0_STATE_BLOCK__MASK			0x003c0000
#define CP_LOAD_STATE4_0_STATE_BLOCK__SHIFT			18
static inline uint32_t CP_LOAD_STATE4_0_STATE_BLOCK(enum a4xx_state_block val)
{
	return ((val) << CP_LOAD_STATE4_0_STATE_BLOCK__SHIFT) & CP_LOAD_STATE4_0_STATE_BLOCK__MASK;
}
#define CP_LOAD_STATE4_0_NUM_UNIT__MASK				0xffc00000
#define CP_LOAD_STATE4_0_NUM_UNIT__SHIFT			22
static inline uint32_t CP_LOAD_STATE4_0_NUM_UNIT(uint32_t val)
{
	return ((val) << CP_LOAD_STATE4_0_NUM_UNIT__SHIFT) & CP_LOAD_STATE4_0_NUM_UNIT__MASK;
}

#define REG_CP_LOAD_STATE4_1					0x00000001
#define CP_LOAD_STATE4_1_STATE_TYPE__MASK			0x00000003
#define CP_LOAD_STATE4_1_STATE_TYPE__SHIFT			0
static inline uint32_t CP_LOAD_STATE4_1_STATE_TYPE(enum a4xx_state_type val)
{
	return ((val) << CP_LOAD_STATE4_1_STATE_TYPE__SHIFT) & CP_LOAD_STATE4_1_STATE_TYPE__MASK;
}
#define CP_LOAD_STATE4_1_EXT_SRC_ADDR__MASK			0xfffffffc
#define CP_LOAD_STATE4_1_EXT_SRC_ADDR__SHIFT			2
static inline uint32_t CP_LOAD_STATE4_1_EXT_SRC_ADDR(uint32_t val)
{
	assert(!(val & 0x3));
	return ((val >> 2) << CP_LOAD_STATE4_1_EXT_SRC_ADDR__SHIFT) & CP_LOAD_STATE4_1_EXT_SRC_ADDR__MASK;
}

#define REG_CP_LOAD_STATE4_2					0x00000002
#define CP_LOAD_STATE4_2_EXT_SRC_ADDR_HI__MASK			0xffffffff
#define CP_LOAD_STATE4_2_EXT_SRC_ADDR_HI__SHIFT			0
static inline uint32_t CP_LOAD_STATE4_2_EXT_SRC_ADDR_HI(uint32_t val)
{
	return ((val) << CP_LOAD_STATE4_2_EXT_SRC_ADDR_HI__SHIFT) & CP_LOAD_STATE4_2_EXT_SRC_ADDR_HI__MASK;
}

#define REG_CP_DRAW_INDX_0					0x00000000
#define CP_DRAW_INDX_0_VIZ_QUERY__MASK				0xffffffff
#define CP_DRAW_INDX_0_VIZ_QUERY__SHIFT				0
static inline uint32_t CP_DRAW_INDX_0_VIZ_QUERY(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_0_VIZ_QUERY__SHIFT) & CP_DRAW_INDX_0_VIZ_QUERY__MASK;
}

#define REG_CP_DRAW_INDX_1					0x00000001
#define CP_DRAW_INDX_1_PRIM_TYPE__MASK				0x0000003f
#define CP_DRAW_INDX_1_PRIM_TYPE__SHIFT				0
static inline uint32_t CP_DRAW_INDX_1_PRIM_TYPE(enum pc_di_primtype val)
{
	return ((val) << CP_DRAW_INDX_1_PRIM_TYPE__SHIFT) & CP_DRAW_INDX_1_PRIM_TYPE__MASK;
}
#define CP_DRAW_INDX_1_SOURCE_SELECT__MASK			0x000000c0
#define CP_DRAW_INDX_1_SOURCE_SELECT__SHIFT			6
static inline uint32_t CP_DRAW_INDX_1_SOURCE_SELECT(enum pc_di_src_sel val)
{
	return ((val) << CP_DRAW_INDX_1_SOURCE_SELECT__SHIFT) & CP_DRAW_INDX_1_SOURCE_SELECT__MASK;
}
#define CP_DRAW_INDX_1_VIS_CULL__MASK				0x00000600
#define CP_DRAW_INDX_1_VIS_CULL__SHIFT				9
static inline uint32_t CP_DRAW_INDX_1_VIS_CULL(enum pc_di_vis_cull_mode val)
{
	return ((val) << CP_DRAW_INDX_1_VIS_CULL__SHIFT) & CP_DRAW_INDX_1_VIS_CULL__MASK;
}
#define CP_DRAW_INDX_1_INDEX_SIZE__MASK				0x00000800
#define CP_DRAW_INDX_1_INDEX_SIZE__SHIFT			11
static inline uint32_t CP_DRAW_INDX_1_INDEX_SIZE(enum pc_di_index_size val)
{
	return ((val) << CP_DRAW_INDX_1_INDEX_SIZE__SHIFT) & CP_DRAW_INDX_1_INDEX_SIZE__MASK;
}
#define CP_DRAW_INDX_1_NOT_EOP					0x00001000
#define CP_DRAW_INDX_1_SMALL_INDEX				0x00002000
#define CP_DRAW_INDX_1_PRE_DRAW_INITIATOR_ENABLE		0x00004000
#define CP_DRAW_INDX_1_NUM_INSTANCES__MASK			0xff000000
#define CP_DRAW_INDX_1_NUM_INSTANCES__SHIFT			24
static inline uint32_t CP_DRAW_INDX_1_NUM_INSTANCES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_1_NUM_INSTANCES__SHIFT) & CP_DRAW_INDX_1_NUM_INSTANCES__MASK;
}

#define REG_CP_DRAW_INDX_2					0x00000002
#define CP_DRAW_INDX_2_NUM_INDICES__MASK			0xffffffff
#define CP_DRAW_INDX_2_NUM_INDICES__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_NUM_INDICES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_NUM_INDICES__SHIFT) & CP_DRAW_INDX_2_NUM_INDICES__MASK;
}

#define REG_CP_DRAW_INDX_3					0x00000003
#define CP_DRAW_INDX_3_INDX_BASE__MASK				0xffffffff
#define CP_DRAW_INDX_3_INDX_BASE__SHIFT				0
static inline uint32_t CP_DRAW_INDX_3_INDX_BASE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_3_INDX_BASE__SHIFT) & CP_DRAW_INDX_3_INDX_BASE__MASK;
}

#define REG_CP_DRAW_INDX_4					0x00000004
#define CP_DRAW_INDX_4_INDX_SIZE__MASK				0xffffffff
#define CP_DRAW_INDX_4_INDX_SIZE__SHIFT				0
static inline uint32_t CP_DRAW_INDX_4_INDX_SIZE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_4_INDX_SIZE__SHIFT) & CP_DRAW_INDX_4_INDX_SIZE__MASK;
}

#define REG_CP_DRAW_INDX_2_0					0x00000000
#define CP_DRAW_INDX_2_0_VIZ_QUERY__MASK			0xffffffff
#define CP_DRAW_INDX_2_0_VIZ_QUERY__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_0_VIZ_QUERY(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_0_VIZ_QUERY__SHIFT) & CP_DRAW_INDX_2_0_VIZ_QUERY__MASK;
}

#define REG_CP_DRAW_INDX_2_1					0x00000001
#define CP_DRAW_INDX_2_1_PRIM_TYPE__MASK			0x0000003f
#define CP_DRAW_INDX_2_1_PRIM_TYPE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_1_PRIM_TYPE(enum pc_di_primtype val)
{
	return ((val) << CP_DRAW_INDX_2_1_PRIM_TYPE__SHIFT) & CP_DRAW_INDX_2_1_PRIM_TYPE__MASK;
}
#define CP_DRAW_INDX_2_1_SOURCE_SELECT__MASK			0x000000c0
#define CP_DRAW_INDX_2_1_SOURCE_SELECT__SHIFT			6
static inline uint32_t CP_DRAW_INDX_2_1_SOURCE_SELECT(enum pc_di_src_sel val)
{
	return ((val) << CP_DRAW_INDX_2_1_SOURCE_SELECT__SHIFT) & CP_DRAW_INDX_2_1_SOURCE_SELECT__MASK;
}
#define CP_DRAW_INDX_2_1_VIS_CULL__MASK				0x00000600
#define CP_DRAW_INDX_2_1_VIS_CULL__SHIFT			9
static inline uint32_t CP_DRAW_INDX_2_1_VIS_CULL(enum pc_di_vis_cull_mode val)
{
	return ((val) << CP_DRAW_INDX_2_1_VIS_CULL__SHIFT) & CP_DRAW_INDX_2_1_VIS_CULL__MASK;
}
#define CP_DRAW_INDX_2_1_INDEX_SIZE__MASK			0x00000800
#define CP_DRAW_INDX_2_1_INDEX_SIZE__SHIFT			11
static inline uint32_t CP_DRAW_INDX_2_1_INDEX_SIZE(enum pc_di_index_size val)
{
	return ((val) << CP_DRAW_INDX_2_1_INDEX_SIZE__SHIFT) & CP_DRAW_INDX_2_1_INDEX_SIZE__MASK;
}
#define CP_DRAW_INDX_2_1_NOT_EOP				0x00001000
#define CP_DRAW_INDX_2_1_SMALL_INDEX				0x00002000
#define CP_DRAW_INDX_2_1_PRE_DRAW_INITIATOR_ENABLE		0x00004000
#define CP_DRAW_INDX_2_1_NUM_INSTANCES__MASK			0xff000000
#define CP_DRAW_INDX_2_1_NUM_INSTANCES__SHIFT			24
static inline uint32_t CP_DRAW_INDX_2_1_NUM_INSTANCES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_1_NUM_INSTANCES__SHIFT) & CP_DRAW_INDX_2_1_NUM_INSTANCES__MASK;
}

#define REG_CP_DRAW_INDX_2_2					0x00000002
#define CP_DRAW_INDX_2_2_NUM_INDICES__MASK			0xffffffff
#define CP_DRAW_INDX_2_2_NUM_INDICES__SHIFT			0
static inline uint32_t CP_DRAW_INDX_2_2_NUM_INDICES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_2_2_NUM_INDICES__SHIFT) & CP_DRAW_INDX_2_2_NUM_INDICES__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_0				0x00000000
#define CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__MASK			0x0000003f
#define CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_OFFSET_0_PRIM_TYPE(enum pc_di_primtype val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__SHIFT) & CP_DRAW_INDX_OFFSET_0_PRIM_TYPE__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__MASK		0x000000c0
#define CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__SHIFT		6
static inline uint32_t CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT(enum pc_di_src_sel val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__SHIFT) & CP_DRAW_INDX_OFFSET_0_SOURCE_SELECT__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_VIS_CULL__MASK			0x00000300
#define CP_DRAW_INDX_OFFSET_0_VIS_CULL__SHIFT			8
static inline uint32_t CP_DRAW_INDX_OFFSET_0_VIS_CULL(enum pc_di_vis_cull_mode val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_VIS_CULL__SHIFT) & CP_DRAW_INDX_OFFSET_0_VIS_CULL__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__MASK			0x00000c00
#define CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__SHIFT			10
static inline uint32_t CP_DRAW_INDX_OFFSET_0_INDEX_SIZE(enum a4xx_index_size val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__SHIFT) & CP_DRAW_INDX_OFFSET_0_INDEX_SIZE__MASK;
}
#define CP_DRAW_INDX_OFFSET_0_TESS_MODE__MASK			0x01f00000
#define CP_DRAW_INDX_OFFSET_0_TESS_MODE__SHIFT			20
static inline uint32_t CP_DRAW_INDX_OFFSET_0_TESS_MODE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_0_TESS_MODE__SHIFT) & CP_DRAW_INDX_OFFSET_0_TESS_MODE__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_1				0x00000001
#define CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__MASK		0xffffffff
#define CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__SHIFT		0
static inline uint32_t CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__SHIFT) & CP_DRAW_INDX_OFFSET_1_NUM_INSTANCES__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_2				0x00000002
#define CP_DRAW_INDX_OFFSET_2_NUM_INDICES__MASK			0xffffffff
#define CP_DRAW_INDX_OFFSET_2_NUM_INDICES__SHIFT		0
static inline uint32_t CP_DRAW_INDX_OFFSET_2_NUM_INDICES(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_2_NUM_INDICES__SHIFT) & CP_DRAW_INDX_OFFSET_2_NUM_INDICES__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_3				0x00000003

#define REG_CP_DRAW_INDX_OFFSET_4				0x00000004
#define CP_DRAW_INDX_OFFSET_4_INDX_BASE__MASK			0xffffffff
#define CP_DRAW_INDX_OFFSET_4_INDX_BASE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_OFFSET_4_INDX_BASE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_4_INDX_BASE__SHIFT) & CP_DRAW_INDX_OFFSET_4_INDX_BASE__MASK;
}

#define REG_CP_DRAW_INDX_OFFSET_5				0x00000005
#define CP_DRAW_INDX_OFFSET_5_INDX_SIZE__MASK			0xffffffff
#define CP_DRAW_INDX_OFFSET_5_INDX_SIZE__SHIFT			0
static inline uint32_t CP_DRAW_INDX_OFFSET_5_INDX_SIZE(uint32_t val)
{
	return ((val) << CP_DRAW_INDX_OFFSET_5_INDX_SIZE__SHIFT) & CP_DRAW_INDX_OFFSET_5_INDX_SIZE__MASK;
}

static inline uint32_t REG_CP_SET_DRAW_STATE_(uint32_t i0) { return 0x00000000 + 0x3*i0; }

static inline uint32_t REG_CP_SET_DRAW_STATE__0(uint32_t i0) { return 0x00000000 + 0x3*i0; }
#define CP_SET_DRAW_STATE__0_COUNT__MASK			0x0000ffff
#define CP_SET_DRAW_STATE__0_COUNT__SHIFT			0
static inline uint32_t CP_SET_DRAW_STATE__0_COUNT(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE__0_COUNT__SHIFT) & CP_SET_DRAW_STATE__0_COUNT__MASK;
}
#define CP_SET_DRAW_STATE__0_DIRTY				0x00010000
#define CP_SET_DRAW_STATE__0_DISABLE				0x00020000
#define CP_SET_DRAW_STATE__0_DISABLE_ALL_GROUPS			0x00040000
#define CP_SET_DRAW_STATE__0_LOAD_IMMED				0x00080000
#define CP_SET_DRAW_STATE__0_GROUP_ID__MASK			0x1f000000
#define CP_SET_DRAW_STATE__0_GROUP_ID__SHIFT			24
static inline uint32_t CP_SET_DRAW_STATE__0_GROUP_ID(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE__0_GROUP_ID__SHIFT) & CP_SET_DRAW_STATE__0_GROUP_ID__MASK;
}

static inline uint32_t REG_CP_SET_DRAW_STATE__1(uint32_t i0) { return 0x00000001 + 0x3*i0; }
#define CP_SET_DRAW_STATE__1_ADDR_LO__MASK			0xffffffff
#define CP_SET_DRAW_STATE__1_ADDR_LO__SHIFT			0
static inline uint32_t CP_SET_DRAW_STATE__1_ADDR_LO(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE__1_ADDR_LO__SHIFT) & CP_SET_DRAW_STATE__1_ADDR_LO__MASK;
}

static inline uint32_t REG_CP_SET_DRAW_STATE__2(uint32_t i0) { return 0x00000002 + 0x3*i0; }
#define CP_SET_DRAW_STATE__2_ADDR_HI__MASK			0xffffffff
#define CP_SET_DRAW_STATE__2_ADDR_HI__SHIFT			0
static inline uint32_t CP_SET_DRAW_STATE__2_ADDR_HI(uint32_t val)
{
	return ((val) << CP_SET_DRAW_STATE__2_ADDR_HI__SHIFT) & CP_SET_DRAW_STATE__2_ADDR_HI__MASK;
}

#define REG_CP_SET_BIN_0					0x00000000

#define REG_CP_SET_BIN_1					0x00000001
#define CP_SET_BIN_1_X1__MASK					0x0000ffff
#define CP_SET_BIN_1_X1__SHIFT					0
static inline uint32_t CP_SET_BIN_1_X1(uint32_t val)
{
	return ((val) << CP_SET_BIN_1_X1__SHIFT) & CP_SET_BIN_1_X1__MASK;
}
#define CP_SET_BIN_1_Y1__MASK					0xffff0000
#define CP_SET_BIN_1_Y1__SHIFT					16
static inline uint32_t CP_SET_BIN_1_Y1(uint32_t val)
{
	return ((val) << CP_SET_BIN_1_Y1__SHIFT) & CP_SET_BIN_1_Y1__MASK;
}

#define REG_CP_SET_BIN_2					0x00000002
#define CP_SET_BIN_2_X2__MASK					0x0000ffff
#define CP_SET_BIN_2_X2__SHIFT					0
static inline uint32_t CP_SET_BIN_2_X2(uint32_t val)
{
	return ((val) << CP_SET_BIN_2_X2__SHIFT) & CP_SET_BIN_2_X2__MASK;
}
#define CP_SET_BIN_2_Y2__MASK					0xffff0000
#define CP_SET_BIN_2_Y2__SHIFT					16
static inline uint32_t CP_SET_BIN_2_Y2(uint32_t val)
{
	return ((val) << CP_SET_BIN_2_Y2__SHIFT) & CP_SET_BIN_2_Y2__MASK;
}

#define REG_CP_SET_BIN_DATA_0					0x00000000
#define CP_SET_BIN_DATA_0_BIN_DATA_ADDR__MASK			0xffffffff
#define CP_SET_BIN_DATA_0_BIN_DATA_ADDR__SHIFT			0
static inline uint32_t CP_SET_BIN_DATA_0_BIN_DATA_ADDR(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA_0_BIN_DATA_ADDR__SHIFT) & CP_SET_BIN_DATA_0_BIN_DATA_ADDR__MASK;
}

#define REG_CP_SET_BIN_DATA_1					0x00000001
#define CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__MASK		0xffffffff
#define CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__SHIFT		0
static inline uint32_t CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__SHIFT) & CP_SET_BIN_DATA_1_BIN_SIZE_ADDRESS__MASK;
}

#define REG_CP_SET_BIN_DATA5_0					0x00000000
#define CP_SET_BIN_DATA5_0_VSC_SIZE__MASK			0x003f0000
#define CP_SET_BIN_DATA5_0_VSC_SIZE__SHIFT			16
static inline uint32_t CP_SET_BIN_DATA5_0_VSC_SIZE(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA5_0_VSC_SIZE__SHIFT) & CP_SET_BIN_DATA5_0_VSC_SIZE__MASK;
}
#define CP_SET_BIN_DATA5_0_VSC_N__MASK				0x07c00000
#define CP_SET_BIN_DATA5_0_VSC_N__SHIFT				22
static inline uint32_t CP_SET_BIN_DATA5_0_VSC_N(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA5_0_VSC_N__SHIFT) & CP_SET_BIN_DATA5_0_VSC_N__MASK;
}

#define REG_CP_SET_BIN_DATA5_1					0x00000001
#define CP_SET_BIN_DATA5_1_BIN_DATA_ADDR_LO__MASK		0xffffffff
#define CP_SET_BIN_DATA5_1_BIN_DATA_ADDR_LO__SHIFT		0
static inline uint32_t CP_SET_BIN_DATA5_1_BIN_DATA_ADDR_LO(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA5_1_BIN_DATA_ADDR_LO__SHIFT) & CP_SET_BIN_DATA5_1_BIN_DATA_ADDR_LO__MASK;
}

#define REG_CP_SET_BIN_DATA5_2					0x00000002
#define CP_SET_BIN_DATA5_2_BIN_DATA_ADDR_HI__MASK		0xffffffff
#define CP_SET_BIN_DATA5_2_BIN_DATA_ADDR_HI__SHIFT		0
static inline uint32_t CP_SET_BIN_DATA5_2_BIN_DATA_ADDR_HI(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA5_2_BIN_DATA_ADDR_HI__SHIFT) & CP_SET_BIN_DATA5_2_BIN_DATA_ADDR_HI__MASK;
}

#define REG_CP_SET_BIN_DATA5_3					0x00000003
#define CP_SET_BIN_DATA5_3_BIN_SIZE_ADDRESS_LO__MASK		0xffffffff
#define CP_SET_BIN_DATA5_3_BIN_SIZE_ADDRESS_LO__SHIFT		0
static inline uint32_t CP_SET_BIN_DATA5_3_BIN_SIZE_ADDRESS_LO(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA5_3_BIN_SIZE_ADDRESS_LO__SHIFT) & CP_SET_BIN_DATA5_3_BIN_SIZE_ADDRESS_LO__MASK;
}

#define REG_CP_SET_BIN_DATA5_4					0x00000004
#define CP_SET_BIN_DATA5_4_BIN_SIZE_ADDRESS_HI__MASK		0xffffffff
#define CP_SET_BIN_DATA5_4_BIN_SIZE_ADDRESS_HI__SHIFT		0
static inline uint32_t CP_SET_BIN_DATA5_4_BIN_SIZE_ADDRESS_HI(uint32_t val)
{
	return ((val) << CP_SET_BIN_DATA5_4_BIN_SIZE_ADDRESS_HI__SHIFT) & CP_SET_BIN_DATA5_4_BIN_SIZE_ADDRESS_HI__MASK;
}

#define REG_CP_REG_TO_MEM_0					0x00000000
#define CP_REG_TO_MEM_0_REG__MASK				0x0000ffff
#define CP_REG_TO_MEM_0_REG__SHIFT				0
static inline uint32_t CP_REG_TO_MEM_0_REG(uint32_t val)
{
	return ((val) << CP_REG_TO_MEM_0_REG__SHIFT) & CP_REG_TO_MEM_0_REG__MASK;
}
#define CP_REG_TO_MEM_0_CNT__MASK				0x3ff80000
#define CP_REG_TO_MEM_0_CNT__SHIFT				19
static inline uint32_t CP_REG_TO_MEM_0_CNT(uint32_t val)
{
	return ((val) << CP_REG_TO_MEM_0_CNT__SHIFT) & CP_REG_TO_MEM_0_CNT__MASK;
}
#define CP_REG_TO_MEM_0_64B					0x40000000
#define CP_REG_TO_MEM_0_ACCUMULATE				0x80000000

#define REG_CP_REG_TO_MEM_1					0x00000001
#define CP_REG_TO_MEM_1_DEST__MASK				0xffffffff
#define CP_REG_TO_MEM_1_DEST__SHIFT				0
static inline uint32_t CP_REG_TO_MEM_1_DEST(uint32_t val)
{
	return ((val) << CP_REG_TO_MEM_1_DEST__SHIFT) & CP_REG_TO_MEM_1_DEST__MASK;
}

#define REG_CP_MEM_TO_MEM_0					0x00000000
#define CP_MEM_TO_MEM_0_NEG_A					0x00000001
#define CP_MEM_TO_MEM_0_NEG_B					0x00000002
#define CP_MEM_TO_MEM_0_NEG_C					0x00000004
#define CP_MEM_TO_MEM_0_DOUBLE					0x20000000

#define REG_CP_COND_WRITE_0					0x00000000
#define CP_COND_WRITE_0_FUNCTION__MASK				0x00000007
#define CP_COND_WRITE_0_FUNCTION__SHIFT				0
static inline uint32_t CP_COND_WRITE_0_FUNCTION(enum cp_cond_function val)
{
	return ((val) << CP_COND_WRITE_0_FUNCTION__SHIFT) & CP_COND_WRITE_0_FUNCTION__MASK;
}
#define CP_COND_WRITE_0_POLL_MEMORY				0x00000010
#define CP_COND_WRITE_0_WRITE_MEMORY				0x00000100

#define REG_CP_COND_WRITE_1					0x00000001
#define CP_COND_WRITE_1_POLL_ADDR__MASK				0xffffffff
#define CP_COND_WRITE_1_POLL_ADDR__SHIFT			0
static inline uint32_t CP_COND_WRITE_1_POLL_ADDR(uint32_t val)
{
	return ((val) << CP_COND_WRITE_1_POLL_ADDR__SHIFT) & CP_COND_WRITE_1_POLL_ADDR__MASK;
}

#define REG_CP_COND_WRITE_2					0x00000002
#define CP_COND_WRITE_2_REF__MASK				0xffffffff
#define CP_COND_WRITE_2_REF__SHIFT				0
static inline uint32_t CP_COND_WRITE_2_REF(uint32_t val)
{
	return ((val) << CP_COND_WRITE_2_REF__SHIFT) & CP_COND_WRITE_2_REF__MASK;
}

#define REG_CP_COND_WRITE_3					0x00000003
#define CP_COND_WRITE_3_MASK__MASK				0xffffffff
#define CP_COND_WRITE_3_MASK__SHIFT				0
static inline uint32_t CP_COND_WRITE_3_MASK(uint32_t val)
{
	return ((val) << CP_COND_WRITE_3_MASK__SHIFT) & CP_COND_WRITE_3_MASK__MASK;
}

#define REG_CP_COND_WRITE_4					0x00000004
#define CP_COND_WRITE_4_WRITE_ADDR__MASK			0xffffffff
#define CP_COND_WRITE_4_WRITE_ADDR__SHIFT			0
static inline uint32_t CP_COND_WRITE_4_WRITE_ADDR(uint32_t val)
{
	return ((val) << CP_COND_WRITE_4_WRITE_ADDR__SHIFT) & CP_COND_WRITE_4_WRITE_ADDR__MASK;
}

#define REG_CP_COND_WRITE_5					0x00000005
#define CP_COND_WRITE_5_WRITE_DATA__MASK			0xffffffff
#define CP_COND_WRITE_5_WRITE_DATA__SHIFT			0
static inline uint32_t CP_COND_WRITE_5_WRITE_DATA(uint32_t val)
{
	return ((val) << CP_COND_WRITE_5_WRITE_DATA__SHIFT) & CP_COND_WRITE_5_WRITE_DATA__MASK;
}

#define REG_CP_COND_WRITE5_0					0x00000000
#define CP_COND_WRITE5_0_FUNCTION__MASK				0x00000007
#define CP_COND_WRITE5_0_FUNCTION__SHIFT			0
static inline uint32_t CP_COND_WRITE5_0_FUNCTION(enum cp_cond_function val)
{
	return ((val) << CP_COND_WRITE5_0_FUNCTION__SHIFT) & CP_COND_WRITE5_0_FUNCTION__MASK;
}
#define CP_COND_WRITE5_0_POLL_MEMORY				0x00000010
#define CP_COND_WRITE5_0_WRITE_MEMORY				0x00000100

#define REG_CP_COND_WRITE5_1					0x00000001
#define CP_COND_WRITE5_1_POLL_ADDR_LO__MASK			0xffffffff
#define CP_COND_WRITE5_1_POLL_ADDR_LO__SHIFT			0
static inline uint32_t CP_COND_WRITE5_1_POLL_ADDR_LO(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_1_POLL_ADDR_LO__SHIFT) & CP_COND_WRITE5_1_POLL_ADDR_LO__MASK;
}

#define REG_CP_COND_WRITE5_2					0x00000002
#define CP_COND_WRITE5_2_POLL_ADDR_HI__MASK			0xffffffff
#define CP_COND_WRITE5_2_POLL_ADDR_HI__SHIFT			0
static inline uint32_t CP_COND_WRITE5_2_POLL_ADDR_HI(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_2_POLL_ADDR_HI__SHIFT) & CP_COND_WRITE5_2_POLL_ADDR_HI__MASK;
}

#define REG_CP_COND_WRITE5_3					0x00000003
#define CP_COND_WRITE5_3_REF__MASK				0xffffffff
#define CP_COND_WRITE5_3_REF__SHIFT				0
static inline uint32_t CP_COND_WRITE5_3_REF(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_3_REF__SHIFT) & CP_COND_WRITE5_3_REF__MASK;
}

#define REG_CP_COND_WRITE5_4					0x00000004
#define CP_COND_WRITE5_4_MASK__MASK				0xffffffff
#define CP_COND_WRITE5_4_MASK__SHIFT				0
static inline uint32_t CP_COND_WRITE5_4_MASK(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_4_MASK__SHIFT) & CP_COND_WRITE5_4_MASK__MASK;
}

#define REG_CP_COND_WRITE5_5					0x00000005
#define CP_COND_WRITE5_5_WRITE_ADDR_LO__MASK			0xffffffff
#define CP_COND_WRITE5_5_WRITE_ADDR_LO__SHIFT			0
static inline uint32_t CP_COND_WRITE5_5_WRITE_ADDR_LO(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_5_WRITE_ADDR_LO__SHIFT) & CP_COND_WRITE5_5_WRITE_ADDR_LO__MASK;
}

#define REG_CP_COND_WRITE5_6					0x00000006
#define CP_COND_WRITE5_6_WRITE_ADDR_HI__MASK			0xffffffff
#define CP_COND_WRITE5_6_WRITE_ADDR_HI__SHIFT			0
static inline uint32_t CP_COND_WRITE5_6_WRITE_ADDR_HI(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_6_WRITE_ADDR_HI__SHIFT) & CP_COND_WRITE5_6_WRITE_ADDR_HI__MASK;
}

#define REG_CP_COND_WRITE5_7					0x00000007
#define CP_COND_WRITE5_7_WRITE_DATA__MASK			0xffffffff
#define CP_COND_WRITE5_7_WRITE_DATA__SHIFT			0
static inline uint32_t CP_COND_WRITE5_7_WRITE_DATA(uint32_t val)
{
	return ((val) << CP_COND_WRITE5_7_WRITE_DATA__SHIFT) & CP_COND_WRITE5_7_WRITE_DATA__MASK;
}

#define REG_CP_DISPATCH_COMPUTE_0				0x00000000

#define REG_CP_DISPATCH_COMPUTE_1				0x00000001
#define CP_DISPATCH_COMPUTE_1_X__MASK				0xffffffff
#define CP_DISPATCH_COMPUTE_1_X__SHIFT				0
static inline uint32_t CP_DISPATCH_COMPUTE_1_X(uint32_t val)
{
	return ((val) << CP_DISPATCH_COMPUTE_1_X__SHIFT) & CP_DISPATCH_COMPUTE_1_X__MASK;
}

#define REG_CP_DISPATCH_COMPUTE_2				0x00000002
#define CP_DISPATCH_COMPUTE_2_Y__MASK				0xffffffff
#define CP_DISPATCH_COMPUTE_2_Y__SHIFT				0
static inline uint32_t CP_DISPATCH_COMPUTE_2_Y(uint32_t val)
{
	return ((val) << CP_DISPATCH_COMPUTE_2_Y__SHIFT) & CP_DISPATCH_COMPUTE_2_Y__MASK;
}

#define REG_CP_DISPATCH_COMPUTE_3				0x00000003
#define CP_DISPATCH_COMPUTE_3_Z__MASK				0xffffffff
#define CP_DISPATCH_COMPUTE_3_Z__SHIFT				0
static inline uint32_t CP_DISPATCH_COMPUTE_3_Z(uint32_t val)
{
	return ((val) << CP_DISPATCH_COMPUTE_3_Z__SHIFT) & CP_DISPATCH_COMPUTE_3_Z__MASK;
}

#define REG_CP_SET_RENDER_MODE_0				0x00000000
#define CP_SET_RENDER_MODE_0_MODE__MASK				0x000001ff
#define CP_SET_RENDER_MODE_0_MODE__SHIFT			0
static inline uint32_t CP_SET_RENDER_MODE_0_MODE(enum render_mode_cmd val)
{
	return ((val) << CP_SET_RENDER_MODE_0_MODE__SHIFT) & CP_SET_RENDER_MODE_0_MODE__MASK;
}

#define REG_CP_SET_RENDER_MODE_1				0x00000001
#define CP_SET_RENDER_MODE_1_ADDR_0_LO__MASK			0xffffffff
#define CP_SET_RENDER_MODE_1_ADDR_0_LO__SHIFT			0
static inline uint32_t CP_SET_RENDER_MODE_1_ADDR_0_LO(uint32_t val)
{
	return ((val) << CP_SET_RENDER_MODE_1_ADDR_0_LO__SHIFT) & CP_SET_RENDER_MODE_1_ADDR_0_LO__MASK;
}

#define REG_CP_SET_RENDER_MODE_2				0x00000002
#define CP_SET_RENDER_MODE_2_ADDR_0_HI__MASK			0xffffffff
#define CP_SET_RENDER_MODE_2_ADDR_0_HI__SHIFT			0
static inline uint32_t CP_SET_RENDER_MODE_2_ADDR_0_HI(uint32_t val)
{
	return ((val) << CP_SET_RENDER_MODE_2_ADDR_0_HI__SHIFT) & CP_SET_RENDER_MODE_2_ADDR_0_HI__MASK;
}

#define REG_CP_SET_RENDER_MODE_3				0x00000003
#define CP_SET_RENDER_MODE_3_VSC_ENABLE				0x00000008
#define CP_SET_RENDER_MODE_3_GMEM_ENABLE			0x00000010

#define REG_CP_SET_RENDER_MODE_4				0x00000004

#define REG_CP_SET_RENDER_MODE_5				0x00000005
#define CP_SET_RENDER_MODE_5_ADDR_1_LEN__MASK			0xffffffff
#define CP_SET_RENDER_MODE_5_ADDR_1_LEN__SHIFT			0
static inline uint32_t CP_SET_RENDER_MODE_5_ADDR_1_LEN(uint32_t val)
{
	return ((val) << CP_SET_RENDER_MODE_5_ADDR_1_LEN__SHIFT) & CP_SET_RENDER_MODE_5_ADDR_1_LEN__MASK;
}

#define REG_CP_SET_RENDER_MODE_6				0x00000006
#define CP_SET_RENDER_MODE_6_ADDR_1_LO__MASK			0xffffffff
#define CP_SET_RENDER_MODE_6_ADDR_1_LO__SHIFT			0
static inline uint32_t CP_SET_RENDER_MODE_6_ADDR_1_LO(uint32_t val)
{
	return ((val) << CP_SET_RENDER_MODE_6_ADDR_1_LO__SHIFT) & CP_SET_RENDER_MODE_6_ADDR_1_LO__MASK;
}

#define REG_CP_SET_RENDER_MODE_7				0x00000007
#define CP_SET_RENDER_MODE_7_ADDR_1_HI__MASK			0xffffffff
#define CP_SET_RENDER_MODE_7_ADDR_1_HI__SHIFT			0
static inline uint32_t CP_SET_RENDER_MODE_7_ADDR_1_HI(uint32_t val)
{
	return ((val) << CP_SET_RENDER_MODE_7_ADDR_1_HI__SHIFT) & CP_SET_RENDER_MODE_7_ADDR_1_HI__MASK;
}

#define REG_CP_COMPUTE_CHECKPOINT_0				0x00000000
#define CP_COMPUTE_CHECKPOINT_0_ADDR_0_LO__MASK			0xffffffff
#define CP_COMPUTE_CHECKPOINT_0_ADDR_0_LO__SHIFT		0
static inline uint32_t CP_COMPUTE_CHECKPOINT_0_ADDR_0_LO(uint32_t val)
{
	return ((val) << CP_COMPUTE_CHECKPOINT_0_ADDR_0_LO__SHIFT) & CP_COMPUTE_CHECKPOINT_0_ADDR_0_LO__MASK;
}

#define REG_CP_COMPUTE_CHECKPOINT_1				0x00000001
#define CP_COMPUTE_CHECKPOINT_1_ADDR_0_HI__MASK			0xffffffff
#define CP_COMPUTE_CHECKPOINT_1_ADDR_0_HI__SHIFT		0
static inline uint32_t CP_COMPUTE_CHECKPOINT_1_ADDR_0_HI(uint32_t val)
{
	return ((val) << CP_COMPUTE_CHECKPOINT_1_ADDR_0_HI__SHIFT) & CP_COMPUTE_CHECKPOINT_1_ADDR_0_HI__MASK;
}

#define REG_CP_COMPUTE_CHECKPOINT_2				0x00000002

#define REG_CP_COMPUTE_CHECKPOINT_3				0x00000003

#define REG_CP_COMPUTE_CHECKPOINT_4				0x00000004
#define CP_COMPUTE_CHECKPOINT_4_ADDR_1_LEN__MASK		0xffffffff
#define CP_COMPUTE_CHECKPOINT_4_ADDR_1_LEN__SHIFT		0
static inline uint32_t CP_COMPUTE_CHECKPOINT_4_ADDR_1_LEN(uint32_t val)
{
	return ((val) << CP_COMPUTE_CHECKPOINT_4_ADDR_1_LEN__SHIFT) & CP_COMPUTE_CHECKPOINT_4_ADDR_1_LEN__MASK;
}

#define REG_CP_COMPUTE_CHECKPOINT_5				0x00000005
#define CP_COMPUTE_CHECKPOINT_5_ADDR_1_LO__MASK			0xffffffff
#define CP_COMPUTE_CHECKPOINT_5_ADDR_1_LO__SHIFT		0
static inline uint32_t CP_COMPUTE_CHECKPOINT_5_ADDR_1_LO(uint32_t val)
{
	return ((val) << CP_COMPUTE_CHECKPOINT_5_ADDR_1_LO__SHIFT) & CP_COMPUTE_CHECKPOINT_5_ADDR_1_LO__MASK;
}

#define REG_CP_COMPUTE_CHECKPOINT_6				0x00000006
#define CP_COMPUTE_CHECKPOINT_6_ADDR_1_HI__MASK			0xffffffff
#define CP_COMPUTE_CHECKPOINT_6_ADDR_1_HI__SHIFT		0
static inline uint32_t CP_COMPUTE_CHECKPOINT_6_ADDR_1_HI(uint32_t val)
{
	return ((val) << CP_COMPUTE_CHECKPOINT_6_ADDR_1_HI__SHIFT) & CP_COMPUTE_CHECKPOINT_6_ADDR_1_HI__MASK;
}

#define REG_CP_PERFCOUNTER_ACTION_0				0x00000000

#define REG_CP_PERFCOUNTER_ACTION_1				0x00000001
#define CP_PERFCOUNTER_ACTION_1_ADDR_0_LO__MASK			0xffffffff
#define CP_PERFCOUNTER_ACTION_1_ADDR_0_LO__SHIFT		0
static inline uint32_t CP_PERFCOUNTER_ACTION_1_ADDR_0_LO(uint32_t val)
{
	return ((val) << CP_PERFCOUNTER_ACTION_1_ADDR_0_LO__SHIFT) & CP_PERFCOUNTER_ACTION_1_ADDR_0_LO__MASK;
}

#define REG_CP_PERFCOUNTER_ACTION_2				0x00000002
#define CP_PERFCOUNTER_ACTION_2_ADDR_0_HI__MASK			0xffffffff
#define CP_PERFCOUNTER_ACTION_2_ADDR_0_HI__SHIFT		0
static inline uint32_t CP_PERFCOUNTER_ACTION_2_ADDR_0_HI(uint32_t val)
{
	return ((val) << CP_PERFCOUNTER_ACTION_2_ADDR_0_HI__SHIFT) & CP_PERFCOUNTER_ACTION_2_ADDR_0_HI__MASK;
}

#define REG_CP_EVENT_WRITE_0					0x00000000
#define CP_EVENT_WRITE_0_EVENT__MASK				0x000000ff
#define CP_EVENT_WRITE_0_EVENT__SHIFT				0
static inline uint32_t CP_EVENT_WRITE_0_EVENT(enum vgt_event_type val)
{
	return ((val) << CP_EVENT_WRITE_0_EVENT__SHIFT) & CP_EVENT_WRITE_0_EVENT__MASK;
}
#define CP_EVENT_WRITE_0_TIMESTAMP				0x40000000

#define REG_CP_EVENT_WRITE_1					0x00000001
#define CP_EVENT_WRITE_1_ADDR_0_LO__MASK			0xffffffff
#define CP_EVENT_WRITE_1_ADDR_0_LO__SHIFT			0
static inline uint32_t CP_EVENT_WRITE_1_ADDR_0_LO(uint32_t val)
{
	return ((val) << CP_EVENT_WRITE_1_ADDR_0_LO__SHIFT) & CP_EVENT_WRITE_1_ADDR_0_LO__MASK;
}

#define REG_CP_EVENT_WRITE_2					0x00000002
#define CP_EVENT_WRITE_2_ADDR_0_HI__MASK			0xffffffff
#define CP_EVENT_WRITE_2_ADDR_0_HI__SHIFT			0
static inline uint32_t CP_EVENT_WRITE_2_ADDR_0_HI(uint32_t val)
{
	return ((val) << CP_EVENT_WRITE_2_ADDR_0_HI__SHIFT) & CP_EVENT_WRITE_2_ADDR_0_HI__MASK;
}

#define REG_CP_EVENT_WRITE_3					0x00000003

#define REG_CP_BLIT_0						0x00000000
#define CP_BLIT_0_OP__MASK					0x0000000f
#define CP_BLIT_0_OP__SHIFT					0
static inline uint32_t CP_BLIT_0_OP(enum cp_blit_cmd val)
{
	return ((val) << CP_BLIT_0_OP__SHIFT) & CP_BLIT_0_OP__MASK;
}

#define REG_CP_BLIT_1						0x00000001
#define CP_BLIT_1_SRC_X1__MASK					0x0000ffff
#define CP_BLIT_1_SRC_X1__SHIFT					0
static inline uint32_t CP_BLIT_1_SRC_X1(uint32_t val)
{
	return ((val) << CP_BLIT_1_SRC_X1__SHIFT) & CP_BLIT_1_SRC_X1__MASK;
}
#define CP_BLIT_1_SRC_Y1__MASK					0xffff0000
#define CP_BLIT_1_SRC_Y1__SHIFT					16
static inline uint32_t CP_BLIT_1_SRC_Y1(uint32_t val)
{
	return ((val) << CP_BLIT_1_SRC_Y1__SHIFT) & CP_BLIT_1_SRC_Y1__MASK;
}

#define REG_CP_BLIT_2						0x00000002
#define CP_BLIT_2_SRC_X2__MASK					0x0000ffff
#define CP_BLIT_2_SRC_X2__SHIFT					0
static inline uint32_t CP_BLIT_2_SRC_X2(uint32_t val)
{
	return ((val) << CP_BLIT_2_SRC_X2__SHIFT) & CP_BLIT_2_SRC_X2__MASK;
}
#define CP_BLIT_2_SRC_Y2__MASK					0xffff0000
#define CP_BLIT_2_SRC_Y2__SHIFT					16
static inline uint32_t CP_BLIT_2_SRC_Y2(uint32_t val)
{
	return ((val) << CP_BLIT_2_SRC_Y2__SHIFT) & CP_BLIT_2_SRC_Y2__MASK;
}

#define REG_CP_BLIT_3						0x00000003
#define CP_BLIT_3_DST_X1__MASK					0x0000ffff
#define CP_BLIT_3_DST_X1__SHIFT					0
static inline uint32_t CP_BLIT_3_DST_X1(uint32_t val)
{
	return ((val) << CP_BLIT_3_DST_X1__SHIFT) & CP_BLIT_3_DST_X1__MASK;
}
#define CP_BLIT_3_DST_Y1__MASK					0xffff0000
#define CP_BLIT_3_DST_Y1__SHIFT					16
static inline uint32_t CP_BLIT_3_DST_Y1(uint32_t val)
{
	return ((val) << CP_BLIT_3_DST_Y1__SHIFT) & CP_BLIT_3_DST_Y1__MASK;
}

#define REG_CP_BLIT_4						0x00000004
#define CP_BLIT_4_DST_X2__MASK					0x0000ffff
#define CP_BLIT_4_DST_X2__SHIFT					0
static inline uint32_t CP_BLIT_4_DST_X2(uint32_t val)
{
	return ((val) << CP_BLIT_4_DST_X2__SHIFT) & CP_BLIT_4_DST_X2__MASK;
}
#define CP_BLIT_4_DST_Y2__MASK					0xffff0000
#define CP_BLIT_4_DST_Y2__SHIFT					16
static inline uint32_t CP_BLIT_4_DST_Y2(uint32_t val)
{
	return ((val) << CP_BLIT_4_DST_Y2__SHIFT) & CP_BLIT_4_DST_Y2__MASK;
}

#define REG_CP_EXEC_CS_0					0x00000000

#define REG_CP_EXEC_CS_1					0x00000001
#define CP_EXEC_CS_1_NGROUPS_X__MASK				0xffffffff
#define CP_EXEC_CS_1_NGROUPS_X__SHIFT				0
static inline uint32_t CP_EXEC_CS_1_NGROUPS_X(uint32_t val)
{
	return ((val) << CP_EXEC_CS_1_NGROUPS_X__SHIFT) & CP_EXEC_CS_1_NGROUPS_X__MASK;
}

#define REG_CP_EXEC_CS_2					0x00000002
#define CP_EXEC_CS_2_NGROUPS_Y__MASK				0xffffffff
#define CP_EXEC_CS_2_NGROUPS_Y__SHIFT				0
static inline uint32_t CP_EXEC_CS_2_NGROUPS_Y(uint32_t val)
{
	return ((val) << CP_EXEC_CS_2_NGROUPS_Y__SHIFT) & CP_EXEC_CS_2_NGROUPS_Y__MASK;
}

#define REG_CP_EXEC_CS_3					0x00000003
#define CP_EXEC_CS_3_NGROUPS_Z__MASK				0xffffffff
#define CP_EXEC_CS_3_NGROUPS_Z__SHIFT				0
static inline uint32_t CP_EXEC_CS_3_NGROUPS_Z(uint32_t val)
{
	return ((val) << CP_EXEC_CS_3_NGROUPS_Z__SHIFT) & CP_EXEC_CS_3_NGROUPS_Z__MASK;
}


#endif /* ADRENO_PM4_XML */
