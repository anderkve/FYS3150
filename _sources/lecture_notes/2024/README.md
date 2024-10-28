## Overview of lecture topics


### Lecture 1, August 22:

- Introduction to the course 


### Lecture 2, August 23:

- Code discussions:
  - Intro to C++
  - "Hello World" example
  - Compilation and linking
  - Source files and header files
  - Compilation and linking with multiple files
  - C++ variable types and scopes


### Lecture 3, August 29:

- Topics for Project 1:
  - Discretisation
  - Numerical differentiation
  - Started discussion of boundary value problems (BVPs)
- Code topics:
  - C++: write output to file
  - Unix terminal: redirect terminal output to file
  - C++: containers (`std::vector` and `std::map`)
  - C++: integer vs floating-point division


### Lecture 4, August 30:

- Topics for Project 1:
  - Discretisation
  - Numerical differentiation
  - Finished discussion of boundary value problems (BVPs)
    - Expressing a BVP as a matrix equation
    - Overview of Gaussian elimination
    - Gaussian elimintation for tridiagonal matrix → Thomas algorithm
  - Counting floating-point operations (FLOPs)
- Code topics:
  - C++: pass-by-reference vs pass-by-value


### Lecture 5, September 5:

- Binary representation 
  - Integers
  - Floating-point numbers
- Numerical errors
  - Truncation errors
  - Roundoff errors
    - Loss of numerical precision ("catastrophic cancellation")


### Lecture 6, September 6:

- Continue discussion of numerical errors
  - Example error analysis
  - Code example: `error_analysis`
- LU decomposition
  - What it is
  - What it's good for:
    - Solving matrix equations  


### Lecture 7, September 12:

- Continue discussion of LU decomposition
  - What it's good for:
    - Finding the determinant
    - Finding the inverse
  - How: algorithm for determining the L and U matrices
  - PLU decomposition
- Overview of topics for Project 2
- Scaling equations


### Lecture 8, September 13:

- Continue discussion of scaling equations
- Eigenvalue problems
  - Similarity transformations
  - Jacobi's rotation method
    - Main idea
    - Example with $2 \times 2$ matrix
    - Algorithm for $N \times N$ case


### Lectures 9 and 10, September 19 and 20:

(Videos replaced in-person lectures)

- Project 2 physics case: The buckling beam
- Iterative methods for solving matrix equations
- Debugging tips & tricks
- Guest lecture: How to improve your project reports


### Lecture 11, September 26:

- Overview of topics for Project 3
- Code topics:
  - Classes in C++
  - Code design for simulations
- Project 3 physics case: Penning traps


### Lecture 12, September 27:

- Cont. discussion of the physics case for Project 3: Penning traps
- Initial value problems:
  - Introduction
  - Classification
  - From a second-order equation to coupled first-order equations
  - Local vs global errors
  - Forward Euler
  - Forward Euler and Euler-Cromer for coupled equations
- Code topics:
  - Static variables
  - Hidden files


### Lecture 13, October 3:

- Initial value problems:
  - Predictor-corrector
  - Runge-Kutta
  - Leapfrog


### Lecture 14, October 4:

- Grading system for projects 3--5
- How to write a scientific report


### Lecture 15, October 10:

- Cont. on initial value problems
  - Recap of the Leapfrog algorithm
  - Leapfrog for coupled equations
  - Verlet algorithm
  - Classification of methods for solving IVPs
  - Matrix method for stability analysis


### Lecture 16, October 11:

- Cont. on initial value problems:
  - Cont. on the matrix method for stability analysis
  - Python example illustrating (in)stability and accuracy of different IVP methods
- Start on topics for Project 4:
  - Background: probability theory, meaning of probability


### Lecture 17, October 17:

- Wrap up discussion of the meaning of probability
- Probability theory basics (notation, definitions, ...)
- Prob. distribution functions in many variables


### Lecture 18, October 18:

- **No lecture today**


### Lecture 19, October 24:

- Expectation values
- Project 4 physics case: the 2D Ising model


### Lecture 20, October 25:

- Wrap up discussion of the 2D Ising model
- Introduction to Monte Carlo methods
- Markov chains


### Plan for Lecture 21, October 31:

- Wrap up discussion of Markov chains
- Markov chain Monte Carlo (MCMC)
- Start on parallel computing








