// 发送消息进程sndfile.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MAXMSG 512

// 定义消息缓存区队列中的数据结构
struct my_msg{
    long int my_msg_type;
    char some_text[MAXMSG];
}msg;

int main(int argc, char const *argv[]){
    int msgid; // 定义消息缓冲区内部标识
    char buffer[BUFSIZ]; //用户缓冲区

    // 创建消息队列
    msgid = msgget(1234, 0666|IPC_CREAT);

    // 循环向消息队列中发送消息, 直到end
    while(1) {
        puts("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        msg.my_msg_type = 1;
        strcpy(msg.some_text, buffer);
        msgsnd(msgid, &msg, MAXMSG, 0); // 发送消息到缓冲队列

        if(strncmp(msg.some_text, "end", 3) == 0)
            break;
    }
    return 0;
}