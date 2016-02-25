#include <pthread.h>
#include <stdio.h>

pthread_t thread[2];

int number = 0;
pthread_mutex_t mut;

void * worker1()
{
     int i = 0;

     printf("I am worker1!\n");

     for (i = 0;i < 10;i++)
     {
          pthread_mutex_lock(&mut);

          number++;

          pthread_mutex_unlock(&mut);

          printf("worker1 number %d\n",number);

          sleep(1);
     }

     pthread_exit(NULL);
}

void * worker2()
{
    int i = 0;

    printf("I am worker2!\n");

    for (i = 0;i < 10;i++)
    {
        pthread_mutex_lock(&mut);

        number++;

        pthread_mutex_unlock(&mut);

        printf("worker2 number %d\n",number);

        sleep(1);
    }

    pthread_exit(NULL);

}

int main()
{

     pthread_mutex_init(&mut,NULL);
//1.creat worker1 thread
     pthread_create(&thread[0],NULL,worker1,NULL);

//2.creat worker2 thread
     pthread_create(&thread[1],NULL,worker2,NULL);

//3.wait worker1 thread over
     pthread_join(thread[0],NULL);

//4.wait worker2 thread over
     pthread_join(thread[1],NULL);

     return 0;
}