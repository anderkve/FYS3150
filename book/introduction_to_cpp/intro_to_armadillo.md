# Introduction to Armadillo

Armadillo is an efficient linear algebra library for C++ users. Its aim is to provide a library that balances speed and ease of use. We recommend this library for numerical computations.

## Building code with Armadillo

We must make sure to include the header file for Armadillo, which amounts to adding `#include <armadillo>` at the top of a header or source file.

### Compiling code with Armadillo
For macOS users specifically, you must specificy a version of C++ that is C++11 or later. This is done by adding the compiler flag `-std=c++11` during compilation.

For Linux users, nothing special is typically required.


### Linking code with Armadillo

To link to Armadillo, we must add the compiler flag `-larmadillo` during linking.


## Matrices
Assume that `n` and `m` are positive integers.


### Declaring and filling matrices

Creating matrices with Armadillo is easy. Here's a couple examples:

```c++
arma::mat A = arma::mat(n, m); //Initialize but don't fill
arma::mat B = arma::mat(n, m).fill(0.); //Declare and fill with zeros.
arma::mat C = arma::mat(n, m).randn(); //Declare and fill with random values from the normal distribution.
```

### Accessing elements in a matrix

Access of elements in an Armadillo matrix is done as follows:

```c++
double A_ij = A(i,j); //Assign element (i,j) of the matrix A to A_ij.
```

### Extracting a column of a matrix

Armadillo provides a simple way to extract entire columns of a matrix:

```c++
arma::vec col_vec = A.col(j); //Extract column j of A and assign it to col_vec.
```
