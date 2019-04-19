//信号量实现同步互斥
//  1.信号量初始化
//  2.信号量操作（等待/通知）
//  3.信号量的释放
//  
//  同步：等待与通知

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

sem_t sem;
int ticket = 100;

void *buy_ticket(void *arg)
{
    int id = (int)arg;
    while(1){
        //为0等待直到信号量-1
        //信号量计数器最大是1所以只有一个线程能获取到信号量
        //，保证了同一时间只有一个线程能操作
        sem_wait(&sem);
        if(ticket > 0){
            usleep(10000);
            ticket--;
            printf("scalper %d buy a ticket: %d\n", id, ticket);
        }
        //操作完毕信号量计数器+1，信号量资源可以获取
        //又进行新一轮的资源争抢
        sem_post(&sem);
    }
    return NULL;
}

int main()
{
    //买票
    int ret;
    pthread_t tid;
    ret = sem_init(&sem, 0, 1);
    if(ret == -1){
        printf("init sem error!\n");
        return -1;
    }
    int i = 0;
    for(i = 0; i < 4; i++){
        ret = pthread_create(&tid, NULL, buy_ticket, (void *)i);
        if(ret != 0){
            printf("pthread_create error\n");
            return -1;
        }    
    }
    pthread_join(tid, NULL);
    sem_destroy(&sem);
    return 0;
}
