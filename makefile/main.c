#include <stdio.h>
#include "function1.h"
#include "function2.h" 
int main(int argc, char **argv)
{
  function1_print("hello");
  function2_print("world");
  return 0;
}
