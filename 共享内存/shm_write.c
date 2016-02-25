#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TEXT_SZ 2048

struct shared_use_st 
{
    int written_by_you;
    char some_text[TEXT_SZ];
};


int main()
{
    int running = 1;
    int shmid;
    struct shared_use_st *shared_stuff;
    char buffer[TEXT_SZ];

    //1.creat share memery
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st),IPC_CREAT);
    if(shmid == -1)
    {
        printf("creat share memery fail!");
        exit(EXIT_FAILURE);
    }
    //2.associate share memmery
    shared_stuff = (struct share_use_st *)shmat(shmid,NULL,0);

    //3.circulation
    while(running)
    {
        while (shared_stuff->written_by_you == 1)//init written_by_you = 0 ,
        {                   //wait fgets input and after input written_by_you = 1.
            sleep(1);
            printf("wait read process!\n");
        }
    //3.1.get user input
        fgets(buffer,TEXT_SZ,stdin);

    //3.2.remove string to share memery
        strncpy(shared_stuff->some_text,buffer,TEXT_SZ);
        shared_stuff->written_by_you = 1;

        if (strncpy(buffer,"end",3) == 0)
            running = 0;

    }
    //4.break away from share memery
    shmdt((const void *)shared_stuff);

    return 0;
}