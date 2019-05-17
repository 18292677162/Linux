#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int pipe_fd[2];
    char buf[10];
    if(pipe(pipe_fd) == -1){
        perror("pipe error");
        exit(1);
    }
    
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        close(pipe_fd[0]);
        write(pipe_fd[1], "hello", 5);
        close(pipe_fd[1]);
        exit(1);
    }
    close(pipe_fd[1]);
    read(pipe_fd[0], buf, 10);
    
    printf("buf = %s\n", buf);
    return 0;
}
