#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#define LISTENQ 1024

int open_clientfd(char *hostname, char* port){
        int clientfd;
        struct addrinfo hints, *listp, *p;
        
        /* Get a list of potential server address */
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_socktype = SOCK_STREAM; /* connection only */
        hints.ai_flags = AI_NUMERICSERV; /* numeric port only */
        hints.ai_flags |= AI_ADDRCONFIG; /* Recommended for connectio
n*/
        
        getaddrinfo(hostname, port, &hints, &listp);


        /* Walk the list for one that we can successfully connect to 
*/ 
        for(p = listp; p; p = p->ai_next){
                /* Create a socket descriptor */
                if((clientfd = socket(p->ai_family, p->ai_socktype, p
->ai_protocol)) < 0)
                        continue;
                /* Connect to the server */
        if(connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break; // Success
        close(clientfd);
    }   
    
    /* Clean up */
    freeaddrinfo(listp);
    if(!p) /* All connection failed */
        return -1;
    return clientfd;
}

int open_listenfd(char *port){
    struct addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; /* Accept connections */
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; /* on any IP address */
        hints.ai_flags |= AI_NUMERICSERV; /* numeric port only */
    
    getaddrinfo(NULL, port, &hints, &listp);    

    /* Walk the list for one that we can bind to */
    for (p = listp; p; p = p->ai_next){
        /* Create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
        /* Eliminates "Address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

        /* Bind the descriptor to the address */
        if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;
        close(listenfd);
    }

    /* Clean up */
    freeaddrinfo(listp);
    if(!p) /* No address worked */ 
        return -1;
    /* Make it a listenning socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0){
        close(listenfd);
        return -1;
    }
    return listenfd;
}
