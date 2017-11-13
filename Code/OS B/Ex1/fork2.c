// fork2.c

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    int p1, p2;

    while( (p1 = fork()) == -1);
    if (p1 == 0){
        for (int i = 0; i < 8; i++){
            printf("daughter %d\n", i);
            sleep(4);
        }

    }
    else{
        while( (p2 = fork()) == -1);
        if (p2 == 0){
            for (int i = 0; i < 8; i++){
                printf("son %d\n", i);
                sleep(4);
            }
        }
        else{
            for (int i = 0; i < 8; i++){
                printf("parent %d\n", i);
                sleep(4);
            }
        }
    }

    return 0;
}