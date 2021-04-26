/*************************************************************************
    > File Name: fscanfVSread.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-30
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>

#define N (1 << 24)

int main(){
    int  fd, i;
    FILE *f;
    char ch;
    int start, end;
    unsigned char *s;

    fd = open("test", O_RDONLY);
    start = clock();
    while (read(fd, (void *)&ch, 1) > 0);
    end = clock();
    close(fd);
    fprintf(stdout, "read: %d\n", end - start);

    f = fopen("test", "r");
    start = clock();
    while (fscanf(f, "%c", &ch) == 1);
    end = clock();
    fclose(f);
    fprintf(stdout, "fscanf: %d\n", end - start);
   
    fd = open("test", O_RDONLY);
    s = (unsigned char *)mmap(NULL, N, PROT_READ, MAP_SHARED, fd, 0);
    start = clock();
    for (i = 0; i < N; i++){
        ch = s[i];
    }
    end = clock();
    close(fd);
    fprintf(stdout, "mmap: %d\n", end - start);

    return 0;
}
