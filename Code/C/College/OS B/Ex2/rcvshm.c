// 共享内存的接收进程程序rcvshm.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

int main(int argc, char const *argv[]){
    int shmid;
    char *viraddr;

    // 获取共享内存
    shmid = shmget(1234, BUFSIZ, 0666|IPC_CREAT);

    // 附接到进程的虚拟地址空间
    viraddr = (char *)shmat(shmid, 0, 0);

    // 打印信息内容
    printf("%s%s\n", "your message is: ", viraddr);

    // 断开链接
    shmdt(viraddr);

    // 撤销共享内存
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}