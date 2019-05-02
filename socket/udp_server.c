/*this is an udp server
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>

int main()
{
  //1.create socket
  //int socket(int domain, int type, int protocol);
  //  domain:地址域
  //    AF_INET   IPv4
  //    AF_INET6  IPv6
  //  type:套接字类型
  //    SOCK_STREAM 
  //    SOCK_DGRAM
  //    SOCK_SEQPACKET
  //    SOCK_RAW
  //  protocol:协议类型
  //    0--default
  //  defeat:-1
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sockfd < 0){
    perror("socket error!!!\n");
    return -1;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 8000;
  addr.sin_addr.sin_addr = "192.168.93.167";
  return 0;














