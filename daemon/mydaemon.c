#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

void mydaemon()
{ 

}

int main()
{
  mydaemon();
  while (1) {
    sleep(1);
  } 
}
