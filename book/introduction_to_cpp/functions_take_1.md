# Functions, take 1

A **function** in C++ is a code block which is executed only when the function is called. A function takes **arguments**, performs some action and usually returns and **output**.

## Creating a function

Creating a function in C++ consists of two steps:
1. **Declaration**. Specifies the function's name, return type and parameters.
2. **Definition**. The code block of the function, or its **body**.

Generically:

```c++
type function_name(type1 input1, ..., typeN inputN){ //declaration
    //Code block or body (i.e definition)
}
```

```{note}
If you declare a function after the main() function in C++, you will get an error. You must therefore declare the function before the main() function in your C++ program.
```

## Separation of declaration and definition

As noted, we can't declare a function after the `main()` function of a C++ program. We can however separate the two. What this means is
- Declare the function *before* `main()`. This is called **forward declaration** if a definition isn't provided simultaneously.
- Provide a definition of the function *after* `main()`.

In other words:

```c++
type function_name(type1 input1, ..., typeN inputN); //Declaration

int main() {
    /* code of the main function */
    return 0;
}

type function_name(type1 input1, ..., typeN inputN){
    //Code block or body (i.e definition)
}
```


## Example 1: single argument

Say we want to implements the function `f(x) = x*x` in C++ and call it once in a `main()` program. A short program for this looks like

```c++
double f(double x); //Declaration

int main() {
    double x = 2;
    double res = f(x); //Should return 2*2 = 4.
    return 0;
}

double f(double x){
    //Provide definition of function here:
    return x*x;
}
```
## Example 2: multiple arguments

Let's do the same with a function of multiple arguments. Assume we're to implement `f(x,y) = x*x + y` and call it once. This can be done as follows.

```c++
double f(double x, double y); //Definition

int main() {
    double x = 2, y = 1;
    double res = f(x, y);
    return 0;
}


double f(double x, double y){
    //Definition:
    return x*x + y;
}
```
