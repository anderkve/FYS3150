# Loops

## For loops

### Syntax

The generic syntax for a for loop in C++ is

```c++
for (int i = 0; i < n; i++){
    //Some code here
}
```
where `n` is assumed to be some positive integer.

We can naturally nest loops as follows

```c++
for (int i = 0; i < n; i++){
    //Maybe some code here
    for (int j = 0; j < m; j++){
        //More code here
        for (int k = 0; k < l; l++){
            //More code
            //And so on ...
        }
    }
}
```

### Example 1

Let's assume we want to sum up the first 100 integers. A for-loop is suited for this and can be implemented as follows:

```c++
double s = 0;
for (int i = 0; i <= 100; i++){
  s += i;
}
```

### Example 2
Let's look a nested loop. We'll implement matrix multiplication `C = AB`. Assume `A` is an (n x m) matrix, `B` is an (m x n) matrix. Then `C` is an (n x n) matrix. The for-loop explicitly implementing this can look as follows (using Armadillo matrices):

```c++
for (int j = 0; j < n; j++){
  for (int i = 0; i < n; i++){
      for (int k = 0; k < m; k++){
          C(i, j) += A(i, k)*B(k, j);
      }
  }
}
```


## While loops

While loops is very useful if we can predict the precise number of iterations needed to perform some task. Instead, we specify a condition that will terminate the loop one the condition is false.


### Syntax

The generic syntax of a while loop is

```c++
while (condition){
    //Code block to execute as long as condition is true.
}
```


### Example 1

Let's redo the summation of the 100 first integers, but instead with a while loop. This looks like:

```c++
int i = 0;
double s = 0;
while (i <= 100){
    s += i;
    i++;
}
```
