#include <sys/types.h>
#include <signal.h>
#include  <stdio.h>

void main(int argc,char *argv[])
{
    pid_t pid;

    pid = atoi(argv[1]);

    kill(pid,SIGINT);

}