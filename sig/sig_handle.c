/*信号处理方式测试
 *  1.默认处理方式
 *  2.忽略处理方式
 *  3.自定义处理方式
 *
 */
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("recv signo: %d\n", signo);
    sleep(5);
}

int main()
{   
    //2.信号的忽略处理
    //sighandler_t signal(int signum, sighandler_t handler);
    //  用于修改一个信号的处理方式
    //  signum: 用于指定修改哪个信号的处理方式
    //  handler: 用于指定处理方式(函数)
    //      SIG_IGN 忽略处理
    //      SIG_DFL 默认处理
    //signal(SIGINT, SIG_IGN);
    //getchar();
    //signal(SIGINT, SIG_DFL);
    //
    //3.信号的自定义处理
    //  sigcb是用户自定义的信号处理方式
    //  void sigcb(int signo)
    //signal(SIGINT, sigcb);
    /*
        int sigaction(int signum, const struct sigaction *act,
                        struct sigaction *oldact);i
        signum: 指定修改哪一个信号的处理动作
        act:    给指定信号指定的处理动作
        odlact: 用于保存信号原来的处理动作
        struct sigaction {
        //自定义处理方式，不能接收参数
        void (*sa_handler)(int);
        //自定义处理方式，可以接收信号携带参数
        void (*sa_sigaction)(int, siginfo_t *, void *);
        //处理信号时不希望处理过程被其他信号打扰，用于处理信号时阻塞某些信号
        sigset_t sa_mask;
        //决定哪个成员函数作为信号处理接口
        //0-sa_handler  SA_SIGINFO-sa_sigaction
        int sa_flags;
        void (*sa_restorer)(void);
    };
    */
    struct sigaction new_act, old_act;
    sigemptyset(&new_act.sa_mask);
    //在处理信号期间不希望受到SIGQUIT影响，因此通过sa_mask将SIGQUIT阻塞
    sigaddset(&new_act.sa_mask, SIGQUIT);
    new_act.sa_handler = sigcb;
    new_act.sa_flags = 0;
    
    sigaction(SIGINT, &new_act, &old_act);

    while(1){
        printf("hello world\n");
        sleep(1);
    }
    return 0;
}

