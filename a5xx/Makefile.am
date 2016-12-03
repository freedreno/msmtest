AUTOMAKE_OPTIONS=subdir-objects

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

