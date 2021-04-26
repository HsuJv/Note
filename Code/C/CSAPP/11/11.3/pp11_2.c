#include <stdio.h>
#include <inttypes.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
    uint16_t hostshort;
    struct in_addr inaddr;
    char buf[BUFSIZ];

    if (argc != 2) return 1;
    
    // get the input hex
    sscanf(argv[1], "%x", &hostshort);
    // convert the input to network byte order
    inaddr.s_addr = htons(hostshort);
    // convert the network byte order to a dotted-decimal string
    if(!inet_ntop(AF_INET, &inaddr, buf, BUFSIZ))
        perror("inet_ntop");
    printf("%s\n", buf);
    return 0;
}
