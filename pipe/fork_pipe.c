#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fds[2];
    char buf[20];

    if(pipe(fds) == -1){
        perror("pipe error");
        exit(1);
    }
    
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        exit(1);
    }
    //child
    if(pid == 0){
      //close read
      close(fds[0]);
      write(fds[1], "hello world", 20);
      //close write
      close(fds[1]);
      exit(1);
    }
    
    //close write
    close(fds[1]);
    read(fds[0], buf, 20);
    close(fds[0]);
   
    printf("buf = %s\n", buf);
    return 0;
}
