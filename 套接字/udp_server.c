#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT 2222

static int sockfd;
static struct sockaddr_in server_addr;
static struct sockaddr_in client_addr;
static char buffer[128];
static int n;
static int ADDRLEN;
static pthread_t thread[2];

//3.1 recieve data from client
void * recv_ms()
{
    ADDRLEN = sizeof(struct sockaddr);
    bzero(buffer,128);
    n = recvfrom(sockfd,buffer,128,0,(struct sockaddr *)(&client_addr),&ADDRLEN);
    buffer[n] = 0;
    printf("%s",buffer);
    bzero(buffer,128);
}

//3.2 sent data to client
void * send_ms()
{
    fgets(buffer,128,stdin); 
    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&client_addr,sizeof(struct sockaddr));
    bzero(buffer,128);
}

int main()
{
//1.creat sockfd
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd == -1)
    {
        printf("creat socket error!\n");
        exit(1);
    }

//2.1 set bind addr
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

//2.2 bind addr
    bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));

//3 recieve and send
    while(1)
    {
        pthread_create(&thread[0],NULL,recv_ms,NULL);
        pthread_create(&thread[1],NULL,send_ms,NULL);
    }

//4.over connect
    close(sockfd);

    return 0;
}