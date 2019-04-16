#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid < 0){
        printf("fork error!\n");
        return 1;
    } else if(pid == 0){ //child
        printf("child running..., pid is :%d\n", getpid());
        sleep(5);
        exit(1);
    } else{ //parent
        int status = 0;
        pid_t ret = waitpid(-1, &status, 0);
        printf("waiting for child...\n");
        if (WIFEXITED(status) && ret == pid){
            printf("wait child 5s, return code: %d\n", WEXITSTATUS(status));
        } else{
            printf("wait child failed!, return code: %d\n", WEXITSTATUS(status));
            return 1;
        }
    }
    return 0;
}
