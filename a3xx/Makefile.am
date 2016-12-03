AUTOMAKE_OPTIONS=subdir-objects

bin_PROGRAMS = \
	a3xx_pm4test

LDFLAGS = \
	-no-undefined

LDADD = \
	$(DRM_LIBS)

CFLAGS = \
	-O0 -g -lm \
	-I$(top_srcdir)/include \
	$(DRM_CFLAGS)

a3xx_pm4test_SOURCES = \
	a3xx_pm4test.c
