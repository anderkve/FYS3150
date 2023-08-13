# Functions, take 1

A **function** in C++ is a code block which is executed only when the function is called. A function takes **arguments**, performs some action, and usually **returns** some result.

Here's a generic example:

```c++
return_type function_name(type_1 argument_1, ..., type_N argument_N)
{
    // The function code block ("function body")

    // If the return_type is not "void", the function must 
    // end with a "return" statement.
}
```

Here's a silly, specific example:

```c++
double add(double a, double b)
{
    return a + b; 
}
```

And here's an example function with a `void` return type, meaning that the function simply performs some action and does not return anything back to the calling program:

```c++
void say_hello(std::string name)
{
    std::cout << "Hi there, " << name << "!" << std::endl;
}
```

Note that for such `void` functions, the function does not end with a `return` statement.


## Declaration vs definition

In C++ there is a difference between a function **declaration** and a function **definition**:

- **Function declaration**: A single code statement that just specifies the function's name, return type and arguments, e.g
  ```c++
  double add(double a, double b);
  ```

- **Function definition**: A complete definition of the function, e.g.
  ```c++
  double add(double a, double b)
  {
      return a + b; 
  }
  ```



## Separation of declaration and definition

If the function definition appears *before* the point in the code where it is used (e.g. in the `main` function), no separate declaration line is needed:

```c++
#include <iostream>

// The function definition
double add(double x, double y)
{
    return a + y;
}

// Main function
int main() 
{
    double x = 1.2;
    double y = 3.4;

    double sum = add(x, y);

    std::cout << "The sum is " << sum << std::endl;

    return 0;
}
```

However, if the function definition is placed *after* the point where it is first used, a function declaration line must be added first:
```c++
#include <iostream>

// Function declaration
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
When a function is declared somewhere before the full function definition is provided, like in the example above, we refer to the declaration as a **forward declaration**.

In larger code projects, function declarations are typically placed inside header (`.hpp`) files that the main program can `#include`, while the corresponding function definitions live in source (`.cpp`) files, completely separate from the `.cpp` file with the `main` program. During the build process, each `.cpp` file is first *compiled* to a corresponding object file, and finally these object files are *linked* together to form an executable.