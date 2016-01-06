#include <stdio.h>
#include "blondie.h"
 
int Fibonacci(int n, int w);
 
int main(int argc, char** argv) {
   int n, i = 0, c;

//    scanf("%d",&n);
    n = atoi(argv[1]);

   printf("Fibonacci series %d\n", n);
 
   for ( c = 1 ; c <= n ; c++ ) {
      printf("%d\n", Fibonacci(i, 0));
      i++; 
   }
 
   return 0;
}
 
BlondieMemoize( 
    int, Fibonacci, $P(int n, int w), $V(n, w), 
    {
    if ( n == 0 )
          return 0;
       else if ( n == 1 )
          return 1;
       else
          return (Fibonacci(n-1, 0)+Fibonacci(n-2, 0));
    }
)

