#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

void mydaemon()
{ 
  int i;
  int fd0;
  pid_t pid;

  //1.将文件模式创建屏蔽字设置为0
  umask(0);
  //2.fork，退出父进程，让shell认为命令已执行完毕，将进程退出终端，
  //fork后子进程不是一个进程组的组长，否则父进程无法调用setsid()
  if((pid = fork()) < 0){
    perror("fork");
    return;
  }else if(pid > 0){
    exit(0);  //终止父进程
  }else{
    //3.setsid创建新会话
    setsid();

    //4.忽略SIGCHLD信号
    signal(SIGCHLD, SIG_IGN);

    //二次fork，终止父进程，保证子进程不是会话首进程，
    //保证后续不会和其他终端相关联
    if((pid = fork()) < 0){
      perror("fork");
    }else if(pid > 0){
      exit(0);
    }else{
      //5.将当前工作目录改为根目录
      if(chdir("/") < 0){
        perror("child");
        return;
      }
      //关闭不需要的文件描述符,或重定向到/dev/null
      close(0);
      fd0 = open("/dev/null", O_RDWR);
      dup2(fd0, 1);
      dup2(fd0, 2);
    }
  }
}

int main()
{
  mydaemon();
  while (1) {
    sleep(1);
  } 
  return 0;
}
