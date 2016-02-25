#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

    //1.creat share memery
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st),IPC_CREAT);
    if(shmid == -1)
    {
        printf("creat share memery fail!");
        exit(EXIT_FAILURE);
    }
    //2.map share memery
    shared_stuff = (struct share_use_st *)shmat(shmid,NULL,0);

    //3.loop print share memery
    while (running)
    {   
        if (shared_stuff->written_by_you == 1)//init written_by_you = 0
        {
            printf("write process write %s\n",shared_stuff->some_text);
            shared_stuff->written_by_you = 0;

            if (strncpy(shared_stuff->some_text,"end",3) == 0)
                running = 0;
        }
    }


    //4.break away from share memery
    shmdt((const void *)shared_stuff);
    //5.delete share memery
    shmctl(shmid,IPC_RMID,0);

    return 1;
}