#include <stdio.h>
#include <stdlib.h>

int Fibonacci(int);

int main(int argc, char** argv) {
   int n, i = 0, c;

//    scanf("%d",&n);
    n = atoi(argv[1]);

   printf("Fibonacci series %d\n", n);
 
   for ( c = 1 ; c <= n ; c++ ) {
      printf("%d\n", Fibonacci(i));
      i++; 
   }
 
   return 0;
}
 
int Fibonacci(int n) {
   if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return ( Fibonacci(n-1) + Fibonacci(n-2) );
} 

