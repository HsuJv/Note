/*************************************************************************
    > File Name: app.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-05-26
 ************************************************************************/

#include "hdfs.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "upload.h"
#include "download.h"
#include "fs.h"
#include <fcntl.h>

void helpInfo(){
    fprintf(stdout, "Usage:demo [(-u|upload) filename]\n");
    fprintf(stdout, "           [(-d|download) filename]\n");
    fprintf(stdout, "           [(-l|list) path]\n");
    fprintf(stdout, "           [(-r|remove) filename]\n");
}

int getOption(const char* options[], const char *op){
    unsigned int i;
    
    for (i = 0; options[i]; i++){
        if (!strcmp(options[i], op)) return i;
    }
    
    fprintf(stdout, "unknown option %s\n", op);
    helpInfo();
    exit(0);
}

int main(int argc, char* argv[]){
    const char* options[] = {"-u", "upload", "-d", "download", \
        "-h", "help", "-l", "list", "-r", "remove", 0};
    int op;

    if (argc != 3 && argc != 2){
        helpInfo();
        return 0;
    }
    
    op = getOption(options, argv[1]);
    switch(op){
        case 0:
        case 1:
            if (argc == 2){
                fprintf(stdout, "Please input the filename!\n");
                exit(0);
            }
            if (access(argv[2], R_OK)){
                fprintf(stdout, "File '%s' not exists,\n", argv[2]);
                fprintf(stdout, "Or permession denied.\n");
                fprintf(stdout, "Please check the filename.\n");
                exit(0);
            }
            if(!uploadFile(argv[2]))
                fprintf(stdout, "Upload %s success\n", argv[2]);
            break;
        case 2:
        case 3:
            if (argc == 2){
                fprintf(stdout, "Please input the filename!\n");
                exit(0);
            }
            if(!downloadFile(argv[2]))
               fprintf(stdout, "Downloadload %s success\n", argv[2]);
            break;
        case 4:
        case 5:
            helpInfo();
            break;
        case 6:
        case 7:
            if (argc == 2){
                fprintf(stdout, "Please input the filename!\n");
                exit(0);
            }
            dfsList(argv[2]);
            break;
        case 8:
        case 9:
            if (argc == 2){
                fprintf(stdout, "Please input the filename!\n");
                exit(0);
            }
            if (!dfsRemove(argv[2]))
                fprintf(stdout, "Delete %s success\n", argv[2]);
            break;
        default:
            exit(-1);
    }
    exit(0);
}
