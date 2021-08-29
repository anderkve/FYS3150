# Variables

Variables are containers for storing data.

There are several **types** of variables. We'll list a few here:

- `int` stores integers.
- `double` stores floating point numbers (kind of like numbers on the real axis, but limited by machine precision).
- `char` stores single characters, for instance the letter `a`.
- `string` stores text strings, e.g it can store `"Hello world!"`.
- `bool` stores one of either two states: `true` or `false`.

## Declaration of Variables

**Declaration** means to create a variable. We must specify a **type** and a variable name, called an **identifier**. Optionally we can assign a value to the variable. The generic syntax is

```c++
type variable_name = value;
```

For example,

```c++
double x = 2;
```

declared a variable named `x` assigned the value `2`.

As stated, we need not specify the value of the declared variable. Statements like

```c++
type variable_name;
```

are perfectly legitimate. You can assign a value to the declared variable at later point in the code. However, it's considered good practice to declare the variable as close to its assignment as possible.


### Declaration of multiple variables:

We can declare multiple variables at once. For example

```c++
double x, y = 0, z;
```

This declares three variables `x`, `y` and `z`. It only assigns `y = 0`, while the other two are currently not assigned a specific value by us.
