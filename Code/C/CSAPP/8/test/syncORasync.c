/*************************************************************************
    > File Name: syncORasync.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-05-05
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle(int sig){
    sleep(10);
    exit(1);
}
int main(){
    long i;

    signal(SIGINT, handle);
    for (i = 1; i <= 2 << 24; i++){
        fprintf(stdout, "test\n");
    }
}
