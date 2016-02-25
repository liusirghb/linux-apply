#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
    int fd;
    key_t key;
    int semid;
    int ret;
    struct sembuf sops;

    key = ftok("/home",1);//指定键值
    semid = semget(key,1,IPC_CREAT);//创建信号量
    ret = semctl(semid,0,GETVAL);//获取信号量的值
    printf("The semval is %d\n",ret);

    fd = open("./board.txt",O_RDWR|O_APPEND);//打开文件

    sops.sem_num = 0;
    sops.sem_op =- 1;
    semop(semid,&sops,1);//获取信号量

    write(fd," class English is test",21);//写入字符

    sops.sem_num = 0;
    sops.sem_op =+ 1;
    semop(semid,&sops,1);//释放信号量
    ret = semctl(semid,0,GETVAL);//获取信号量的值
    printf("The semval is %d\n",ret);

    close(fd);

}