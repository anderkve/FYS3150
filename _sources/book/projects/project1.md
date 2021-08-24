# Project 1

## Practicalities

- **Deadline**: Monday, September 13.
- **Format:** 
  - A pdf document, typeset in LaTeX, with answers to all the problems below. You deliver the pdf on Canvas.
  - Code (with comments, of course) on a GitHub repo, with the repo link provided in the pdf documentet.

- **Not a complete report:** For project 1 we do not require you to write a proper scientific report --- only a document with an answer for each problem. But the quality of the presentation still matters, of course. So pay attention to figures, figure captions, grammar, etc.

- **Collaboration:** If you are collaborating with others (*and we hope you are!*) you *must* register a group on Canvas. The group hands in a single pdf. Remember to list everyone's name in the pdf. 

- **Reproducibility:** Your code should be available on a GitHub repo. You can refer to relevant parts of your code in your answers. Make sure to include a README file in the repo that explains how the code should be compiled and run in order to reproduce your results.

- **Figures:** Figures included in your LaTeX document should be made as vector graphics (e.g. `.pdf` files), rather than raster graphics (e.g. `.png` files). If you are making plots with `matplotlib.pyplot` in Python, this is as simple as calling `plt.savefig("figure.pdf")` rather than `plt.savefig("figure.png")`.

## Preliminaries

- If you're not familiar with using the terminal, we recommend taking the time to work through the examples on the terminal [basics](../using_the_terminal/basics.md) page, and look at the [keyboard shortcuts](../using_the_terminal/keyboard_shortcuts.md).

- Similarly, if you've not used git before, it's a good idea to learn some of the basics before jumping into the project. See the links on the left-hand side.

- The most important C++ aspects for this project are: 
  - basic C++ program structure
  - compiliation and linking
  - functions
  - vectors/arrays (examples of *containers*)
  - writing output to screen and/or file

  We will discuss these topics in the lectures, and our discussions there will largely be based on the "Introduction to C++" pages on the left (which are currently under development.)


## Introduction 
The overall topic of this project is numerical solution of the one-dimensional Poisson equation. This is a second-order differential equation that shows up in several areas of physics, e.g. electrostatics. In future projects we will pay close attention to scaling of dimensionfull physics equations, but for this first project we start directly from the differential equation *after* scaling to dimensionless variables.

The one-dimensional Poisson equation is given by

$$ 
-\frac{d^2 u}{dx^2} = f(x).
$$ (poisson_eq)

Here $f(x)$ is a known function (the *source term*). Our task is to find the function $u(x)$ that satisfies this equation for a given boundary condition. The specific setup we will assume is the following:

- source term: $f(x) = 100 e^{-10 x}$
- $x$ range: $x \in [0,1]$
- boundary condition: $u(0) = 0$ and $u(1) = 0$



## Problems


### Problem 1

Check analytically that an exact solution to Eq. {eq}`poisson_eq` is given by

$$
u(x) = 1 - (1 - e^{-10}) x - e^{-10 x}.
$$ (exact_solution)


### Problem 2

Make a plot of the exact solution above, using the following strategy:
- Write a program that defines an array of $x$ values, evaluates the exact solution $u(x)$ above for these points, and outputs the $x$ and $u(x)$ values as two columns in a data file. The numbers should be written to file in scientific notation and with a fixed number of decimals. (Choose a sensible number.)
- Write a short plotting script (we recommend Python for this) that reads the data file and generates the plot.


### Problem 3

Derive a discretized version of the Possion equation. You don't have to show every step of your derivation, but include the main steps and a couple of sentences to explain the logic.

*Notation:* Make sure that your notation clearly distinguishes the *discretized approximation to $u(x)$* from the *actual exact $u(x)$*. Here we will use $v$ to represent an approximation to $u$.


### Problem 4

Show that you can rewrite your discretized equation as a matrix equation on the form

$$
\mathbf{A} \vec{v} = \vec{g}
$$ (matrix_eq)

where $\mathbf{A}$ is a tridiagonal matrix with the subdiagonal, main diagonal and superdiagonal specified by the signature $(-1,2,-1)$.

Make sure to specify how an element of $\vec{g}$ is related to the variables in the original differential equation.


### Problem 5

Let the vector $\vec{v}^*$ of length $m$ represent a complete solution of the discretized Poisson equation, with corresponding $x$ values given by the lenght-$m$ vector $\vec{x}$. Let $\mathbf{A}$ be an $n \times n$ matrix. 
  
**a)** How is $n$ related to $m$? 

**b)** What part of the complete solution $\vec{v}^*$ do we find when we solve Eq. {eq}`matrix_eq` for $\vec{v}$?


### Problem 6

Now we'll forget about the Poisson equation for a moment, and simply consider
the equation $\mathbf{A} \vec{v} = \vec{g}$ where $\mathbf{A}$ is a *general* tridiagonal matrix, with vectors
$\vec{a}$, $\vec{b}$ and $\vec{c}$ representing the subdiagonal, main diagonal and superdiagonal, respectively.
That $\mathbf{A}$ is a general tridiagonal matrix means that every element of $\vec{a}$, $\vec{b}$ and $\vec{c}$ can be different.

**a)** Write down an algorithm for solving $\mathbf{A} \vec{v} = \vec{g}$.

**b)** Find the number of floating-point operations (FLOPs) for this algorithm.

We'll refer to this algorithm as the *general algorithm*.


### Problem 7

Now we get back to the Poisson equation. 

**a)** Write a program that
- uses the *general algorithm* to solve $\mathbf{A} \vec{v} = \vec{g}$, 
where $\mathbf{A}$ is the tridiagonal matrix from Problem 4;
- writes the solution $\vec{v}$ and corresponding $\vec{x}$ (plus any other data you find useful) to a file.

**b)** With $n$ being the number of grid points, run your program for $n=10,100,1000,\ldots$ (as far as you think is reasonable) and make a plot that compares your numeric solutions for different values of $n$ against the exact solution for $u(x)$ in Eq. {eq}`exact_solution`.


### Problem 8

**a)** Make a plot that shows the (logarithm of) the *absolute* error, 
  
$$
\Delta_i = \log_{10}(|u_i - v_i|)
$$  

as a function of $x_i$. Show $\Delta_i$ for different choices of $n$ as different graphs in the same plot.


**b)** Similarly, make a plot of the *relative* error 

$$
\epsilon_i = \log_{10}\left(\left| \frac{u_i - v_i}{u_i} \right| \right) 
$$

as function of $x_i$. Again, one graph per choice of $n$.

**c**) Now make a table that shows the *maximum* relative error $\max(\epsilon_i)$ for each choice of $n$, up to $n = 10^7$. Feel free to also make a plot to visualise this. Comment on your result.



### Problem 9

**a)** Now specialize your algorithm from Problem 6 for our special case where $\mathbf{A}$ is specified by the signature $(-1,2,-1)$, that is, with $\vec{a} = (-1,-1,\ldots,-1)$, $\vec{b} = (2,2,\ldots,2)$ and $\vec{c} = (-1,-1,\ldots,-1)$.

We'll refer to this as the *special algorithm*.

**b)** Find the number of FLOPs for this algorithm.

**c)** Write code that implements this algorithm.


### Problem 10

For values of $n$ up to $n = 10^6$, run timing tests that compares the time 
used by the general algorithm and the special algorithm. (*Remember:* reliable timing results require repeated runs for each choice of $n$.) 
Make a table or plot to present your timing results, and comment briefly on the results.



### Problem 11

Now say we wanted to solve our matrix equation using the general 
LU decomposition approach to solving matrix equations. 
(Feel free to try this, either by writing your own code or using a library, e.g. armadillo.) 
  
What do you expect would happen if you attempted to run code for the case $n = 10^5$ on your laptop?


----


## Code snippets

Here's a C++ code example that uses `<chrono>` from the C++ standard library to measure the time used by a part of a program:

```cpp
#include <chrono>

int main () 
{

  // ...

  // Start measuring time
  auto t1 = std::chrono::high_resolution_clock::now();
    
  //
  // The code you want to perform timing on
  //

  // Stop measuring time
  auto t2 = std::chrono::high_resolution_clock::now();
   
  // Calculate the elapsed time
  // We use chrono::duration<double>::count(), which by default returns duration in seconds
  double duration_seconds = std::chrono::duration<double>(t2 - t1).count();

  // ...
}
```


Alternatively, you can use the C library `time.h`. Here's a code snippet demonstrating that:


```c
#include <time.h>

int main () 
{

  // ...

  // Start measuring time
  clock_t t1 = clock();
   
  //
  // The code you want to perform timing on
  //

  // Stop measuring time
  clock_t t2 = clock();

  // Calculate the elapsed time.
  double duration_seconds = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
   
  // ...
}
```


(There may appear more useful code snippets here...)

