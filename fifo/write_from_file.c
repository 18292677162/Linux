#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define ERROR_EXIT(n) do {perror(n); exit(EXIT_FAILURE);} while(0);

int main()
{
    mkfifo("tp", 0644);
    int infd = open("fifo_test", O_RDONLY);
    if(infd == -1){
        ERROR_EXIT("open");
    }

    int outfd = open("tp", O_WRONLY);
    if(outfd == -1){
        ERROR_EXIT("open");
    }
    
    char buf[1024];
    int n;
    while((n = read(infd, buf, 1024)) > 0){
        write(outfd, buf, n);
    }
    close(infd);
    close(outfd);
    return 0;
}
