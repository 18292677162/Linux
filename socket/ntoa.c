#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
  struct sockaddr_in addr;
  inet_aton("192.168.255.255", &addr.sin_addr);
  uint32_t* ptr = (uint32_t*)(&addr.sin_addr);
  printf("addr: %x\n", *ptr);
  printf("addr_str: %s\n", inet_ntoa(addr.sin_addr));
  return 0;
}
