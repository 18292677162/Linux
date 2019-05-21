#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define IPC_KEY 0x12345678  //消息队列key
#define TYPE_SER 1  //数据块类型
#define TYPE_CLI 2  //数据块类型

struct msgbuf {
  long mtype;
  char mtext[1024];
};

int main()
{
  int msgid = -1;

  msgid = msgget(IPC_KEY, IPC_CREAT | 0664);
  if (msgid < 0) {
    perror("msgget error");
    return -1;
  }
  while (1) {
    //接收数据
    //struct msgbuf 自己定义
    struct msgbuf buf;
    //msgid :操作句柄
    msgrcv(msgid, &buf, 1024, TYPE_CLI, 0);
    printf("client say:[%s]\n", buf.mtext);
    //发送数据
    memset(&buf, 0x00, sizeof(struct msgbuf));
    buf.mtype = TYPE_SER;
    scanf("%s", buf.mtext);
    msgsnd(msgid, &buf, 1024, 0);
  }
  //删除IPC
  msgctl(msgid, IPC_RMID, NULL);
  return 0;
}
