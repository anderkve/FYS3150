## Lecture notes

You can find the latest version of the lecture notes in the file [`lecture_notes.pdf`](https://raw.githubusercontent.com/anderkve/FYS3150/master/lecture_notes/2026/lecture_notes.pdf) above. Keep in mind that the notes are continually updated, so if you read ahead of the lectures some things may change later.


## Overview of lecture topics

### Lecture 1, August 20

- Introduction to the course
- First chat about C++


### Lecture 2, August 21

- Code discussions:
  - Intro to C++
  - "Hello World" example
  - Compilation and linking
  - Source files and header files
  - Compilation and linking with multiple files
  - C++ variable types and scopes


### Lecture 3, August 27

- Topics for Project 1:
  - Discretisation
  - Numerical differentiation
  - Start discussion of boundary value problems (BVPs)
    - Expressing a BVP as a matrix equation

### Lecture 4, August 28

- Cont. topics for Project 1
  - Finish discussion of boundary value problems
    - Overview of Gaussian elimination
    - Gaussian elimination for tridiagonal matrix -> Thomas algorithm
- Code topics:
  - Write C++ output to file
  - Unix terminal: redirect terminal output to file
  - C++: containers (`std::vector` and `std::map`)


### Lecture 5, September 3

- Code topics:
  - Wrap up discussion of `std::vector` and `std::map`. Also mention `std::array`.
  - C++: integer vs floating-point division
- Counting floating-point operations (FLOPs)
- Numerical errors
  - Truncation errors
  - Roundoff errors
    - Loss of numerical precision ("catastrophic cancellation")
    - Example error analysis


### Lecture 6, September 4

- Continue discussion of numerical errors
  - Finish the example error analysis
  - Code example: `error_analysis`
- Binary representation (background for roundoff error discussion)
  - Integers
  - Floating-point numbers
- Code topics:
  - C++: pass-by-reference vs pass-by-value


### Lecture 7, September 10

- Wrap up discussion of binary representation (background for roundoff error discussion)
- Overview of topics for Project 2
- Scaling equations
- Project 2 physics case: The buckling beam
  - Two-point boundary value problem, connection to eigenvalue problem
- Start discussion of eigenvalue problems
- Code topics (if time):
  - C++: pass-by-reference vs pass-by-value


### Lecture 8, September 11

- Cont. discussion of eigenvalue problems
  - Similarity transformations
  - Jacobi's rotation method
    - Main idea
    - Example with $2 \times 2$ matrix
    - Algorithm for $N \times N$ case


### Lecture 9, September 17

- LU decomposition
  - What it is
  - What is it good for:
    - Solving matrix equations  
    - Finding the determinant
    - Finding the inverse
  - How: An algorithm for determining the L and U matrices
  - PLU decomposition
- Code topics:
  - Debugging tips & tricks


### Lecture 10, September 18

- Wrap up discussion of debugging tips & tricks
- Iterative methods for solving matrix equations


### Lecture 11, September 24

- Wrap up discussion of iterative methods for solving matrix equations
- Overview of topics for Project 3
- Code topics:
  - Begin discussing classes in C++
 

### Lecture 12, September 25

- Finish discussion of classes in C++
- Project 3 physics case: Penning traps
- Start discussing initial value problems
  - Introduction
  - Classification
  - From a second-order equation to coupled first-order equations
  - Local vs global errors
If time: begin discussing methods (Forward Euler, Predictor-Corrector, ...)


### Lecture 13, October 1

- Continue discussion of initial value problems
  - Forward Euler
  - Predictor-Corrector
  - Runge-Kutta, 4th order
    - RK4 for sets of coupled equations


### Lecture 14, October 2

- Grading system for projects 3 and 4
- Tips for how to write a good scientific report



