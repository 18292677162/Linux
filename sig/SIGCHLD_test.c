#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    pid_t cid;
    while((cid = waitpid(-1, NULL, WNOHANG)) > 0){
        printf("waiting child success: %d\n", cid);
    }
    printf("child is quit! %d\n", getpid);
}

int main()
{
    signal(SIGCHLD, handler);
    pid_t pid;
    if((pid = fork()) == 0){ //child
        printf("child: %d\n", getpid());
        sleep(3);
        exit(1);
    }
    
    while(1){
        printf("parent proc is busying!\n");
        sleep(1);
    }
    return 0;
}
