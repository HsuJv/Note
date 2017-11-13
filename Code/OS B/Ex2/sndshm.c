// 共享内存的发送程序sndshm.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

int main(int argc, char const *argv[]){
    int shmid; // 共享内存的内部标识
    char *viraddr; // 定义附接到共享内存的虚拟地址
    char buffer[BUFSIZ];

    // 创建共享内存
    shmid = shmget(1234, BUFSIZ, 0666|IPC_CREAT);

    // 附接到进程的虚拟地址空间
    viraddr = (char *)shmat(shmid, 0, 0);

    // 循环输入信息, 直到end
    while(1) {
        puts("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        strcat(viraddr, buffer); //追加到共享内存

        if (strncmp(buffer, "end", 3) == 0)
            break;
    }

    shmdt(viraddr); //断开链接
    return 0;
}