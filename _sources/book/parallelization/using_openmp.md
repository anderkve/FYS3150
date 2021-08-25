# Using OpenMP

For future reference, you can download OpenMP reference cards that contain tables with OpenMPs functionality. They help you quickly access syntax and built-in functionality if you forget. [OpenMP reference cards](https://www.openmp.org/resources/refguides/)

## Compiler directives

OpenMP is very user-friendly in the sense that
a code written to run series can easily be parallelized
simply by adding **compiler directives**. We'll go through a couple useful ones here.

## Parallel region

A flexible , one can create a **parallel region**, which looks like this

```c++
#pragma omp parallel
{
  //Some code to parallelize here.
}
```
Note:
- It's important that the brackets {} are placed *below* the compiler directive and not directly after. Otherwise a compiler error will occur.
- Any variable declared inside a parallel region is automatically **private**. Each thread can thus use this variable regardless of what the other threads do with it.
- Once you create a parallel region, your computer will **fork** or **spawn** a set of threads. These can now perform computations in parallel.
- Once the region ends, it will **merge** the threads, leaving you with a single thread again.


## Parallelizing a for-loop.

A straight forward way to do this is to create a parallel region and parallelize the code as follows.

```c++
#pragma omp parallel
{
  #pragma omp for
  for (int i = 0; i < n; i++){
    //some code that is parallelized with respect to i
  }
}
```
But parallelization of for-loops is done so often that the two compiler directives

```c++
#pragma omp parallel
```
and
```c++
#pragma omp for
```
is fused to a simpler compiler directive given by

```c++
#pragma omp parallel for
```
Thus the same for-loop can more compactly be parallelized by
```c++
#pragma omp parallel for
for (int i = 0; i < n; i++){
  //some code that is parallelized with respect to i
}
```
The compiler directive here is

```c++
#pragma omp parallel for
```
The variable `i` in the loop is distributed among the threads so that each thread operates with a subset of the loop. The distribution is decided by the compiler. But it may look like this:
  - Assume there are `p` threads. Then thread 0 gets the `n/p` first values of `i`, thread 1 gets the next `n/p` values and so on.
  - Sometimes the compiler divides the for loop cyclically, so thread 0 gets `i = 0, p, 2p, ...` while thread 1 gets `i = 1, p+1, 2p+1, ...` and so on.


The compiler directive only parallelize the *first* following for-loop. For instance
```c++
#pragma omp parallel for
for (int i = 0; i < n; i++){
  for (int j = 0; j < m; j++){
    //some code
  }
}
```
is only parallelized with respect to `i`, not the inner loop that runs over `j`.

## Build a code that can run in serial and in parallel

It's often convenient to specify a compiler directive that tells the compiler to compile a specific part of the code depending on whether we pass `-fopenmp` as a compiler flag or not. If we do not pass it during compilation, it will compile the code in serial. If we do pass it, it will compile it to run in parallel. The generic structure of this looks as follows:

```c++
#ifdef _OPENMP
{
  //parallel code
}
#else
{
  //Serial code
}
#endif
```

## Synchronization (atomic and critical sections)

To avoid the problems that race conditions can bring, it's sometimes convenient to create sections where we force synchronization such that only one thread is executing a code block at a time. There are two alternatives:

1. An `atomic` section which supports incremental operations.
2. A `critical` section which is slightly slower, but is more flexible in the sense that it supports an arbitrary set of operations.

```{note}
In examples where we simply want to combine the results from each thread, there exists functionality known as clauses that perform this efficiently. But it's important to know how to perform synchronization when built-in functionality doesn't do exactly what you need it do.
```

### The atomic section

This is used if we simply want to combine the contribution from each thread to a global variable by addition, multiplication and division **in place**. For example with addition in place, this looks as:

```c++
#pragma omp atomic
  global_variable += local_thread_variable
```

### The critical section

Here we can perform multiple operations but with a slightly larger performance penalty. We could for instance find the maximum value of the local thread variables and assign it to the global variable as follows:

```c++
#pragma omp critical
{
  if (local_thread_variable > global_variable){
    global_variable = local_thread_variable;
  }
}
```


## Clauses

Clauses can be added to OpenMP's compiler directives. They vary depending on what the compiler directive is, and the code documentation for OpenMP can give a far more complete list.
Nevertheless, we provide a few important ones, perhaps the only ones you'll need.

Generically, it looks like

```c++
#pragma omp parallel clause1 clause2 clause3 ... clauseN
{
  //code block
}
```

(may also be added to for loops).

### The private clause
Sometimes, a variable that is initially global (and shared), is desired to be made a private variable. For a parallel region (applies to for loops as well), we simply tack on a clause called `private()` as follows:

```c++
#pragma omp parallel private(variable1, variable2, ..., variableN)
{
  //code block
}
```

### The reduction clause

Often times, we want to combine the results from each thread into a some final global result. A couple examples:
- Sum up the contribution from each thread (+).
- Find the maximum/minimum value from the threads (max/min).

The reduction clause facilitates this by:

```c++
#pragma omp parallel reduction(op:result_variable)
{
  //code block
}
```
There are several operations *op*.

| op | symbol   |
| :------------- | :------------- |
| Sum      | +      |
| Maximum or minimum     | max or min    |
| Multiply     | *    |

An exhaustive list can be found the OpenMP documentation.

### Specify number of threads by a clause

We can specify a desired number `N` of threads by

```c++
#pragma omp parallel num_threads(N)
{
  //code block
}
```

This does not guarantee that the operating system actually gives us that many threads.

### Example: computing the sum of the 100 first integers

We've looked at a lot of general theory. Let's put some of it to use in an example. We'll compute the sum of the 100 first integers. The answer is 5050.

The first step should be to do this with a serial code so we're sure the computations are done correctly. A short program is all we need:

```c++
double s = 0;
int n = 100;
for (int i = 0; i <= n; i++){
        s += i;
    }
std::cout << "sum of first " << n << " integers = " << s << std::endl;
```
which should output

```sh
sum of first 100 integers = 5050
```

Now, parallelizing the code is straight forward. We want to parallelize the for-loop and add a `reduction` clause for `s` with `op` set to `+`:

```c++
#pragma omp parallel for reduction(+:s)
for (int i = 0; i <= n; i++){
        s += i;
    }
```
which should yield the same output as before. We can structure the code so that it runs the serial code if `-fopenmp` is not passed during compilation, and the parallelized version if we pass it. This is done by

```c++
double s = 0;
int n = 100;
#ifdef _OPENMP
{
    #pragma omp parallel for reduction(+:s)
    for (int i = 0; i <= n; i++){
        s += i;
    }
}
#else
{
    for (int i = 0; i <= n; i++){
        s += i;
    }
}
#endif
std::cout << "sum of first " << n << " integers = " << s << std::endl;
```

Now we can run the code both in serial and parallel depending on how we build it.


***

We could've performed the reduction part of the parallelized for-loop by tacking on an `atomic` section at the end as follows:

```c++
double s = 0;
#pragma omp parallel
{
  double s_local = 0;
  #pragma omp for
  for (int i = 0; i <= n; i++){
      s_local += i;
  }
  #pragma omp atomic
      s += s_local;
}
```

but you should use the reduction clause when it's supported. It's typically slightly more efficient and yields cleaner code. But at least now you've seen how you can use a synchronization section in practice.
