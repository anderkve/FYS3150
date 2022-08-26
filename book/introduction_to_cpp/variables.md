# Variables

We use variables to hold information in memory. There is a large number of different **types** of variables -- here we'll only list some of the most basic and common types:

- `int` stores integers (positive or negative).
- `unsigned int` stores non-negative integers.
- `double` stores floating point numbers (kind of like numbers on the real axis, but limited by machine precision).
- `bool` stores one of two states: `true` or `false`.
- `char` stores single characters, for instance the letter 'a'.
- `std::string` stores text strings, e.g it can store "Hello world!".

We'll encounter many more variable types throughout the course -- and also make some new types (classes) ourselves.

## C++ cares a lot about variable types

In Python one can do crazy stuff like e.g. changing a variable from an integer to a string like this:

```python
x = 10
x = "Oh, I'm a string now!"
```

In C++ this is not allowed -- you would have to use two different variables, one declared to be of type `int` and one declared to be of type `std::string`. So let's discuss variable declarations.


## Declaration of variables

**Declaration** means to create a new variable by specifying a **type** and a variable name (**identifier**). A few examples of declarations:

```c++
int i;
double d;
std::string s;
```

Now that we have some declared variables, we can assign some **values** to them in the way you'd expect:

```c++
i = 10;
d = 3.14;
s = "Hi there!;
```

Often it is useful to do both the declaration and the value assignment as one code statement, like in these examples:

```c++
int i = 10;
double d = 3.14;
std::string s = "Hi there!;
```

We can also declare multiple variables at once:

```c++
double x, y = 1.0, z;
```

Here we declare three variables `x`, `y` and `z` to be of type double, but only assign a specific value to the variable `y`.


## What does `const` mean?

In C++ code you will quite frequently see the word `const` in variable declarations, e.g. 

```c++
const std::string planet_name = "Earth";
const double g = 9.8;
```

This specifies that these variables hold *constant* values, i.e. the variables are never never allowed to change. If you try to do so, e.g. like this

```c++
const double g = 9.8;
g = 1.6;
```

you will get a compilation error. Declaring variables to be `const` can help to

- communicate to others reading your code how you intend to use a variable; and 

- detect potential bugs and/or code design mistakes.

We will get back to `const` when we discuss input arguments for functions.


## Scope -- where does my variable live?

In Python, a silly code like this 

```python
if True:
  s = "Hello!"

print(s)
```

will give the output

```
Hello!
```

That is, even though the variable `s` is created *inside* the `if` block, it still persists in memory after the `if` block, meaning that the statement `print(s)` will run without complaining.

The equivalent code in C++ would be:

```c++
if (true)
{
  std::string s = "Hello!";
}

std::cout << s;
```

This code will *not* work. The compilation error will point to the `std::cout` statement and say something like

```
error: use of undeclared identifier 's'
```

The reason is that in C++ the variable `s` that we created inside the `if` block is *deleted* once that code block or **scope** ends, which happens when we reach the closing `}`.

However, the following code will work:

```c++
std::string s;

if (true)
{
  s = "Hello!";
}

std::cout << s;
```

Here we create the variable `s` in the outer scope, which means `s` is still alive when we reach the `std::cout` statement.

In this example we used an `if` block to illustrate the scope concept. It works the same way for other code blocks contained within curly brackets, like `for` loops, function bodies, etc.


