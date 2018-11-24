#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char const *argv[]){
    if(argc < 2){
        fprintf(stderr, "Usage: %s argv[1].\n", argv[0]);
        return 1;
    }

    if (opendir(argv[1])){
        perror("Dir exists.\n");
        return 1;
    }
    mkdir(argv[1], 0777);
    
    return 0;
}