/*
fileoper.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    int fd0, record_len, buff_len, cnt;
    char filename[50], f_buff[2000];

    /*
    打开当前目录下的一个文件example.txt, 确保存在
     */
    strcpy(filename, "./example.txt");
    fd0 = open(filename, O_RDWR|O_CREAT, 0644); // 打开文件

    if (fd0 < 0){
        printf("%s\n", "Can't create example.txt file!");
        exit(0);
    }

    buff_len = 20;
    record_len = 10;

    lseek(fd0, 0, SEEK_SET);

    /*
    读文件, 长度为record_len * buff_len的内容写到f_buff中
     */
    cnt = read(fd0, f_buff, record_len * buff_len);
    cnt = cnt / record_len;
    printf("%s\n", f_buff);

    strcpy(f_buff, "1234567890"); //设置要写入的文件的信息
    write(fd0, f_buff, strlen(f_buff));
    write(fd0, "\n", 1);
    close(fd0);

    return 0;
}