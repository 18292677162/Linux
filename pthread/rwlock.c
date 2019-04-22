#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//写优先
/*
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
            const pthread_rwlockattr_t *restrict attr);
        成功-0      失败-错误编号
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
 */

pthread_rwlock_t rwlock;
int count = 0;

void *writer(void *arg)
{
    int i = (int)arg;
    while(1){
        pthread_rwlock_wrlock(&rwlock);
        printf("writer %d is writing, count = %d\n", i, ++count);
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
    }
}

void *reader(void *arg)
{
    int i = (int)arg;
    while(1){
        pthread_rwlock_rdlock(&rwlock);
        printf("reader %d is reading, count = %d\n", i, count);
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
    }
}

int main()
{
    int i; 
    pthread_t tid[8];

    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    //int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *attr
    //                          , int pref)
    //      attr:   读写锁属性
    //      pref:   优先级属性
    //      PTHREAD_RWLOCK_PREFER_READER_NP（默认设置）读者优先
    //      PTHREAD_RWLOCK_PREFER_WRITER_NP 
    //      PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP    写优先
    //      默认读优先
    pthread_rwlockattr_setkind_np(&attr
                , PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&rwlock, &attr);
    //      销毁属性
    //      int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
    pthread_rwlockattr_destroy(&attr);
    for(i = 0; i < 3; i++){
        pthread_create(&tid[i], NULL, writer, (void *)i);
    }
    for(i = 3; i < 8; i++){
        pthread_create(&tid[i], NULL, reader, (void *)i);
    }
    for(i = 0; i < 8; i++){
        pthread_join(tid[i], NULL);
    }
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
