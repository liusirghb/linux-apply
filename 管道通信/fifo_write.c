#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
    int fd;
    char c_buf[11];

    mkfifo("/home/shunzhi/apply/lesson14/test",0666);


    fd = open("/home/shunzhi/apply/lesson14/test",O_RDONLY);
    read(fd,c_buf,12);
    printf("printf fifofile : %s\n",c_buf);
    close(fd);

    unlink("/home/shunzhi/apply/lesson14/test");
}