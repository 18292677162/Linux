#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* thr_start(void *arg){
    int num = (int)arg;

    while(1){
        printf("I am thread, num: %d\n", arg);
        sleep(1);
    }
    return NULL;
}

int main()
{
    //线程创建（创建用户线程）
    //int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    //                void *(*start_routine) (void *), void *arg);
    //  thread: 用于接收一个用户线程ID
    //  attr:   用于设置线程属性，一般置NULL
    //  start_routine: 线程的入口函数
    //      线程运行的就是这个函数，这个函数退出了，线程就退出了
    //  arg:    用于给线程入口函数传递参数
    //  返回值:0-成功       errno-失败
    pthread_t tid;
    int ret;    //线程属性
    ret = pthread_create(&tid, NULL, thr_start, (void*)123);
    if(ret != 0){
        perror("pthread_create error");
        return -1;
    }
    //pthread_t pthread_self(void);
    //  获取调用线程的线程id（用户态线程id）
    printf("main thread id: %p\n", pthread_self());
    printf("pthread id: %p\n", tid);
    while(1){
        printf("--------line--------\n");
        sleep(1);
    }
    return 0;
}
