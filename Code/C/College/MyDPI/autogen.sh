#!/bin/sh

mkdir m4;
libtoolize;
autoheader;
automake --gnu --add-missing --copy;
automake --add-missing;
autoreconf -fi;
rm -Rf autom4te.cache;
