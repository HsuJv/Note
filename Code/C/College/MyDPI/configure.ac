#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([DPI], [1.0], [jv.hsu@outlook.com])
AC_CONFIG_SRCDIR([src/DPI.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([-Wall subdir-objects])

AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug], [enable DEBUG mode(default=no)]),
              [],                                                            
              [enable_debug=no])
              
AS_IF([test "x$enable_debug" = "xyes"], [CFLAGS="-g -O0 -DDEBUG -Wall"],       
    [test "x$enable_debug" = "xno"], [CFLAGS="-O2 -Wall"],                  
    [])

AC_PROG_INSTALL
AM_PROG_AR
LT_INIT

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lopendpi':
AC_CHECK_LIB([opendpi], [ipoque_detection_process_packet])
# FIXME: Replace `main' with a function in `-lpcap':
AC_CHECK_LIB([pcap], [pcap_loop])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [pthread_create])
# FIXME: Replace `main' with a function in `-lutil':
AC_CHECK_LIB([util], [Atom_string])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h limits.h netinet/in.h stddef.h stdint.h stdlib.h string.h strings.h sys/param.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([dup2 getcwd memset putenv socket strcasecmp strrchr])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/OpenDPI/Makefile
                 src/OpenDPI/src/include/Makefile
                 src/OpenDPI/src/lib/Makefile
                 src/http/Makefile
                 src/util/include/Makefile
                 src/util/lib/Makefile
                 test/Makefile])
AC_OUTPUT
