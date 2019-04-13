#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define ERROR_EXIT(m) do {perror(m); exit(EXIT_FAILURE);} while(0)

int main()
{
    int wfd = open("mypipe", O_WRONLY);
    if(wfd < 0){
        ERROR_EXIT("open");
    }

    char buf[1024];
    while(1){
        buf[0] = 0;
        printf("Plese Enter# ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf)-1);
        if(s > 0){
            buf[s] = 0;
            write(wfd, buf, strlen(buf));
        } else if(s <= 0){
            ERROR_EXIT("read");
        }
    }

    close(wfd);
    return 0;
}

