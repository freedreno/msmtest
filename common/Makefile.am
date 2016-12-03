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

msmtest_SOURCES = \
	msmtest.c

submittest_SOURCES = \
	submittest.c

evilsubmittest_SOURCES = \
	evilsubmittest.c

