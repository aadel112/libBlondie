# Overview
libBlondie is a memoization library for c. Ideally, you'd only expect it work with functions where the parameters are all pass by value and non-struct. 

## Notes
This isn't a complete library as of yet, and shouldn't be used. However, example syntax and performance implications can be seen below.

# Usage
```
BlondieMemoize(return type, function name, function body, $P(parameter list), parameter list without types)
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
    int, Fibonacci, {
    if ( n == 0 )
          return 0;
       else if ( n == 1 )
          return 1;
       else
          return (Fibonacci(n-1)+Fibonacci(n-2));
    }, $P(int n), n
)
```

## Timings
From the examples

> $ time examples/fibonacci 38 > ~/tmp/fib.out
> 
> real    0m1.672s
> user    0m1.660s
> sys     0m0.000s

> $ time examples/fibonacci_memoized 38 > ~/tmp/fib.mem.out
> 
> real    0m0.028s
> user    0m0.000s
> sys     0m0.030s

The output shows no difference

> $ diff ~/tmp/fib.out ~/tmp/fib.mem.out
> $

Similarly, finding the 40th fibonacci number takes exponentially longer when it's not memoized, but takes about the same amount of time when it is memoized.

> $ time examples/fibonacci 40 > ~/fib.out
> 
> real    0m3.702s
> user    0m3.690s
> sys     0m0.000s

> $ time examples/fibonacci_memoized 40 > ~/tmp/fib.mem.out
> 
> real    0m0.019s
> user    0m0.010s
> sys     0m0.000s

> $ diff ~/tmp/fib.out ~/tmp/fib.mem.out
> $

## Use cases for libBlondie
Here I've deliberately chosen a great case for memoization. It shouldn't be used in cases where you expect the target function to produce side effects outside of the function, and should only be used with functions that take only non-struct, non-reference parameters. 

Ideal uses abound, and aren't just limited to recursive functions.

1. Functions that shell out to read a file because of the file size, and grep their output from the file
2. Functions that return expensive computed values
3. Anything that returns the same output for the same input.
