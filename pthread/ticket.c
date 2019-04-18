//火车站售票系统
//每一个买票的人都是一个线程,总票数为ticket

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int ticket = 100;

void *buy_ticket(void *arg)
{
    int id = (int)arg;
    while(1){
        if(ticket > 0){
            usleep(50000);
            printf("holders:%d get a ticket: %d!\n", id, ticket);
            ticket--;
        }
        else{
            printf("have no ticket! exit!\n");
            pthread_exit(NULL);
        }
    }
}

int main ()
{
    pthread_t tid[4];

    int i = 0;
    for(i = 0; i < 4; i++){
        int ret = pthread_create(&tid[i], NULL, buy_ticket, (void*)i);
        if(ret != 0){
            printf("pthread_create error");
            return -1;
        }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    return 0;
}
