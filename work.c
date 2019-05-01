#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t id = fork();
    if(id < 0){
        perror("fork");
        return -1;
    }
    else if(0 == id){ //child
        while(1){
            printf("child(%d)# I'm running!\n", getpid());
            sleep(1);
        }
    }
    else{   //parent
        int i = 5;
        while(i){
            printf("parent(%d)# I'm going to die after %ds\n", getpid(), i--);
            sleep(1);
        }
    }
    return 0;
}
