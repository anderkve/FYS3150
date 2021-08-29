# Containers
<!--
Add page on containers (arrays, vectors, maps, pairs, ...).
-->

A **container** stores data in C++. We've already seen the most basic example of this, namely variables. But there's containers akin to *lists* in Python known as `std::vector`. We'll discuss this particular one in detail here.


<!--

- Discuss std::vector (C++) vs std::array (C++) vs C-style arrays
  - https://stackoverflow.com/questions/31548281/advantages-of-2d-vector-array
  - https://stackoverflow.com/questions/4424579/stdvector-versus-stdarray-in-c/4424658#4424658
  - https://stackoverflow.com/questions/15079057/arrays-vs-vectors-introductory-similarities-and-differences



-->


## std::vector

We'll give a short introduction to the `std::vector` class here. For more details, you should consult [code documentation](https://en.cppreference.com/w/cpp/container/vector).


The `std::vector` class must be included using `#include <vector>`.

### Creating a `std::vector` object
We must specify the type of the elements of a `std::vector` object. We can fill it with any type we'd like.

```c++
std::vector<type> variable_name; //Declare, but don't initialize specific elements or length.
std::vector<type> variable_name(length); //Initialize with length, but values are assigned randomly (not sampled to any particular probability distribution though!)
std::vector<type> variable_name(length, value); //Initialize with length and a value for each element.
```

#### Example 1: creating a vector of length `n` filled with zeros
We'll choose the elements to be of the type `double`.


```c++
std::vector<double> my_vector(n, 0.0);
```


#### Example 2: Create a matrix of dimension `N x M`

We can create a matrix by creating a vector that we fill with vectors. That's a mouthful, but not too difficult to understand in practice:

```c++
/*
std::vector<std::vector<double> might seem daunting.
It simply means that the std::vector variable will contain elements of type std::vector<double>
*/
std::vector<std::vector<double>> A(N); //Reserve N elements of type std::vector<double>.
for (int i = 0; i < N; i++){
    A[i].reserve(M); //Reserve memory for M elements of type double at row i
}
```

We haven't filled the matrix with any values yet though, they are just randomly initialized by the operating system.


### Append or `push_back`

The `std::vector` class comes packed with a lot of useful functionality. One of these are the `push_back` method which appends an object to the end of the vector.

#### Example 3: Adding elements of type double using `push_back`

```c++
std::vector x; //Declare a variable x of type std::vector
x.push_back(2.0); //Append the value 2.0 to the variable x.
```

#### Example 4: Creating a matrix using `push_back`

Instead iterating by reserving a predefined number of vectors that `A` should contain, we can instead append how many we feel like as follows.

```c++
std::vector<std::vector<double>> A;
for (int i = 0; i < n; i++){
    std::vector<double> tmp(m, 1.*i); //Create a temporary vector of length m and fill it with the value i.
    A.push_back(tmp); //Append the vector to A. Each vector becomes a row of A.
}
```
