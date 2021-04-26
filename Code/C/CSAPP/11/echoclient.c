#include "openfd.h"
#include <stdio.h>


int main (int argc, char **argv){
    int clientfd;
    char *host, *port, buf[BUFSIZ];

    if (argc != 3) return(1);

    host = argv[1];
    port = argv[2];

    clientfd = open_clientfd(host, port);

    while(fgets(buf, BUFSIZ, stdin) != NULL){
        write(clientfd, buf, strlen(buf));
        read(clientfd, buf, BUFSIZ);
        fputs(buf, stdout);
        memset(buf, 0, BUFSIZ);
    }
    close(clientfd);
    return 0;
}
