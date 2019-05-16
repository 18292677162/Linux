#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define OPEN_MAX 1024

my_dup2(int fd, int new_fd)
{
  int count = 0;
  int fdarr[new_fd];  //打开的文件描述符
  if(new_fd < 0 || new_fd > OPEN_MAX){
    printf("输入文件描述符有误");
    exit(0);
  }
  if (fd == new_fd) {
    return fd;
  }
  close(new_fd);
  for(count = 0; count <= new_fd; count++){
    fdarr[count] = dup(fd);
    if (fdarr[count] == -1) {
      perror(dup);
      exit(0);
    }
    else {
      printf("fd in for is: %d\n", fdarr[count]);
      if (fdarr[count] == new_fd) {
        return fdarr[count];
      }
    }
  }
}

int main(int argc, const char *argv[])
{
  int new_fd, ret_fd;
  if(argc != 2){
    printf("./a.out test\n");
    exit(0);
  }
  printf("输入要设置的文件描述符\n");
  scanf("%d", &new_fd);

  int fd = open(argv[1], 0);
  if(fd == -1){
    perror(argv[1]);
    exit(0);
  }
  printf("old fd: %d\n", fd);
  ret_fd = my_dup2(fd, new_fd);
  printf("new fd: %d\n", ret_fd);
  close(fd);
  close(ret_fd);
  return 0;
}
