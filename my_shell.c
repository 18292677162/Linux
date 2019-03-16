#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char *argv[8];
int argc = 0;

void get_buf(char *buf)
{
    int i;
    int status = 0;
    for(argc = i = 0; buf[i]; i++){
        if(!isspace(buf[i]) && status == 0){
            argv[argc++] = buf + i;
            status = 1;
        } else if(isspace(buf[i])){
            status = 0;
            buf[i] = 0;
        } 
    }
    argv[argc] = NULL;
}

void do_comm()
{
    pid_t pid = fork();

    switch(pid){
        case -1:
            perror("fork error");
            exit(0);
            break;
        case 0:
            execvp(argv[0], argv);
            perror("execvp error");
            exit(0);
        default:
            {
                int sstatus;
                while(wait(&sstatus) != pid)
                    ;
            }
    }   

}

int main()
{
    char buf[1024] = {};
    while(1){
        printf("myshell> ");
        scanf("%[^\n]%*c", buf);
        get_buf(buf);
        do_comm();
    }
    return 0;
}
