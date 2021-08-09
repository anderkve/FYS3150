# Using OpenMP


## Compiler directives

OpenMP is very user-friendly in the sense that
a code written to run series can easily be parallelized
simply by adding *compiler directives*. We'll go through a couple useful ones here.

## Parallel region

A flexible , one can create a *parallel region*, which looks like this

```c++
#pragma omp parallel
{
  //Some code to parallelize here.
}
```
Note:
- It's important that the brackets {} are placed *below* the compiler directive and not directly after. Otherwise a compiler error will occur.
- Any variable declared inside a parallel region is automatically *private*. Each thread can thus use this variable regardless of what the other threads do with it.


## Parallelizing a for-loop.

A straight forward way to do this is to create a parallel reigion and parallelize the code as follows.

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
The variable *i* in the loop is distributed among the threads so that each thread operates with a subset of the loop. The distribution is decided by the compiler. But it may look like this:
  - Assume there are *p* threads. Then thread 0 gets the *n/p* first values of *i*, thread 1 gets the next *n/p* values and so on.
  - Sometimes the compiler divides the for loop cyclically, so thread 0 gets *i = 0, p, 2p, ...* while thread 1 gets *i = 1, p+1, 2p+1, ...* and so on.


The compiler directive only parallelize the *first* following for-loop. For instance
```c++
#pragma omp parallel for
for (int i = 0; i < n; i++){
  for (int j = 0; j < m; j++){
    //some code
  }
}
```
is only parallelized with respect to *i*, not the inner loop that runs over *j*.

## Clauses

Clauses can be added compiler directives. They vary depending on what the compiler directive is, and the code documentation for OpenMP can give a far more complete list.
Nevertheless, we provide a few important ones, perhaps the only ones you'll use.

Generically, this looks like

```c++
#pragma omp parallel clause1 clause2 clause3 ... clauseN
{
  //code block
}
```

(may also be added to for loops).

### The private clause
Sometimes, a variable that is initially global (and shared), is desired to be made a private variable. For a parallel region (applies to for loops as well), we simply tack on a clause called *private()* as follows:

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

We can specify a desired number *N* of threads by

```c++
#pragma omp parallel num_threads(N)
{
  //code block
}
```
