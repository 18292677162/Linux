#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int value = 0;

int main()
{
    pid_t pid = fork();
    if(fork() < 0){
        perror("fork");
        exit(1);
    }
    else if(fork() == 0){//child
        value = 10;
        printf("I am child: %d, value = %d, %p\n", getpid(), value, &value);
    }
    else{ //parent
        printf("I am parent: %d, value = %d, %p\n", getpid(), value, &value);
    }
    sleep(1);
    return 0;
}
