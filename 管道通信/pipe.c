#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void main(void)
{
    pid_t pid;
    int pipefd[2];
    char *buffer[12];   

    pipe(pipefd);

    pid = fork();
    if(pid < 0)
        exit(errno);

    if(pid > 0)
    {
        write(pipefd[1],"\nhello,world!\n",13);
        close(pipefd[1]);
        exit(0);
    }
    else
    {
        read(pipefd[0],buffer,13);
        close(pipefd[1]);
        printf("%s",buffer);
        exit(0);
    }

}