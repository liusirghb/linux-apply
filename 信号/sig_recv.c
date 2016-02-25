#include <unistd.h>
#include <signal.h>

void myfunc(int a)
{
    printf("process B recieve SIGINT\n");
}

void main()
{

    signal(SIGINT,myfunc);

    pause();

}