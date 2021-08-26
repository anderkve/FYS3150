# Classes

We'll think of a **class** as a user-defined object that contains:
1. Variables
2. **Class methods** or functions that belong to the class.

They provide a flexible way to package code that facilitates creation of readable and easy-to-use C++ programs.

## Division of files

We recommend that you structure your code as follows:
1. Place the **declaration** and **defintion** of your class in a header file `class_name.hpp`.
2. Place definitions of all class constructors and class methods in a source file named `class_name.cpp`.

Don't worry, we'll explain how shortly.


## General structure of the class code

### The #define Guard

To prevent multiple inclusion when we're dealing with many header and source files, we create a so-called **#define guard** in each header file. The generic structure of a #define guard looks like this:

```c++
#ifndef CLASS_NAME_HPP
#define CLASS_NAME_HPP

...

#endif
```
Always do this.

### Generic syntax of header file


The generic structure of a class header file is a follows:

```c++
#ifndef CLASS_NAME_HPP   
#define CLASS_NAME_HPP

class MyClass {
private:
    /* declaration of variables only accessible from within the class*/

public:
    /* Declaration of constructor, destructor and class methods. */
    MyClass (arguments); //Constructor
    virtual ~MyClass (); //Destructor
};

#endif
```


### Generic syntax of class source file

```c++
#include "class_name.hpp"

MyClass::MyClass(arguments){
  //definition of constructor
}

//Definitions of other class methods come here.
```


## Practical example: A straight line.

Let's create a class that does one simple thing: it returns the value of a straight line of the form `y = c0 + c1*x` at some point `x`.

### The straight line: header file

Using the theory above, we define a header file we call `line.hpp` as follows:

```c++
#ifndef LINE_HPP
#define LINE_HPP

class Line {
protected:
    double c0_, c1_; //Parameters of a line: y = c0 + c1*x.
public:
    Line(double c0, double c1); //Constructor
    virtual ~Line ();

    double compute_val(double x); //Compute value y at point (x, y) given x.
};
#endif
```

A couple notes:
1. We have defined coefficents `c0_` and `c1_` that will store the coefficients of the straight line. The variables are called **member variables** of the class.
2. The trailing underdash on the member variables is there to distinguish them from other variables used in the class. The trailing underdash convention follows the [Google styleguide for C++](https://google.github.io/styleguide/cppguide.html).

### The straight line: source file

In the source file we provide a defition of the **constructor** which creates the class object and all its class methods. For the straight line class, we get a pretty simple source file:

```c++
#include "line.hpp"

//This is how a constructor looks like in practice in the source file
Line::Line(double c0, double c1){
    //Assign member variables c0_ and c1_ to input variables c0 and c1, respectively.
    c0_ = c0;
    c1_ = c1;
}

double Line::compute_val(double x){
    //Returns the value of a straight line for an input x.
    return c0_ + c1_*x;
}
```

### The straight line: using the class
The main program that uses the `Line` class can be as simple as

```c++
#include "line.hpp"

int main(int argc, char const *argv[]) {
    double x = 2; //Point to evaluate the polynomials in
    double c0 = 1, c1 = 1; //Coefficients of the straight line.
    Line my_line = Line(c0, c1); //Create a Line object called my_line
    double y = my_line.compute_val(x); //Compute y = c0 + c1*x for a given x.
    return 0;
}
```


## Inheritance: superclasses and derived classes.

A **superclass** or a **base class** is a class that provides the foundation for other classes. It in itself does not inhert or **derive** anything from another class.

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

The syntax of the source file is pretty much identical to the source file of any class. We'll instead show an example on how to actually use something you inherit from the superclass.


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
    double compute_val(double x); //Computes the value y of the polynomial
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

double Quadratic::compute_val(double x){
    //Computes the quadratic polynomial value y at x.
    //Reuses Line::compute_val(x) to compute the contribution from the straight line and tacks on the quadratic explicitly.
    return Line::compute_val(x) + c2_*x*x;
}
```

### Quadratic polynomial: using the class
Again, we can write a short program to use the `Quadratic` class:

```c++
    double x = 2; //Point to evaluate the polynomials in
    double c0 = 1, c1 = 1, c2 = 1;
    Quadratic my_quad = Quadratic(c0, c1, c2); //Call constructor and create Quadratic object my_quad.
    double y = my_quad.compute_val(x); //Compute y = c0 + c1*x + c2*x*x.
```
