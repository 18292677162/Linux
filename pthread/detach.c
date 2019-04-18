#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* thr_start(void *arg){
    //  调用线程分离
    pthread_detach(pthread_self());
    
    int num = (int)arg;
    
    while(1){
        printf("I am thread, num: %d\n", arg);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;    
    ret = pthread_create(&tid, NULL, thr_start, (void*)123);
    if(ret != 0){
        perror("pthread_create error");
        return -1;
    }
    //int pthread_detach(pthread_t thread);
    //  分离指定线程
    //  为线程设置一个detach属性，不会阻塞
    //  pthread_detach(tid);
    printf("main thread id: %p\n", pthread_self());
    printf("pthread id: %p\n", tid);
    while(1){
        printf("--------line--------\n");
        sleep(1);
    }
    return 0;
}
