#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    unsigned char* ptr, *start;
    int fd;

    if (argc != 2){
        fprintf(stdout, "Usage: ./mmaptest filename.\n");
        return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1){
        fprintf(stdout, "File not exists\n");
        return 1;
    }

    ptr = (unsigned char*)mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, fd, 0);
    start = ptr;

    while (*ptr != 0){
        fprintf(stdout, "%c", *ptr++);
    }
    fprintf(stdout, "\n");
    munmap(start, getpagesize());
    return 0;
}
