/*************************************************************************
    > File Name: openVSfopen.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-30
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define N 1 << 24 /* 4 MB file */

int main(){
    int i, fd;
    double start, end;
    FILE* f;


    srand(time(NULL));
    fd = open("test", O_CREAT, S_IRUSR|S_IRGRP|S_IROTH);
    close(fd);
    start = clock();
    for (i = 0; i < N; i ++){
        fd = open("test", O_RDONLY);
        close(fd);
    }
    end = clock();
    fprintf(stdout, "open: %lf\n", end - start);

    start = clock();
    for (i = 0 ; i < N; i ++){
        f = fopen("test", "r");
        fclose(f);
    }
    end = clock();
    fprintf(stdout, "fopen: %lf\n", end - start);
    return 0;
}
