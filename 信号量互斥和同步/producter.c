#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
     int fd;
     key_t key;    
     int semid;
     struct sembuf sops;

     //创建一个键值
     key = ftok("home",1);

     //创建一个信号量
     semid = semget(key,1,IPC_CREAT);

     semctl(semid,0,SETVAL,0);

     fd = open("./pro.txt",O_RDWR|O_CREAT|O_APPEND,0777);

     sleep(15);

     write(fd,"welcome,linux!",14);

     //释放信号量
     sops.sem_num = 0;
     sops.sem_op = 1;
     sops.sem_flg = SEM_UNDO;
     semop(semid,&sops,1);

     close(fd);
}