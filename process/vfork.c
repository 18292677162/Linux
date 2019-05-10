#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int value = 100;
int main()
{
    pid_t pid;
    if((pid = vfork()) == -1){
      perror("fork");
      exit(1);
    }
    if(pid == 0){
        //child
        sleep(1);
        value = 200;
        printf("child value = %d\n", value);
        exit(0);
    }
    else{
        //parent
        printf("parent value = %d\n", value);
    }
    return 0;
}
