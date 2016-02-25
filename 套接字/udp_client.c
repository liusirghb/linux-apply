#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT 2222

int sockfd;
int n;
int ADDRLEN;
struct sockaddr_in server_addr;
char buffer[128];
pthread_t thread[2];

//3.1 send data to server 
void *send_ms()
{ 
    ADDRLEN = sizeof(struct sockaddr);
    fgets(buffer,128,stdin);
    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
    bzero(buffer,128);
}

//3.2 recieve data from server
void *recv_ms()
{
    n = recvfrom(sockfd,buffer,128,0,(struct sockaddr *)(&server_addr),&ADDRLEN);
    buffer[n] = 0;
    printf("%s",buffer);
    bzero(buffer,128);
}

int main(int argc,char **argv)
{
    if(argc != 2)
    {
        printf("Usage : %s server_ip\n",argv[0]);
        exit(1);
    }

//1.creat socket
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd == -1)
    {
        printf("creat socket error!\n");
        exit(1);
    }

//2 set connect server
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_aton(argv[1],&server_addr.sin_addr);

//3.recieve and send
    while (1)
    {
        pthread_create(&thread[0],NULL,send_ms,NULL);
        pthread_create(&thread[1],NULL,recv_ms,NULL);
    }

//4.over connect
    close(sockfd);

    return 0;
}