# Functions, take 1

A **function** in C++ is a code block which is executed only when the function is called. A function takes **arguments**, performs some action, and usually returns some **output**.

## Creating a function

Creating a function in C++ is typically done in two steps:
1. The **declaration**: Specifies the function's name, return type and arguments.
2. The **definition**: Gives the full code block for the function.

A generic example:

```c++
return_type function_name(type_1 argument_1, ..., type_N argument_N)
{
    // The function code block ("function body")
    // If the return_type is not "void", the functino must
    // end with a "return" statement.
}
```

A silly, specific example:

```c++
double add(double a, double b)
{
    return a + b; 
}
```

And here's a silly example function with a `void` return type, meaning that the function simply performs some action but doesn't return anything back to the calling program:

```c++
void say_hello(std::string name)
{
    std::cout << "Hi there, " << name << "!" << std::endl;
}
```

Note that for such `void` functions, the function doesn't end with a `return` statement.


## Separation of declaration and definition

If the function declaration and definition are separated, the function declaration must appear *before* the `main()` function. In practice, the function declaration often appears inside a header file. When a function is declared somewhere before the full function definition is provided, we refer to the declaration as a **forward declaration**.

Below is a simple example with a function `add` which is forward declared and used in the main program, while the corresponding function *definition* appears after the main program. 

```c++
#include <iostream>

// Forward declaration
double add(double x, double y); 


// Main function
int main() 
{
    double x = 1.2;
    double y = 3.4;

    double sum = add(x, y);

    std::cout << "The sum is " << sum << std::endl;

    return 0;
}


// The function definition
double add(double x, double y)
{
    return a + y;
}
```

In larger programs, the function definitions are typically put in completely separate `.cpp` files from the main program. 
During the build process, each `.cpp` is first *compiled* to a corresponding object file, and finally these object files are *linked* together to form an executable.