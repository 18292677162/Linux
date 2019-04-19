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

void *thr_producer(void *arg)
{
    while(1){
        //生产者
        sleep(1);
        printf("produce goods!!!\n");
        //int sem_post(sem_t *sem);
        //生产出资源后要通知等待在信号量上的线程/进程
        //信号量修改的是自己内部的资源计数，资源计数就是条件，而条件
        //变量修改的是外部的条件，需要我们自己来修改
        //信号量+1
        sem_post(&sem);
    }
    return NULL;
}

void *thr_consumer(void *arg)
{
    while(1){
        //消费者:没有资源则等待
        //int sem_wait(sem_t *sem);
        //阻塞等待
        //int sem_trywait(sem_t *sem);
        //非阻塞等待，无资源报错返回
        //int sem_timedwait(sem_t *sem, 
        //          struct timespec *timeout);
        //限时等待，没有资源等待指定时长，超时后报错返回
        //信号量计数器sem对应仓库的数量
        //为0等待知道信号量-1
        sem_wait(&sem);
        printf("consume goods!!!\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;
    int ret;
    //1.初始化信号量
    //int sem_init(sem_t *sem, int pshared, unsigned int value);
    //  sem：信号量变量
    //  pshared：0-线程间   非0-进程间
    //  value：信号量的初始计数
    ret = sem_init(&sem, 0, 0);
    if(ret == -1){
        printf("init sem error!\n");
        return -1;
    }

    //生产者线程
    ret = pthread_create(&tid1, NULL, thr_producer, NULL);
    if(ret != 0){
        printf("pthread_create error\n");
        return -1;
    }

    //消费者线程
    ret = pthread_create(&tid2, NULL, thr_consumer, NULL);
    if(ret != 0){
        printf("pthread_create error\n");
        return -1;
    }
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    //3.销毁信号量
    //int sem_destroy(sem_t *sem);
    sem_destroy(&sem);

    return 0;
}
