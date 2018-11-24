/*************************************************************************
    > File Name: fs.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-05-27
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hdfs.h"
#include "fs.h"

int dfsList(const char* path){
    hdfsFS fs = hdfsConnect("default", 0);
    int i, entries;
    hdfsFileInfo *files, *head;

    /* Get the list info */
    files = hdfsListDirectory(fs, path, &entries);
    if (!files){
        perror("Get directory info");
        exit(-1);
    }
    head = files;

    /* Print the info */
    fprintf(stdout, "%s %-50s %-9s %s\n",
            "Kind", "Name", "Size", "Replicas");

    for (i = 0; i < entries; i++){
        const char* unit[] = {" B", "KB", "MB", "GB", "TB", "PB"};
        double size = files->mSize;
        unsigned int u = 0;

        while (size > 1024){
            u++;
            size /= 1024;
        }

        assert(u < 6);

        fprintf(stdout, "%4c %-50s %-7.2lf%s %8d\n", 
                files->mKind, files->mName,
                size, unit[u],
                files->mReplication);

        files += 1;
    }

    /* List ends */
    hdfsFreeFileInfo(head, entries);
    hdfsDisconnect(fs);
    
    return 0;
}

int dfsRemove(const char* path){
    hdfsFS fs = hdfsConnect("default", 0);

    if (hdfsDelete(fs, path, 1) < 0){
        perror("Delete error");
        exit(-1);
    }

    /* Remove ends */
    hdfsDisconnect(fs);

    return 0;
}
