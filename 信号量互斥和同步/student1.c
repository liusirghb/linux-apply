#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>

void main()
{
    int fd;
    key_t key;
    int semid;
    int ret;
    struct sembuf sops;

    key = ftok("/home",1);//创建键值

    semid = semget(key,1,IPC_CREAT);//创建并打开信号量集合
    semctl(semid,0,SETVAL,1);//设置信号量的值为1

    fd = open("./board.txt",O_RDWR|O_APPEND);//打开文件

    sops.sem_num = 0;//要设置的信号量
    sops.sem_op =  -1;//执行-1操作
    semop(semid,&sops,1);//获取信号量

    ret = semctl(semid,0,GETVAL);//获取信号量的值
    printf("The semval is %d\n",ret);

    write(fd,"class math",10);//写入字符
    sleep(10);//休息
    write(fd," is cancel",9);//再次写入

    sops.sem_num = 0;
    sops.sem_op = 1;//执行加一操作
    semop(semid,&sops,1);//释放信号量

    close(fd);
}