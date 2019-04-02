#include "comm.h"

int main()
{
    int semid = createSemSet(1);
    initSem(semid, 0 ,1);
    pid_t id = fork();
    if(id < 0){
        perror("fork");
        return -1;
    } else if(id == 0){ //child
        int _semid = getSemSet(0);
        while(1){
            P(_semid, 0);
            printf("A");
            fflush(stdout);
            usleep(200000);
            printf("A ");
            fflush(stdout);
            usleep(400000);
            V(_semid, 0);
        }
    } else{ //parent
        while(1){
            P(semid, 0);
            printf("B");
            fflush(stdout);
            usleep(300000);
            printf("B ");
            fflush(stdout);
            usleep(100000);
            V(semid, 0);
        }
        wait(NULL);
    }
    destroySemSet(semid);
    return 0;
}



