#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int fd; 
    int sockfd;
    int n_sockfd;
    ssize_t num = 0;
    char ct_buf[128];
    char st_buf[128];
    //int sin_size;
    unsigned short int portnum = 5000;
    struct sockaddr_in sockaddr_sv;
//1.创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        printf("creat sockfd is fail!");
    }
//2.等待连接
    sockaddr_sv.sin_family = AF_INET;
    sockaddr_sv.sin_port = htons(portnum);
    sockaddr_sv.sin_addr.s_addr = inet_addr("192.168.1.100");
    bzero(&sockaddr_sv.sin_zero,8);
    connect(sockfd,(struct sockaddr *)&sockaddr_sv,sizeof(struct sockaddr));
    while (1)
    {
        num = recv(sockfd, ct_buf, 128, 0);
        ct_buf[num] = '\0';
        printf("%s",ct_buf);

        fd = fork();//创建一个进程用来发送信息
        if (0 == fd)
        {
            while(1)
            {
                fgets(st_buf,128,stdin);
                send(sockfd, st_buf, strlen(st_buf), 0);
            }
        }
    }   
//3.关闭连接
    close(sockfd);
}