#include <stdio.h>
#include <string.h>
#include <dirent.h>

int list(DIR *dir){
    struct dirent *pdir;

    while((pdir = readdir(dir)) != NULL) {
        if (strncmp(pdir->d_name, ".", 1) == 0 || strcmp(pdir->d_name, "..") == 0)
            continue;

        printf("%s\n", pdir->d_name);
    }

    printf("\n");

    return 0;
}

int main(int argc, char const *argv[]){
    DIR *dir;
    if(argc < 2){
        fprintf(stderr, "Usage: %s argv[1].\n", argv[0]);
        return 1;
    }

    if ((dir = opendir(argv[1])) == NULL){
        perror("Fail to open dir.\n");
        return 1;
    }
    list(dir);
    
    return 0;
}