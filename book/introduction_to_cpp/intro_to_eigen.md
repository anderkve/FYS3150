(sec:intro_to_eigen)=
# Introduction to Eigen

Eigen is an efficient linear algebra library for C++, that has become the industry standard for most linear algebra work.

We'll cover some of the very basics of Eigen here to get you started with the library. A complete overview of the available classes and functions, along with usage examples, can be found in the Eigen [code documentation](https://libeigen.gitlab.io/).

## Building code with Eigen

We must make sure to include the header file for Eigen, which amounts to adding `#include <Eigen/Dense>` at the top of a header or source file.


### Including Eigen in code

By default, Eigen is not installed in a path your computer will search through by default during compilation.
This is solved by adding a compiler flag to tell your compiler where it is installed.
To do this, add the flag `-I <path/to/eigen3/folder>`, e.g. `-I /usr/include/eigen3` (this is the default on unix machines like Mac or Linux).

```{note}
Even if you have Eigen 5.0 installed, it still installs in the eigen3 folder.
```

## Vectors

Eigen provides a useful vector class `Eigen::VectorXd` that can be used to replace arrays in numerical computations. Assume `n` is a positive integer.

### Declaring and filling vectors

```c++
Eigen::VectorXd x(n); // Initialize vector but don't fill it
x.fill(2.0); // Fill the vector with twos
Eigen::VectorXd y = Eigen::VectorXd::Constant(n, 2.0); // Alternatively, you can use Eigens own function for this
Eigen::VectorXd z = Eigen::VectorXd::Random(n); // Declare and fill a vector with random values from a uniform distribution on [-1, 1]
Eigen::VectorXd u{{0.1, 0.2, 0.3}}; //Declare and fill a vector with the values 0.1, 0.2 and 0.3
// Alternatively, you can fill it with the << operator
Eigen::VectorXd v = Eigen::VectorXd(3); // 3 matches the number of filled entries below
v << 0.1, 0.1, 0.2;
```

```{note} What does the Xd in VectorXd mean?
In Eigen, the type names encode both the size and the underlying data type:
- `X` signifies *dynamic size*, i.e., the length is not fixed in advance and is determined at runtime (e.g., `Eigen::VectorXd(n)`). These vectors are allocated on the *heap*.
- `d` signifies the data type `double` (similarly, `i` means `int` and `f` means `float`).
    
Eigen also provides fixed-size types where the size is known at compile time, such as `Eigen::Vector3d` (for 3D vectors $(x, y, z)$) or `Eigen::Vector2d`, and for arbitrary types and sizes known at compile time through `Eigen::Vector<double, N>`.
Fixed-size vectors are allocated on the *stack*, avoiding dynamic memory allocation overhead and making them very fast. You will learn more about stack vs. heap memory towards the end of the course, but for general simulations with arbitrary grid sizes, `VectorXd` is the standard choice.
```

### Accessing and assigning elements in a vector

We can access an element `i` from a vector `x` by

```c++
double x_i = x(i); // Extract element i of x and assign it to x_i.
double x_i = x[i]; // This also works ;)
```

We can assign a new value to element `i` in the vector `x` using

```c++
x(i) = some_new_value;
x[i] = some_new_value; // Also works here
```

## Matrices
Assume that `n` and `m` are positive integers.


### Declaring and filling matrices

Creating matrices with Eigen is easy. Here's a couple examples:

```c++
Eigen::MatrixXd A(n, m); // Initialize matrix but don't fill
A.fill(0.0; // Fill the matrix with zeros)
Eigen::MatrixXd B = Eigen::MatrixXd::Constant(n, m, 0.0); // Alternatively, you can use the Constant function
Eigen::MatrixXd C = Eigen::MatrixXd::Random(n, m); // Declare and fill a matrix with random values from the uniform distribution on [-1, 1]
Eigen::MatrixXd D{{0.0, 0.1, 0.2},
                  {1.0, 1.1, 1.2},
                  {2.0, 2.1, 2.2}}; // Initialize a matrix and fill it
Eigen::MatrixXd E = Eigen::MatrixXd(3, 3);
E << 0.0, 0.1, 0.2,
     1.0, 1.1, 1.2,
     2.0, 2.1, 2.2; // Fill a 3x3 matrix with the listed values
```

```{note} Fixed-size vs. Dynamic-size Matrices
Just like vectors, `MatrixXd` denotes a matrix of *dynamic size* (`X`) containing `double` values (`d`).

For small, fixed-size matrices (such as $3 \times 3$ rotation or inertia tensors), you can use stack-allocated types like `Eigen::Matrix3d` or `Eigen::Matrix2d`, or for arbitrary compile-time sizes and types `Eigen::Matrix<double, N, M>`.
When working with larger, runtime-sized matrices (e.g., $N \times M$ discretization grids), always use `Eigen::MatrixXd`.
```

### Accessing elements in a matrix

Access of elements in an Eigen matrix is done as follows:

```c++
double A_ij = A(i,j); // Assign element (i,j) of the matrix A to A_ij
```

### Extracting a column of a matrix

Eigen provides a simple way to extract entire columns of a matrix:

```c++
Eigen::VectorXd col_vec = A.col(j); // Extract column j of A and assign it to col_vec
```


## Saving and loading vectors and matrices

Eigen provides built-in functionality for saving and loading `Eigen::VectorXd` and `Eigen::MatrixXd` objects to text files.
Not only does this simplify storage of results with a predictable format, but it turns out that we can easily load these text files directly in Python with `numpy`!

If `A` is an `Eigen::MatrixXd` object, you can save it to <filename>, e.g. "matrix.txt" or "A.dat" using

```c++
#include <fstream> // The C++ standard library's file streaming utilities

std::ofstream file(filename); // ofstream: out-file-stream
file << A; // Write A to file
```

The default storage format is a human-readable textfile. Precision and format can be set as normal, see [this section on formatting file output](./write_to_file.md#example-with-nicely-formatted-numbers-before-c20) (note that setw will only work for the first element of the matrix, so either drop that or loop through every element explicitly).


### Reading the data table

Say you have written your matrix to some datafile, e.g., `matrix.dat`:

```
0.0000e+00  0.0000e+00  0.0000e+00
0.0000e+00  1.9635e-01  3.8553e-02
0.0000e+00  3.9270e-01  1.5421e-01
0.0000e+00  5.8905e-01  3.4698e-01
0.0000e+00  7.8540e-01  6.1685e-01
1.9635e-01  0.0000e+00  1.9635e-01
1.9635e-01  1.9635e-01  2.4247e-01
1.9635e-01  3.9270e-01  3.6569e-01
1.9635e-01  5.8905e-01  5.6599e-01
1.9635e-01  7.8540e-01  8.4336e-01
3.9270e-01  0.0000e+00  3.9270e-01
3.9270e-01  1.9635e-01  4.6150e-01
3.9270e-01  3.9270e-01  6.0723e-01
3.9270e-01  5.8905e-01  8.2971e-01
3.9270e-01  7.8540e-01  1.1288e+00
5.8905e-01  0.0000e+00  5.8905e-01
5.8905e-01  1.9635e-01  6.9558e-01
5.8905e-01  3.9270e-01  8.7831e-01
5.8905e-01  5.8905e-01  1.1363e+00
5.8905e-01  7.8540e-01  1.4688e+00
```

If you already know the dimensions of the matrix, $n$ and $m$, loading the file can be done by

```c++
#include <fstream>

Eigen::MatrixXd B(n, m); // This is an equivalent way of declaring a MatrixXd object B
std::ifstream file("matrix.dat"); // ifstream: in-file-stream

for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        file >> B(i,j);
    }
}
```

### Writing to binary format

It is also possible to write an `Eigen::MatrixXd` object to binary file. 

To do this, we must convert the `double` values of `Eigen::VectorXd` or `Eigen::MatrixXd` to `char`, the native C++ character type.

```c++
#include <fstream>

std::ofstream file("matrix.bin", std::ios::binary); // "matrix.bin" is an example filename, but you should use .bin extension for binary files

// This next line does a lot of heavy lifting:
// 1. it reinterprets the doubles of A to char values (exposing the raw binary form of the numbers)
// 2. it calculates the number of bytes to write as the size of the matrix times the byte-size of a double
file.write(reinterpret_cast<char*>(A.data()), A.size() * sizeof(double));
```

### Loading vectors and matrices in Python

Eigen interfaces well directly with numpy in python. To load an `Eigen::VectorXd` or `Eigen::MatrixXd` object with numpy you can do

```python
import numpy as np

A = np.loadtxt("matrix.txt") # If you saved is as txt
# If you saved it as a binary and know the number of rows/columns you can load it using
B = np.fromfile("matrix.bin").reshape((n, m), order='F') # The order='F' tells us that the rows and columns are reversed compared to ordinary Numpy, as they are in Fortran (hence the 'F')
```

### When the number of rows and columns are unknown

If you want to tell whomever is reading your saved vector/matrix file how large it is, you can invent your own file format for this!

One such way would (for an `Eigen::MatrixXd` object `A`) to write the number of rows and columns first in your file. This can be done through

```c++
#include <fstream>

std::ofstream file("matrix.bin", std::ios::binary); // File to write too

int rows = A.rows();
int cols = A.cols();

file.write(reinterpret_cast<char*>(&rows), sizeof(int)); // Write the number of rows
file.write(reinterpret_cast<char*>(&cols), sizeof(int)); // Write the number of columns

file.write(reinterpret_cast<char*>(A.data()), A.size() * sizeof(double)); // Write the matrix
```

Then, to load it in numpy, you can do

```python
import numpy as np

with open("matrix.bin", "rb") as file: # "rb" gives you 'read' and 'binary'
    n = np.fromfile(file, dtype=np.int32, count=1)[0] # Read rows
    m = np.fromfile(file, dtype=np.int32, count=1)[0] # Read cols
    A = np.fromfile(file, dtype=np.float64, count=n * m).reshape((n, m), order='F')
```


## What is next?

Now we have gone through the basics of Eigen, and can declare, fill, write and load vectors and matrices using it.
However, this is only the tip of the iceberg, as there is a rich plethora of functions, objects and neat things you can do in Eigen.
Now you can acquaint yourselves with [the documentation](https://libeigen.gitlab.io/documentation/), and learn about things like `.dot()`, `.cross()`, `.transpose()`, `.norm()`, `.mean()`, `Eigen::VectorXd::LinSpaced` and much more.

