#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
    pthread_rwlock_init(&rwlock, NULL);
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
