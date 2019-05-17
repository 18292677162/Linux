#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define ERROR_EXIT(n) do{perror(n); exit(EXIT_FAILURE);} while(0)

int main()
{
    int outfd = open("fifo_test.bak", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(outfd == -1){
        ERROR_EXIT("open");
    }
    
    int infd = open("tp", O_RDONLY);
    if(infd == -1){
        ERROR_EXIT("open");
    }

    char buf[1024];
    int n;
    while((n = read(infd, buf, 1024)) > 0){
        write(outfd, buf, n);
    }
    close(infd);
    close(outfd);
    unlink("tp");
    return 0;
}
