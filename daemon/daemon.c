#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
  //deamon(0, 0);
  //默认更改工作目录，且更改文件描述符012为空，指向/dev/null
  //无论哪个文件描述符对其写，数据都会被丢弃
  //deamon(1, 0);
  //不更改目录也不更改文件描述符
  daemon(0, 0);
  while(1);
  return 0;
}
