/*************************************************************************
    > File Name: vec.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-29
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "vec.h"

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

data_t* get_vec_start(vec_ptr v){
    return v->data;
}

/* 2 x 1 loop unrolling */
void combine5(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);
    long limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2){
        acc = (acc OP data[i]) OP data[i+1];
    }

    /* Finish any remaining elements */
    for(; i< length; i++){
        acc = acc OP data[i];
    }

    *dest = acc;
}

/* 2 x 2 loop unrolling */
void combine6(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);
    long limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2){
        acc0 = acc0 OP data[i];
        acc1 = acc1 OP data[i+1];
    }

    /* Finish any remaining elements */
    for(; i < length; i++){
        acc0 = acc0 OP data[i];
    }
    *dest = acc0 OP acc1;
}

/* 2 x 1a loop unrolling */
void combine7(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);
    long limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i += 2){
        acc = acc OP (data[i] OP data[i+1]);
    }

    /* Finish any remaining elements */
    for(; i< length; i++){
        acc = acc OP data[i];
    }

    *dest = acc;
}

