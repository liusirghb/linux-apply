#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    pid_t pid;
    int i,fd;
    int flag = 1;
    char buffer[] = "I am daemon!";

//1.create a son process
    pid = fork();
    if (pid < 0)
    {
        printf("create son process fail!\n");
        exit(1);
    }

    if (pid > 0)
        exit(1);

//2.take away from terminal
    setsid();

//3.1.change work diractory
    chdir("/");

//3.2.clean mask
    umask(0);

//3.3.close had open file
    for(i = 0;i < 65535;i++)
        close(i);

//4.guard process work content
    while (1)
    {
        if((flag == 1) && (fd = open("/tmp/daemon.log",O_CREAT|O_WRONLY|O_APPEND,0600)))
        {
            printf("open file fail!/n");
            flag = 0;
            exit(1);
        }

        write(fd,buffer,strlen(buffer));
        close(fd);
        sleep(1);
    }

    return 0;
}