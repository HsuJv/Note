SUBDIRS = OpenDPI util/lib util/include http
AM_CPPFLAGS = -I$(top_srcdir)/src/OpenDPI/src/include/ -I$(top_srcdir)/src/util/include/ -I$(top_srcdir)/src/SDK/include/
AM_LDFLAGS = -static -LOpenDPI/src/lib -lopendpi -Lutil/lib -lutil -LSDK/lib -L$(top_srcdir)/src/SDK/lib -lpcre2-8 -lpcap -lpthread

bin_PROGRAMS = DPI
DPI_SOURCE = DPI.c