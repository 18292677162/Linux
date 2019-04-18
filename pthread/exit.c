/*线程退出demo
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg){
    //在线程中调用exit函数: 直接退出进程，进程中的所有线程也就退出
    //exit(0);i
    
    //线程退出1: return
    //sleep(1);
    //return NULL;
    
    //线程退出2: pthread_exit
    //sleep(3);
    //pthread_exit(NULL);
    while(1){
        printf("chile pthread\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = -1;

    ret = pthread_create(&tid, NULL, thr_start, NULL);
    if(ret != 0){
        printf("pthread_create error\n");
        return -1;
    }
    //线程退出3
    //int pthread_cancel(pthread_t thread);
    //  取消线程id为thread的线程
    pthread_cancel(tid);
    while(1){
        printf("main thread\n");
        sleep(1);
    }
}
