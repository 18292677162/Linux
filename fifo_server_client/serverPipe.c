#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define ERROR_EXIT(m) do {perror(m); exit(EXIT_FAILURE);} while(0)

int main()
{
    umask(0);
    if(mkfifo("mypipe", 0644) < 0){
        ERROR_EXIT("mkfifo");
    }
    int rfd = open("mypipe", O_RDONLY);
    if(rfd < 0){
        ERROR_EXIT("open");
    }

    char buf[1024];
    while(1){
        buf[0] = 0;
        printf("Please wait...\n");
        ssize_t s = read(rfd, buf, sizeof(buf)-1);
        if(s > 0){
            buf[s-1] = 0;
            printf("client say# %s\n", buf);
        } else if(s == 0){
            printf("client quit, exit now!\n");
            exit(EXIT_SUCCESS);
        } else{
            ERROR_EXIT("read");
        }
    }

    close(rfd);
    return 0;
}

