#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
   int pid1, pid2;
   while ((pid1 = fork()) == -1);
   if (pid1 == 0) printf("b");
   else
   {
      while ((pid2 = fork()) == -1);
      if (pid2 == 0) printf("c");
      else printf("a");
   }
   return 0;
}