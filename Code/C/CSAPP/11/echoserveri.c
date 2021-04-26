#include "openfd.h"
#include <stdio.h>

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;    
    struct sockaddr_storage clientaddr;
    char client_hostname[BUFSIZ], client_port[BUFSIZ];
    char buf[BUFSIZ];

    if (argc != 2) return 1;

    listenfd = open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        getnameinfo((struct sockaddr*)&clientaddr, clientlen, client_hostname, BUFSIZ, client_port, BUFSIZ, 0);
        printf("Connected to (%s %s)\n", client_hostname, client_port);
        do{
            memset(buf, 0, BUFSIZ);
            read(connfd, buf, BUFSIZ);
            fputs(buf, stdout);
            write(connfd, "success\n\0", 9);
        }while(1);
        close(connfd);
    }
    return 0;
}

