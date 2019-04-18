//火车站售票系统
//每一个买票的人都是一个线程,总票数为ticket

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int ticket = 100;
//互斥锁初始化：
//  1.定义时直接赋值初始化，最后不需要手动释放
//  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//  2.函数接口初始化，最后需要手动释放
//
pthread_mutex_t mutex;

void *buy_ticket(void *arg)
{
    int id = (int)arg;
    while(1){
        //2.加锁操作
        //  int pthread_mutex_lock(pthread_mutex_t *mutex);
        //      阻塞加锁，如果获取不到锁则阻塞等待解锁
        //  int pthread_mutex_trylock(pthread_mutex_t *mutex);
        //      非阻塞加锁，如果获取不到锁立即报错返回EBUSY(锁忙)
        //  int pthread_mutex_timedlock (pthread_mutex_t *mutex,
        //              struct timespec *t);
        //      限时阻塞加锁，如果获取不到锁则等待指定时间，
        //      这段时间如果一直获取不到锁，报错返回，否则加锁

        pthread_mutex_lock(&mutex);
        if(ticket > 0){
            usleep(50000);
            printf("holders:%d get a ticket: %d!\n", id, ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);
        }
        else{
            printf("have no ticket! exit!\n");
            //加锁后在任意有可能退出的地方都要解锁
            //否则会导致其他线程阻塞卡死
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        //3.解锁
        //int pthread_mutex_unlock(pthread_mutex_t *mutex);
        pthread_mutex_unlock(&mutex);
    }
}

int main ()
{
    pthread_t tid[4];
    
    //1.int pthread_mutex_init(pthread_mutex_t *restrict mutex,
    //              const pthread_mutexattr_t *restrict attr);
    //  互斥锁的初始化
    //      mutex:  互斥锁变量
    //      attr:   互斥锁的属性，NULL
    //      返回值: 0 成功      errno 错误
    pthread_mutex_init(&mutex, NULL);

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
    //4.销毁互斥锁
    //int pthread_mutex_destroy(pthread_mutex_t *mutex);
    pthread_mutex_destroy(&mutex);
    return 0;
}
