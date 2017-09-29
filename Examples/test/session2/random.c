#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main(void)
{
  srand(clock());
  int i=0;
  for(i=0;i<100;i++)
  {
   printf("No.%d: %d\n",i+1,rand()%256);
  }
}
