# Introduction to OpenMP

Here we'll add some introductory remarks about OpenMP

## What is OpenMP?

OpenMP is an application programming interface (API) that
allows for easy parallelization of C, C++ and Fortran code.
It has an abundance of built in functionality,
which can be used to parallelize code with very few changes
to the existing code project.

## Forking and joining threads

OpenMP assumes an underlying **shared-memory** architecture. This means that when a code runs in parallel, all **threads** access the same memory. Once a **parallel region** is executed, the **primary** thread that **forks** a set of **sub-threads**. Tasks are then divided among these and execute the code block **concurrently**, meaning at the same time. Once execution of the parallel region is completed, the sub-threads are **joined** and only the primary thread remains. The following image illustrates this process

![fork_join](imgs/Fork_join.svg)

```{note}
Sometimes, you'll see the term "master" thread used for the primary thread and "slave" threads used for sub-threads. This was recently changed due to negative connotations to slavery.
```

## Building C++ code with OpenMP

### Linux users

For linux users, compilation with OpenMP is easily facilitated
by the compiler flag `-fopenmp`. Thus compilation can be as easy as

```sh
g++ -c *.cpp -fopenmp
```

The star tells the shell to search for *any* file that ends with `.cpp`; just a convenient shorthand.

Linking is done by adding `-lomp`:.

```sh
g++ -o main.out *.o -lomp
```


### macOS users

For macOS users, compilation is a little bit different from Linux. Here we must add `-Xpreprocessor -fopenmp` (in this specific order!):

```sh
g++ -c *.cpp -Xpreprocessor -fopenmp
```

Note: this assumes you use the Apple clang compiler (which you should be using if you followed the setup process described [here](../getting_ready/mac_users.md)).

Linking is done by adding `-lomp`:

```sh
g++ -o main.out *.o -lomp
```

## Shared memory programming

OpenMP assumes that the underlying memory is **shared**
among all processes, or **threads** as they are called.
This means that all threads share variables, allocated memory for pointers and so on by default. We must specify
if some variable is to be specific to a particular thread.
The terminology OpenMP uses for this is a **private** variable.

There are two very important concepts to understand
when you parallelize with OpenMP.

### False sharing
```{note}
This is a technical concept, and you might be better suited to return to this at a later point.
```

If more than one thread uses a memory block stored in the **cache** (a type of fast memory used by your cpu), any change to it will require all the threads that uses it to make the exact same update to their version of the memory block. This is imposed by what is known by the **cache-coherence policy**. The punchline is that this leads to performance degradation. This process is called false sharing.
  - Example: say you're working with a pointer of length n. One thread updates the first element and another thread updates the second element. Then the computer must send this update back and forth between the threads so that the copy of their pointer is identical at all times. This means that computing time must be divided to send information between the threads which slows down execution of the code.

### Race condition
```{note}
This is a technical concept, and you might be better suited to return to this at a later point.
```


Suppose two threads are to increment a variable *v* that is initially set to zero, i.e `v = 0`. The ideal result is that the final value should be `v = 2`. This will happen if the following sequence of events occur:

1. Thread 1 reads the value of `v` from memory.
2. Thread 1 adds 1 to `v` and writes it back to memory.
3. Only after this, thread 2 performs the exact same action.

The following scenario describes when it goes wrong:

1. Thread 1 reads the value of `v` from memory.
2. Thread 2 reads the value of `v` from memory *before* thread 1 adds 1 and writes it back to memory.
3. Both thread 1 and 2 now adds 1 to `v` and writes it back to memory. But the value both of them read was `v = 0`, so the final value written to memory will be `v = 1`.


We can of course create more scenarios in which this happens, but the main idea to take from this is:
when two threads operate on the same memory address, they must do so sequentially. Sometimes, absurd results from your program can boil down to this process, so it's important to be aware of it for debugging purposes.
