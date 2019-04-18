/*线程等待demo
 * 
 * int pthread_join(pthread_t thread, void **retval); 
 * 线程有一个属性: joinable
 *   如果线程属性是joinable状态，代表这个线程退出后需要被别人等待
 *   一个线程只有joinable才能被等待（获取线程返回值，释放线程资源）
 *   一个线程创建出来后默认熟悉就是joinable状态
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *thr_start(void *arg)
{
    sleep(5);
    return "I am thread";
}

int main()
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if(ret != 0){
        printf("pthread_create error\n");
        return -1;
    }
    //int pthread_join(pthread_t thread, void **retval);
    //  等待指定的线程并获取返回值
    //  thread:  用于指定等待哪个线程
    //  retval:  用于接收线程返回值
    //  如果调用join函数的时候线程已经退出了，那么将直接退出，否则阻塞等待直到退出
    char *ptr;
    pthread_join(tid, (void **)&ptr);   //强转二级指针取地址
    printf("child thread say: %s\n", ptr);   //指针
    return 0;
}

