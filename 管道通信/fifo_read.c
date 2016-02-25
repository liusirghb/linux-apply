#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
    int fd;
    char c_buf[11];

    mkfifo("/home/shunzhi/apply/lesson14/test",0766);

    fd = open("/home/shunzhi/apply/lesson14/test",O_WRONLY);

    if(fd<0)
        printf("mkfifo the file fail!\n");

    write(fd,"hello world",12);
    close(fd);

    unlink("/home/shunzhi/apply/lesson14/test");
}