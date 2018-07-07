/*************************************************************************
    > File Name: download.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-05-26
 ************************************************************************/

#include <stdio.h>
#include "download.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "hdfs.h"

#define DOWNLOAD_BLOCK (1 << 27)

int downloadFile(const char* path){
    hdfsFS fs = hdfsConnect("default", 0);
    hdfsFile fd_r;
    int fd;
    unsigned long size, i;
    char *buf_w;
    const char* filename;
    hdfsFileInfo *fd_r_info;

    /* Create local file */
    filename = strrchr(path, '/');
    if (!filename){
        filename = path;
    }else{
        filename += 1;
    }

    fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd < 0){
        perror("Create file failed");
        exit(1);
    }

    /* Open the file at hdfs */
    fd_r = hdfsOpenFile(fs, path, O_RDONLY, 0, 0, 0);
    if (!fd_r){
        perror("Failed to open file to download");
        exit(1);
    }    

    /* Get the file size */
    fd_r_info = hdfsGetPathInfo(fs, path);
    size = fd_r_info->mSize;
    hdfsFreeFileInfo(fd_r_info, 1);

    /* Set the local file size */
    if(ftruncate(fd, size) < 0){
        perror("Don't have enough memory to store the file");
        exit(1);
    }
    lseek(fd, 0, SEEK_SET);

    /* Write the file */
    for (i = 0; i + DOWNLOAD_BLOCK < size; i += DOWNLOAD_BLOCK){
        buf_w = (char *)mmap(NULL,\
                DOWNLOAD_BLOCK,\
                PROT_WRITE|PROT_READ,\
                MAP_SHARED,\
                fd, i);

        if (buf_w == MAP_FAILED){
            perror("Failed to map memory");
            exit(1);
        }

        hdfsPread(fs, fd_r, i, (void*)buf_w, DOWNLOAD_BLOCK);
        
        if ((munmap(buf_w, DOWNLOAD_BLOCK)) < 0){
            perror("memory unmap error");
            exit(1);
        }
    }

    if (size){
        buf_w = (char *)mmap(NULL,\
                    size - i,\
                    PROT_WRITE|PROT_READ,\
                    MAP_SHARED,\
                    fd, i);

        if (buf_w == MAP_FAILED){
            perror("Failed to map memory");
            exit(1);
        }

        hdfsPread(fs, fd_r, i, (void*)buf_w, size - i);
        
        if ((munmap(buf_w, size - i)) < 0){
            perror("memory unmap error");
            exit(1);
        }
    }
    
    /* Upload end */
    close(fd);
    hdfsCloseFile(fs, fd_r);
    hdfsDisconnect(fs);
    return 0;
}

