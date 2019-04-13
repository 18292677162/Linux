#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main()
{
    //int kill(pid_t pid, int sig);
    //  向指定进程发送指定信号（进程id， 信号编号）
    //  kill(getpid(), SIGINT);
    
    //int raise(int sig);
    //  给调用进程或线程发送信号
    //raise(SIGABRT);

    //int sigqueue(pid_t pid, int sig, const union sigval value);
    //  给指定的进程发送指定的信号，同时可以携带一个参数过去
    //union sigval {
    //  int   sival_int;
    //  void *sival_ptr;
    //};
    //sigqueue(getpid(), SIGPIPE, (union sigval)0);
    
    //alarm 定时器
    //指定seconds秒后发送一个SIGALRM信号到进程
    //unsigned int alarm(unsigned int seconds);
    //seconds == 0取消以前的定时器
    //返回值：返回上一个定时器剩余的定时时间
    //定时器每次调用会覆盖上一个定时器
    
    int ret = alarm(5);
    ret = alarm(3);
    printf("ret: %d\n", ret);
    while(1){
        printf("ABCDE\n");
        sleep(1);
    }
    return 0;
}

