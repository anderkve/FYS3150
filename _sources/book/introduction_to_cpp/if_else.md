# If else

## Syntax

The general syntax for an **if-else block** in C++ is

```c++
if (condition A)
{
  // Code to run if condition A is true.
}
else if (condition B)
{
  // Code to run if condition B is true.
}
else
{
  // Code to run if both conditions A and B are false.
}
```

Note that both the `else if` and the `else` blocks are optional, that is, you can of course have a single `if` block on its own.


### Example 1

Assume we want to implement a stepwise function that returns the input value if it's positive, otherwise it returns 0. This could look as follows:

```c++
double f(double x)
{
  if (x > 0)
  {
    return x;
  }
  else
  {
    return 0;
  }
}
```

## Inline if tests

We can also write **inline** if-else blocks in C++. The general syntax looks like this:

```c++
variable = (condition) ? expression_if_true : expression_if_false
```

### Example 2

Now let's write the function from example 1 using an inline `if` test instead.

```c++
double f(double x)
{
  return (x > 0) ? x : 0;
}
```

Arguably, this code looks horrible -- it is usually better to use the longer and more readable block format for `if` tests. But for very simple `if` tests, the shorthand version can be handy.
