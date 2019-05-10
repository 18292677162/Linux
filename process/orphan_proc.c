#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(1);
    }
    else if(pid == 0){
        printf("I am child, pid is %d\n", getpid());
        sleep(10);
    }
    else{
        printf("I am parent, pid is %d\n", getpid());
        sleep(5);
        exit(0);
    }
    return 0;
}
