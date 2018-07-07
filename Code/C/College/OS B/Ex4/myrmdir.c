#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: %s argv[1].\n", argv[0]);
        return 1;
    }

    if (!opendir(argv[1])){
        perror("Dir not exists.\n");
        return 1;
    }
    rmdir(argv[1]);
    
    return 0;
}