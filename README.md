# Overview
libBlondie is a memoization library for c. Basically, libBlondie provides an effective and simple caching mechanism for your c code by replacing a given function by code that maintains a hash of the parameters and return, and first checks that hash before executing.

Ideally, you'd only expect it work with functions where the parameters are all pass by value and non-struct. 

## Notes
This isn't a complete library as of yet, and shouldn't be used. However, example syntax and performance implications can be seen below.

## Installation
Typical
```
./configure
make
make install
```

## Usage
First inlcude the header...

```
#include <blondie.h>
```


Then rewrite the function like so.

```
BlondieMemoize(return type, function name, $P(parameter list), $V(parameter list without types) , function body)
```

## Examples
This

```
int Fibonacci(int n) {
   if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return ( Fibonacci(n-1) + Fibonacci(n-2) );
} 
```

becomes

```
BlondieMemoize( 
    int, Fibonacci, $P(int n), $V(n), {
    if ( n == 0 )
          return 0;
       else if ( n == 1 )
          return 1;
       else
          return (Fibonacci(n-1)+Fibonacci(n-2));
    }
)
```

## Timings
From the examples

```
$ time examples/fibonacci 38 > ~/tmp/fib.out
 
real    0m1.672s
user    0m1.660s
sys     0m0.000s
```

```
$ time examples/fibonacci_memoized 38 > ~/tmp/fib.mem.out
 
real    0m0.028s
user    0m0.000s
sys     0m0.030s
```

The output shows no difference

```
$ diff ~/tmp/fib.out ~/tmp/fib.mem.out
$
```

Similarly, finding the 40th fibonacci number takes exponentially longer when it's not memoized, but takes about the same amount of time when it is memoized.

```
$ time examples/fibonacci 40 > ~/fib.out

real    0m3.702s
user    0m3.690s
sys     0m0.000s
```

```
$ time examples/fibonacci_memoized 40 > ~/tmp/fib.mem.out

real    0m0.019s
user    0m0.010s
sys     0m0.000s
```

```
$ diff ~/tmp/fib.out ~/tmp/fib.mem.out
$
```

## Use cases for libBlondie
Here I've deliberately chosen a great case for memoization. It shouldn't be used in cases where you expect the target function to produce side effects outside of the function, and should only be used with functions that take only non-struct, non-reference parameters. 

Ideal uses abound, and aren't just limited to recursive functions.

1. Functions that shell out to read a file because of the file size, and grep their output from the file
2. Functions that return expensive computed values
3. Anything that returns the same output for the same input.

## TODO
1. Use tpl to encode and decode parameters and returns. I think I should be able to build the parameter list into a struct and use tpl_bin on it. This would allow memoization of complex data types and references to a degree.
2. Keep memo hashes of each memoized function with much smaller max lengths to speed up the cdc process, and simplify the code hopefully
3. The goal is for this to be a drop-in memoization library that can memoize anything, and be as fast as possible.

## Note
All examples were tested on my android phone using termux
