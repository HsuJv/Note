#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    char command[50] = "gnome-terminal && kill -s 9 ";
    char ppid[8];

    if(argc < 2){
        fprintf(stderr, "Usage: %s argv[1].\n", argv[0]);
        return 1;
    }

    if (opendir(argv[1]) == NULL){
        perror("Fail to open dir.\n");
        return 1;
    }

    chdir(argv[1]);
    sprintf(ppid, "%d", getppid()); 
    strcat(command, ppid);
    system(command);
    return 0;
}