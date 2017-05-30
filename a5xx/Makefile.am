AUTOMAKE_OPTIONS=subdir-objects

bin_PROGRAMS = \
	a5xx_mem_to_mem \
	a5xx_perfctr \
	a5xx_blit \
	a5xx_dma

LDFLAGS = \
	-no-undefined

LDADD = \
	$(DRM_LIBS)

CFLAGS = \
	-O0 -g -lm \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	$(DRM_CFLAGS)

noinst_LTLIBRARIES = liba5xxcommon.la

liba5xxcommon_la_SOURCES = \
	a5xx_common.c \
	a5xx_common.h

liba5xxcommon_la_CFLAGS = \
	$(CFLAGS)

liba5xxcommon_la_LIBADD = \
	$(top_builddir)/common/libcommon.la \
	$(LDADD)

a5xx_blit_SOURCES = \
	a5xx_blit.c

a5xx_blit_LDADD = \
	liba5xxcommon.la

a5xx_dma_SOURCES = \
	a5xx_dma.c

a5xx_dma_LDADD = \
	liba5xxcommon.la

a5xx_mem_to_mem_SOURCES = \
	a5xx_mem_to_mem.c

a5xx_mem_to_mem_LDADD = \
	liba5xxcommon.la

a5xx_perfctr_SOURCES = \
	a5xx_perfctr.c

a5xx_perfctr_LDADD = \
	liba5xxcommon.la
