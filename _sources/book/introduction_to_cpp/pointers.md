# Pointers

A **pointer** is a variable that stores a memory address as its value. Usually, we use to store the memory address of some *other* variable. We say that it **points** to the address of that variable.

## Declaration of a pointer

A pointer is declared using the `*` operator. The generic syntax with no assignment is.

```c++
type* pointer_name;
```

```{note}
It's perfectly legitimate to write the following also:
type *pointer_name;
```

## Assigning an address to a pointer

Say we have a variable named `my_variable` and we want to create a pointer named `pointer_to_my_variable` to its address. Generically, we can do this by

```c++
type1 my_variable = some_value;
type1 *pointer_to_my_variable = &my_variable;
```

Two things to note here:
1. Our pointer must have the same type as the variable.
2. The `&` operator extracts the address of the variable when applied to the `my_variable`.

```{note}
The &-operator is sometimes called the "reference" operator. The *-operator is on the other hand called the "dereference" operator.
```

A concrete example:

```c++
double x = 2; //x is assigned the value 2.
double *pointer_to_x = &x; //ptr stores the memory address of x.
```

## Extracting a value from a pointer

The pointer stores the memory address of a variable as its value. But we can still extract the value of a variable from the pointer itself! This is known as **dereferencing** and is facilitated by the `*` operator as follows:

```c++
type1 variable_value = *pointer_to_variable;
```

Expanding the example from last section:

```c++
double x = 2; //x is assigned the value 2.
double *pointer_to_x = &x; //x_ptr stores the memory address of x.

double x_value = *pointer_to_x; //Dereference pointer_to_x (extract value of x).
```
