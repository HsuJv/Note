// 消息队列机制的接收程序rcvfile.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MAXMSG 512

struct my_msg{
    long int my_msg_type;
    char some_text[MAXMSG];
}msg;

int main(int argc, char const *argv[]){
    int msgid;
    long int msg_to_receive = 0;

    msgid = msgget(1234, 0666|IPC_CREAT);

    while(1) {
        msgrcv(msgid, &msg, BUFSIZ, msg_to_receive, 0);
        printf("%s%s\n", "You wrote: ", msg.some_text);

        if(strncmp(msg.some_text, "end", 3) == 0)
            break;
    }
    return 0;
}