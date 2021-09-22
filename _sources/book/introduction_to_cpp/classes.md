# Classes

We'll think of a **class** as a user-defined object that contains:
1. **Member variables**, i.e variables that belongs to the class.
2. **Class methods**, i.e functions that belong to the class.

They provide a flexible way to package code that facilitates creation of readable and easy-to-use C++ programs.

```{note}
For more examples of how to write and use classes, see the code examples [here](https://github.com/anderkve/FYS3150/tree/master/code_examples/classes).
```

## Division of files

We recommend that you structure your code as follows:
1. Place the **declaration** and **defintion** of your class in a header file `class_name.hpp`.
2. Place definitions of all class constructors and class methods in a source file named `class_name.cpp`.

Don't worry, we'll explain how shortly.


## General structure of the class code

### The #include guard

To prevent multiple inclusions when we're dealing with many header and source files, we create a so-called **#include guard** (a.k.a. define guard, a.k.a. header guard) in each header file. The generic structure of an #include guard looks like this:

```c++
#ifndef __filename_hpp__
#define __filename_hpp__

... (the rest of the file) ...

#endif
```
Always do this for header files. The exact name you use (here `__filename_hpp__`) doesn't matter, as long as it is unique to this header file.


### Generic syntax of a class header file

Let's say we want to create a class `MyClass`. The generic structure of a header file `MyClass.hpp` for this class would be

```c++
#ifndef __MyClass_hpp__   
#define __MyClass_hpp__

class MyClass 
{
private:
  // Declaration of variables only accessible from within the class

public:
  // Declaration of constructors, e.g.
  MyClass(arguments);

  // Declaration of destructors, copy constructors, ...

  // Declarations of other class methods, e.g.
  void some_function(arguments);

}; // <-- Note that class bodies end with a semicolon!

#endif
```

(We won't need to worry about destructors, copy constructors and such just yet...)


### Generic syntax of class source file

The corresponding source file (`MyClass.cpp`) would have this structure:

```c++
#include "MyClass.hpp"

// Definitions of constructors
MyClass::MyClass(arguments)
{
  // ...
}

// Definitions of copy constructor, ...

// Definitions of other class methods, e.g. 
void MyClass::some_function(arguments)
{
  // ...
}

```


## Practical example: A straight line.

Let's create a class `Line` that does one simple thing: it returns the value of a straight line of the form `y = c0 + c1*x` at some point `x`.

### The straight line: header file

Following the general structure above, we create a header file `Line.hpp` as follows:

```c++
#ifndef __Line_hpp__
#define __Line_hpp__

class Line 
{
protected:
  double c0_, c1_; // Parameters of a line: y = c0 + c1*x

public:
  // Constructor
  Line(double c0, double c1);

  // Method for evaluating y(x) at some point x
  double eval(double x);
};

#endif
```

A couple notes:
1. We have defined coefficents `c0_` and `c1_` that will store the coefficients of the straight line. The variables are called **member variables** of the class.
2. The trailing underscore on the member variables is there to distinguish them from other variables used in the class. This is just a convention, in this case following the [Google styleguide for C++](https://google.github.io/styleguide/cppguide.html).


### The straight line: source file

In the source file we provide defitions for the **constructor** `Line(double c0, double c1)`, which creates an instance (object) of the class, and our only class method, `double eval(double x)`. Note that in the source file we have to prefix the function names with the class namespace `Line::`. We end up with the following simple source file, `Line.cpp`:

```c++
#include "Line.hpp"

// Definition of the constructor
Line::Line(double c0, double c1)
{
  // Use the input variables (c0, c1) to assign values to the class memeber variables (c0_, c1_)
  c0_ = c0;
  c1_ = c1;
}

// Definition of the eval function
double Line::eval(double x)
{
  // Return the value of a straight line at a point x
  return c0_ + c1_*x;
}

```

### The straight line: using the class

The main program that uses the `Line` class can be as simple as

```c++
#include "Line.hpp"

int main() 
{
  // Create a Line object called my_line, with coefficients c0 = 1.5, c1 = 2.5
  Line my_line = Line(1.5, 2.5); 

  // Evaluate the line y = c0 + c1*x at point x = 2
  double y = my_line.eval(2);

  return 0;
}
```


## Inheritance: base classes and derived classes

*To be continued...*


<!-- 

## Inheritance: superclasses and derived classes.

A **superclass** or **base class** is a class that provides the foundation for other classes.

A **derived class** is a class that in general inherits member variables, constructors and methods from a superclass.

### Syntax of a derived class: header file

```c++
#ifndef DERIVED_CLASS_HPP
#define DERIVED_CLASS_HPP

class DerivedClass : public SuperClass { //Inherits all public and protected from SuperClass
private:
    /* data */

public:
    DerivedClass (arguments);
    virtual ~DerivedClass ();
};

#endif
```

### Syntax of derived class: source file

The syntax of the source file is pretty much identical to the source file of any class. We'll instead provide an example that showcases how to actually use something you inherit from the superclass.


## Practical example: Quadratic polynomial

We'll create a quadratic polynomial by inheriting from the `Line` class, meaning `Line` is the superclass. We'll call our derived class for `Quadratic`.

### Quadratic polynomial: the header file

The header file of the `Quadratic` class, named `quadratic.hpp` looks as follows:

```c++
#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

#include "line.hpp" //Include the superclass header file here.

class Quadratic : public Line { //Inherit protected and public variables, constructors and methods from Line.
private:
    double c0_, c1_, c2_;

public:
    Quadratic (double c0, double c1, double c2); //Constructor
    virtual ~Quadratic (); //Destructor
    double eval(double x); //Computes the value y of the polynomial
};

#endif
```

### Quadratic polynomial: the source file

The source file of the `Quadratic` class looks as follows.

```c++
#include "quadratic.hpp"

Quadratic::Quadratic(double c0, double c1, double c2) : Line(c0, c1){ //Here we reuse the constructor of the Line class. Note the syntax!
    c2_ = c2; //Assign the higher order coefficient. The others are assigned in Line(c0,c1).
}

double Quadratic::eval(double x){
    //Computes the quadratic polynomial value y at x.
    //Reuses Line::eval(x) to compute the contribution from the straight line and tacks on the quadratic explicitly.
    return Line::eval(x) + c2_*x*x;
}

/*
Just an empty destructor
*/
Quadratic::~Quadratic(){}
```

### Quadratic polynomial: using the class
Again, we can write a short program to use the `Quadratic` class:

```c++
#include "quadratic.hpp"
int main() {
  double x = 2; //Point to evaluate the polynomials in
  double c0 = 1, c1 = 1, c2 = 1;
  Quadratic my_quad = Quadratic(c0, c1, c2); //Call constructor and create Quadratic object my_quad.
  double y = my_quad.eval(x); //Compute y = c0 + c1*x + c2*x*x.
  return 0;
}
```

 -->