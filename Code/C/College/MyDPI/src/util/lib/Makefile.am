AM_CPPFLAGS = -I$(top_srcdir)/src/util/include/ -I$(top_srcdir)/src/OpenDPI/src/include/ -I$(top_srcdir)/src/SDK/include/
AM_LDFLAGS = -L$(top_srcdir)/src/SDK/lib

noinst_LTLIBRARIES = libutil.la

libutil_la_SOURCES = assert.c \
			atom.c \
			except.c \
			mem.c \
			tinyhttp.c \
			msi.c

snortdir = $(prefix)/bin
snort_DATA = snort3-community.rules