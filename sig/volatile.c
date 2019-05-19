#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>

volatile uint64_t a = 1;
//无符号64位整型

void sigcb(int so)
{
    printf("recv so: %d\n", so);
    a = 0;
}

int main()
{
    signal(SIGINT, sigcb);
    while(a)
    {}
    return 0;
}
