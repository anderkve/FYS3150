# If else

## Syntax

The general syntax for an **if-else block** in C++ is

```c++
if (condition){
    // code to run if condition is true.
}
else{
    // Code to run if condition is false.
}
```

Note that the `else` statement is optional.


### Example 1

Assume we want to implement a stepwise function that returns the input value if it's positive, otherwise it returns 0. This could look as follows:

```c++
double f(double x){
    if (x > 0){
        return x;
    }
    else{
        return 0;
    }
}
```

## Inline if-tests

We can also write inline if-else blocks in C++. This is generically done by

```c++
variable = (condition) ? expression_if_true : expression_if_false
```

### Example 2

Now let's write the function from example 1 using a inline if-test instead.

```c++
double f(double x){
    return (x > 0) ? x : 0;
}
```

It looks horrible, but it is a shorthand that's sometimes used for very simple if-tests. 
