#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
  struct sockaddr_in addr1;
  struct sockaddr_in addr2;
  addr1.sin_addr.s_addr = 0;
  addr2.sin_addr.s_addr = 0xffffffff;
  char* ptr1 = inet_ntoa(addr1.sin_addr);
  char* ptr2 = inet_ntoa(addr2.sin_addr);
  printf("ptr1: %s, ptr2: %s\n", ptr1, ptr2);
  return 0;
}
