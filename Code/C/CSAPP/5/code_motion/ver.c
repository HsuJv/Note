/*************************************************************************
    > File Name: ver.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-29
 ************************************************************************/

#include "ver.h"
#include <stdlib.h>

/* Create vector of specified length */
vec_ptr new_ver(long len){
    /* Allocate header structure */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_ptr));
    data_t *data = NULL;
    if (!result){
        return NULL; /* NO enough storage */
    }
    result->len = len;
    /* Allocate array */
    if (len > 0){
        data = (data_t *)calloc(len, sizeof(data_t));
        if (!data) {
            free((void*) result);
            return NULL; /* No enough storage */
        }
    }
    
    /* Data will either be NULL or allocated array */
    result->data = data;
    return result;
}

/*
 * Retrieve vector element and store at dest
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, long index, data_t *dest){
    if (index < 0 || index >= v->len){
        return 0; /* Out of bounds */
    }
    *dest = v->data[index];
    return 1;
}

/* Return lenght of vector */
long vec_length(vec_ptr v){
    return v->len;
}

/* Implementation with maximun use of data abstraction */
void combine1(vec_ptr v, data_t *dest){
    long i;

    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++){
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine2(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++){
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}
