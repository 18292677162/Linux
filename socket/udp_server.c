/*this is an udp server
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

  //struct sockaddr:公共socket结构体
  //struct sockaddr_in
  //struct sockaddr_in6
  
  //2.bind address info for socket
  //  int bind (int sockfd, struct sockaddr *addr, socklen_t addrlen);
  //    sockfd: 套接字描述符
  //    addr:   要绑定的地址
  //    addrlen:地址信息长度
  //
  //    port:   0-65535   0-1023:Well-Known Port Number 知名端口号
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  //uint16_t htons(uint16_t hostshort);
  //16位短整型从主机字节序转换为网络字节序
  addr.sin_port = htons(9000);
  //in_addr_t inet_addr(const char *cp);
  //IP:Point to Network
  //将点分十进制的字符串IP地址转换为网络字节序的地址
  addr.sin_addr.s_addr = inet_addr("192.168.93.167");
  //inet_pton(AF_INET, "192.168.93.167", &addr.sin_addr);
  
  //int bind(int socket, const struct sockaddr *address,
  //    socklen_t address_len);
  socklen_t len = sizeof(struct sockaddr_in);
  int ret = bind(sockfd, (struct sockaddr*)&addr, len);
  if(ret < 0){
    perror("bind error");
    close(sockfd);
    return -1;
  }

  //3.receive buff from sockfd
  //ssize_t recvfrom(int sockfd, void *buf, size_t len,
  //int flags,struct sockaddr *src_addr, socklen_t *addrlen)
  //sockfd:   套接字描述符
  //buf：     接收到的数据
  //len：      接收的数据长度
  //flags：   发送标志，0-默认阻塞
  //          MSG_PEEK    接收数据后数据并不会从缓冲区删除
  //          场景：探测型获取数据
  //src_addr: 发送端的地址信息
  ////addrlen:  地址信息长度
  //返回值：实际读取到的数据字节长度

  while(1){
    char buff[1024] = {0};
    struct sockaddr_in cli_addr;
    len = sizeof(struct sockaddr_in);
    ssize_t r_len = recvfrom(sockfd, buff, 1023, 0,
                        (struct sockaddr*)&cli_addr, &len);
    if(r_len < 0){
      perror("recvfrom error");
      close(sockfd);
      return -1;
    }
    printf("client[%s:%d]say:%s\n", 
            inet_ntoa(cli_addr.sin_addr),
            ntohs(cli_addr.sin_port), buff);
    memset(buff, 0x00, 1024);
    printf("Please Enter:");
    scanf("%s", buff);
    sendto(sockfd, buff, strlen(buff), 0,
            (struct sockaddr*)&cli_addr, len);
  }
  close(sockfd);
  return 0;
}




