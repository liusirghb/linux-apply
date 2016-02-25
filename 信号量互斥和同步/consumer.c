#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
     key_t key;
     int semid;
     int ret;
     struct sembuf sops;

     key = ftok("home",1);//创建一个键值

     semid = semget(key,1,IPC_CREAT);//获取信号量
               //IPC_CREAT命令如果键值不存在就创建

     /*法一：通过轮寻查看信号量是否释放
     ret = semctl(semid,0,GETVAL);    
     printf("%d\n",ret);
     while(!(ret))
     ret = semctl(semid,0,GETVAL);     */

     //法二：采用信号量机制
     sops.sem_num = 0;//要操作的信号量序号
     sops.sem_op = -1;//设置为自减1
     sops.sem_flg = SEM_UNDO;//要操作的信号量序号
     semop(semid,&sops,1);//执行操作

     system("cp ./pro.txt ./temp");
}