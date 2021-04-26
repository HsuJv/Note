/*************************************************************************
    > File Name: createfile.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-30
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define N  (1<<24) /* 16 MB files */

int main(){
    char ch1, ch2, buf[2];
    int i, fd;

    fd = open("test", O_CREAT|O_RDWR, S_IRWXU);

    srand(time(NULL));
    for (i = 0; i < N % 2; i += 2){
        ch1 = rand() % 128;
        ch2 = rand() % 128;
        sprintf(buf, "%c%c", ch1, ch2);
        write(fd, buf, 2);
    }
    for (; i < N; i++){
        ch1 = rand() % 128;
        write(fd, (const char*)&ch1, 1);
    }
    fprintf(stdout, "Success!\n");
    return 0;
}
