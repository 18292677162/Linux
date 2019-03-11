#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    printf("pid = %d\n",getpid());
    if((pid = fork()) == -1)perror("fork()"),exit(1);
    if(pid == 0){
        //child
        printf("child hello,pid = %d",getpid());
        exit(0);
    }
    else{
        //prent \n=flash tmp
        printf("prent hello,pid = %d", getpid());
        _exit(0);
    }
    return 0;
}
