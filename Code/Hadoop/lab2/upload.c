/*************************************************************************
    > File Name: upload.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-05-26
 ************************************************************************/

#include <stdio.h>
#include "upload.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include "hdfs.h"

/* Map UPLOAD_BLOCK of file each time */
#define UPLOAD_BLOCK (1 << 27)

int uploadFile(const char *path){
    hdfsFS fs = hdfsConnect("default", 0);
    hdfsFile fd_w;
    int fd;
    unsigned long size, i;
    struct stat fd_s;
    char *buf_r;
    const char *filename;

    /* Get the file size */
    if ((fd = open(path, O_RDONLY)) < 0){
        perror("Open file failed");
        exit(1);
    }

    if (fstat(fd, &fd_s) < 0){
        perror("Get file stat failed");
        exit(1);
    }
    
    size = fd_s.st_size;

    /* Open the file at hdfs */
    filename = strrchr(path, '/');
    if (!filename){
        filename = path;
    }else{
        filename += 1;
    }
    
    fd_w = hdfsOpenFile(fs, filename, O_WRONLY|O_CREAT, 0, 0, 0);
    if (!fd_w){
        perror("Failed to create file to upload");
        exit(1);
    }    

    /* Write the file */
    for (i = 0; i + UPLOAD_BLOCK < size; i += UPLOAD_BLOCK){
        buf_r = (char *)mmap(NULL,\
                UPLOAD_BLOCK,\
                PROT_READ,\
                MAP_SHARED,\
                fd, i);
        if (buf_r == MAP_FAILED){
            perror("Failed to map memory");
            exit(1);
        }

        hdfsWrite(fs, fd_w, (void*)buf_r, UPLOAD_BLOCK);
        if (hdfsFlush(fs, fd_w)){
            perror("Failed to flush");
            exit(1);
        }
        
        if ((munmap(buf_r, UPLOAD_BLOCK)) < 0){
            perror("memory unmap error");
            exit(1);
        }
    }
    if (size){
        /* To avoid size == 0 */
        buf_r = (char *)mmap(NULL,\
                    size - i,\
                    PROT_READ,\
                    MAP_SHARED,\
                    fd, i);
        if (buf_r == MAP_FAILED){
            perror("Failed to map memory");
            exit(1);
        }
    
        hdfsWrite(fs, fd_w, (void*)buf_r, size - i);
        if (hdfsFlush(fs, fd_w)){
            perror("Failed to flush");
            exit(1);
        }
            
        if ((munmap(buf_r, size - i)) < 0){
            perror("memory unmap error");
            exit(1);
        }
    }
    
    /* Upload end */
    close(fd);
    hdfsCloseFile(fs, fd_w);
    hdfsDisconnect(fs);
    return 0;
}
