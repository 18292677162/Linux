/*this is an udp client
 *  1.create socket
 *  2.bind
 *  3.sendto
 *  3.recvfrom
 *  5.close socket
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
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sockfd < 0){
    perror("socket error");
    close(sockfd);
    return -1;
  }

  //2.bind----client not recommended socket
  
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9000);
  serv_addr.sin_addr.s_addr = inet_addr("192.168.93.167");
  socklen_t len = sizeof(struct sockaddr_in);
  while(1){
    //3.sendto
    char buff[1024] = {0};
    scanf("%s", buff);
    sendto(sockfd, buff, strlen(buff), 0,
              (struct sockaddr*)&serv_addr, len);
    //4.receive
    memset(buff, 0x00, 1024);
    ssize_t r_len = recvfrom(sockfd, buff, 1023, 0, 
                         (struct sockaddr*)&serv_addr, &len);
    if(r_len < 0){
      perror("recvfrom error");
      close(sockfd);
      return -1;
    }
    printf("server say:%s\n", buff);
  }
  return 0;
}


















