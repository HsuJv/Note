httpdir = ${prefix}/http

http_DATA = Chart.bundle.js \
            data.js \
            display.js \
            jquery.js \
            myChart.js \
            index.html

httpcgidir = ${httpdir}/cgi

httpcgi_PROGRAMS = get_data
get_data_SOURCES = cgi/get_data.c
get_data_CPPFLAGS = -I$(top_srcdir)/src/OpenDPI/src/include/ -I$(top_srcdir)/src/
