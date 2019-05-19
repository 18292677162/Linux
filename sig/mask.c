#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
    sigset_t mask;

    //int sigemptyset(sigset_t *set);
    //清空集合数据，防止出现意外
    sigemptyset(&mask);
    //int sigfillset(sigset_t *set);
    //将所有信号都添加到集合中
    //int sigaddset(sigset_t *set, int signum);
    //向集合中添加指定信号
    sigaddset(&mask, SIGINT);
    //int sigprocmask(int how, const sigset_t *set, sigset_t*oldset);
    //how: 对集合的操作
    //      SIG_BLOCK 对set集合中的信号进行阻塞oldset保留原有
    //      SIG_UNBLOCK 对set集合中的信号解除阻塞oldset忽略
    //      SIG_SETMASK 将set集合中的信号设置到blocked集合中,oldset忽略
    sigset_t oldmask;
    sigemptyset(&oldmask);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    getchar();
    //sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    while(1){
        printf("this is proc mask!\n");
        sleep(1);
        sigset_t pending;
        sigemptyset(&pending);
        //int sigpending(sigset_t *set);
        //将当前pending信号注册集合中的信号取出来放在set中
        sigpending(&pending);
        for(int i = 1; i <= 64; i++){
        //int sigismember(const sigset_t *set, int signum);
        //判断指定信号是否存在集合当中
            if(sigismember(&pending, i)){
                printf("signo: %d\n", i);
            }
        }
    }
    return 0;
}
