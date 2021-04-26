/*************************************************************************
    > File Name: test.c
    > Author: Hsu
    > Mail: jv.hsu@qq.com 
    > Created Time: 2018-04-27
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>

extern void mm_free(void*);
extern void* mm_malloc(size_t);
extern void mem_init(void);
extern int mm_init(void);
extern void heap_display(void);

void init(){
    mem_init();
    if (mm_init() == -1){
        fprintf(stdout, "Initialize failed.");
        exit(1);
    }
}

int main(int argc, char* argv[]){
    char *p;
    char *s = "Hello";

    if (argc != 1){
        fprintf(stdout, "Usage: %s\n", argv[0]);
        return 1;
    }
    init();
    fprintf(stdout, "After init:\n");
    heap_display();
    
    p = (char *)mm_malloc(10);
    fprintf(stdout, "After allocating:\n");
    heap_display();

    memcpy(p, s, sizeof(s));
    fprintf(stdout, "Pointer p is: %s\n\n\n", p);

    mm_free(p);
    fprintf(stdout, "After free:\n");
    heap_display();
    return 0;
}
