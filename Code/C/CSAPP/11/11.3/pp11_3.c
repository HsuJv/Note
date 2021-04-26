#include <stdio.h>
#include <inttypes.h>
#include <arpa/inet.h>


int main(int argc, char* argv[]){
    struct in_addr inaddr;
    
    if (argc != 2) return 1;
    // get the input and convert it to a network byte order
    if (inet_pton(AF_INET, argv[1], &inaddr) <= 0){
        perror("inet_pton");
    }
    // convert the network byte order to host byte order
    fprintf(stderr,"0x%x\n", ntohs(inaddr.s_addr));
    return 0;
}
