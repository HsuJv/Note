/*************************************************************************
    > File Name: ver.h
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-29
 ************************************************************************/

#include<stdio.h>

#ifdef T_INT
typedef long data_t;
#else
typedef double data_t;
#endif

#define IDENT 0
#define OP +

/* Create abstract data type for vector */
typedef struct {
    long len;
    data_t *data;
}vec_rec, *vec_ptr;
