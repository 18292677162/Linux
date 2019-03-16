#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid < 0){
        printf("fork error!\n");
        return 1;
    } else if(pid == 0){ //child
        printf("child running..., pid is: %d\n", getpid());
        sleep(5);
        exit(1);
    } else{
        int status = 0;
        pid_t ret = 0;
        while(ret == 0){
            ret = waitpid(-1, &status, WNOHANG);
            if(ret == 0){
                printf("child is running, wait...\n");
                sleep(1);
            } 
        }
        if(WIFEXITED(status) && ret == pid){
            printf("wait child 5s, return code: %d\n", WEXITSTATUS(status));
        } else{
            printf("waiting failed, return code: %d\n", WEXITSTATUS(status));
            return 1;
        }
    }
    return 0;
}
