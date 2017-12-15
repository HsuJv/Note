#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main(int argc, char const *argv[]){
    int fds, fdd;
    char buf[BUF_SIZE];

    size_t count = 0;

    if (argc != 3){
        return 1;
    }

    fds = open(argv[1], O_RDONLY);
    fdd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC);

    if (fds && fdd){
        while((count = read(fds, buf, sizeof(buf))) > 0) {
            write(fdd, buf, count);
        }
    }

    close(fds);
    close(fdd);
    return 0;
}