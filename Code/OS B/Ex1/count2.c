// count2.c

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    fork();
    fork();
    fork();
    printf("Hello, world! from process id: %d, it's parent id: %d\n", getpid(), getppid());
    wait(0);
    wait(0);
    wait(0);
    return 0;
}