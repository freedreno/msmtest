AUTOMAKE_OPTIONS=subdir-objects

bin_PROGRAMS = \
	msmtest \
	submittest \
	evilsubmittest

LDFLAGS = \
	-no-undefined

LDADD = \
	$(DRM_LIBS)

CFLAGS = \
	-O0 -g -lm \
	-I$(top_srcdir)/include \
	$(DRM_CFLAGS)

noinst_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = \
	common.c \
	common.h

libcommon_la_CFLAGS = \
	$(CFLAGS)

libcommon_la_LIBADD = \
	$(LDADD)

msmtest_SOURCES = \
	msmtest.c

msmtest_LDADD = \
	libcommon.la

submittest_SOURCES = \
	submittest.c

evilsubmittest_SOURCES = \
	evilsubmittest.c

