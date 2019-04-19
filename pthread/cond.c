//生产者消费者同步代码
//仓库里有资源
//  消费者获取资源，通知生产者资源被取走
//  生产者等待
//仓库里无资源
//  消费者等待
//  生产者生产资源，通知消费者已有资源

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
    int pthread_cond_init(pthread_cond_t *restrict cond,const pthread_condattr_t *restrict attr);
    int pthread_cond_destroy(pthread_cond_t *cond);
    int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
    int pthread_cond_broadcast(pthread_cond_t *cond);
    int pthread_cond_signal(pthread_cond_t *cond);
 */

//定义条件变量
//      1.定义赋值初始化，无需释放
//      2.函数接口初始化，需要释放
//      pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond;
pthread_mutex_t mutex;
int goods = 0;

void *producer(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
        if(0 == goods){
            sleep(1);
            printf("product a goods!!!\n");
            goods = 1;
            //int pthread_cond_broadcast(pthread_cond_t *cond);
            //  唤醒所有等待在条件变量上的线程
            //int pthread_cond_signal(pthread_cond_t *cond);
            //  唤醒第一个等待在条件变量上的线程
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
        if(0 == goods){
            //没有资源阻塞等待
            //int pthread_cond_wait(pthread_cond_t *cond,
            //              pthread_mutex_t *mutex);
            //  条件变量和互斥锁搭配使用
            //  先判断互斥锁是否加锁，如果加锁就解锁陷入等待（原子操作）
            //  为了防止：没有货物，消费者先于生产者拿到锁，生产者拿
            //  不到锁无法生产，会死锁
            //  如果消费者先拿到锁，等待之前要解锁，解锁的目的是为了保证
            //  全局条件的操作是受保护的
            pthread_cond_wait(&cond, &mutex);
        }
        sleep(1);
        printf("consume a goods!!!\n");
        goods = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{ 
    pthread_t tid1, tid2;
    int ret;
    //1.条件变量初始化
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    ret = pthread_create(&tid1, NULL, producer, NULL);
    if(ret != 0){
        printf("pthread_create error\n");
        return -1;
    }
    ret = pthread_create(&tid2, NULL, consumer, NULL);
    if(ret != 0){
        printf("pthread_create error\n");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    //2.条件变量销毁
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
