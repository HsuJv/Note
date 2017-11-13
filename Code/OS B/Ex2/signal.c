// signal.c


#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void int_func(int);
int k; // 定义循环变量

void int_func(int sig){
    k = 0;
}

int main(int argc, char const *argv[]){
    signal(SIGINT, int_func);
    k = 1;

    while(k == 1) {
        printf("Hello!\n");
    }

    printf("OK\n");
    printf("%d\n", getppid());
    return 0;
}