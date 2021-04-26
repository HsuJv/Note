/*************************************************************************
    > File Name: memlib.c
    > Author: Hsu
    > Mail: jv.hsu@qq.com 
    > Created Time: 2018-04-25
 ************************************************************************/
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>

/* Private global variables */
static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

#define MAX_HEAP (2<<20)

/* mem_init:
 * Initialize the memory system mode
 */
void mem_init(void){
    mem_heap = (char*) malloc(MAX_HEAP);
    mem_brk = (char*)mem_heap;
    mem_max_addr = (char *)(mem_heap + MAX_HEAP);
}

/*
 * mem_sbrk - Sample model of the sbrk function. Extends the heap
 * by incr bytes and returns the start address of the new area. In
 * this model, the heap cannot be shrunk
 */
void *mem_sbrk(int incr){
    char *old_brk = mem_brk;

    if ((incr < 0) || ((mem_brk + incr) > mem_max_addr)){
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed. Ran out of memory...\n");
        return (void *) -1;
    }
    mem_brk += incr;
    return (void *)old_brk;
}
