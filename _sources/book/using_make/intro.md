# Intro

Make is, for our purposes, a programming language that facilitates compilation and execution of C++ programs.  

## Makefiles

A *Makefile* is both the type and the name of the file that *Make* executes.

Makefiles can be quite complicated, but in this introduction we'll confine ourselves to simply writing a simple makefile. A makefile should either be named *makefile* or *Makefile*.


Let's go ahead and create a makefile that we'll use to compile a some a short C++ program. First, run

```sh
touch makefile
```

We can divide the makefile into several simple instructions. Let's define an instruction *compile*:

```make
compile:
  g++ -c main.cpp
```

Add another instruction for linking:

```make
link:
  g++ -o main.out main.o
```

And finally an instruction for executing the program

```make
run:
  ./main.out
```

It's convenient to define an instruction that combines all three at once:

```make
all: compile link run
```

The instruction *all* executes *compile*, *link* and *run* in the order they appear. The complete makefile will look as follows.

```make
all: compile link run

compile:
  g++ -c main.cpp

link:
  g++ -o main.out main.o

run:
  ./main.out
```

## How to use Make

To run a specific instruction, run

```sh
make instruction
```

In the example makefile above, we could run

```sh
make all
```
which would perform all three instructions *compile*, *link* and *run*. You can naturally also just execute any of them manually.

You can try it out with the C++ program below. Copy it into a file name *main.cpp*.


```c++
#include <iostream>

double f(double x);

int main(int argc, char const *argv[]) {
    double a = 0;
    double b = 1;
    double I = 0;
    int n = 10000;
    double h = (b-a)*1./n;
    for (int i = 0; i < n; i++){
        double x = a + i*h;
        I += f(x);
    }
    I *= h;
    std::cout << "Integral = " << I << std::endl;

    return 0;
}

double f(double x){
    return x*x;
}
```


## Some more advanced usage of make

1. **Wildcard**. If you have a large number of .cpp that needs to be compiled, you can use the wildcard function of make to compile all files that ends with .cpp. It looks as follows

  ```make
  compile:
    g++ -c $(wildcard *.cpp)

  link:
    g++ -o main.out $(wildcard *.o)
  ```
  The *compile* instruction compiles all files ending with .cpp while *link* links all files ending with .o to main.out.
