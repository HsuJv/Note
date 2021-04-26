/*************************************************************************
    > File Name: callocVSmalloc.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-05-13
 ************************************************************************/

#include <csapp.h>
#include <time.h>

#define N (1<<24)

int main(){
    int start, end;
    int *s;

    start = clock();
    for (int i = 0; i < 100; i++){
        s = (int*) calloc (N, sizeof(int));
        free(s);
    }
    end = clock();
    printf("Calloc: %lf\n", ((double)end - start)/1000000 );

    start = clock();
    for (int i = 0; i < 100; i++){
        s = (int *) malloc (N * sizeof(int));
        memset(s, 0, sizeof(int) * N);
        free(s);
    }
    end = clock();
    printf("Malloc + Memset: %lf\n",((double)end - start)/1000000);

    return 0;
}
