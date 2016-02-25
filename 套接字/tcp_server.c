#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sockfd;
    int n_sockfd;
    int fd;
    ssize_t num;
    char sv_buf[128];
    char rv_buf[128];
    int sin_size;
    unsigned short int portnum = 5000;  
    struct sockaddr_in sockaddr_sv, sockaddr_ct;
//1.创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        printf("creat sockfd fail!\n");
        exit(1);
    }
//2.绑定IP地址
    sockaddr_sv.sin_family = AF_INET;
    sockaddr_sv.sin_port = htons(portnum);
    sockaddr_sv.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&sockaddr_sv.sin_zero,8);

    if(-1 == bind(sockfd,(struct sockaddr *) &sockaddr_sv,sizeof(struct sockaddr)))
    {
        printf("bind port fail!\n");
        exit(1);
    }

//3.监听端口
    if(-1 == listen(sockfd,5))
    {
        printf("listen port fail!\n");
        exit(1);
    }


//4.等待连接
    sin_size = sizeof(struct sockaddr);
    n_sockfd = accept(sockfd, (struct sockaddr *)&sockaddr_ct,&sin_size);
    printf("server get connection from %s\n",inet_ntoa(sockaddr_ct.sin_addr));

//5.发送/接收数据
    while (1)
    {
        fgets(sv_buf,128,stdin);
        send(n_sockfd, sv_buf, strlen(sv_buf), 0);

        fd = fork();//创建一个进程用来接收信息
        if (0 == fd)
        {
            while(1)
            {
                num = recv(n_sockfd, rv_buf, 128, 0);
                rv_buf[num] = '\0';
                printf("%s",rv_buf);
            }
        }
    }
//6.关闭连接
    close(sockfd);
}