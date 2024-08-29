#include <iostream>

// A function that:
// - uses pass-by-value to get an input of type double
// - returns nothing
void add_one_passbyvalue(double a)
{
  a = a + 1.;
}

// A function that:
// - uses pass-by-value to get an input of type double
// - returns a result of type double
double add_one_passbyvalue_return(double a)
{
  a = a + 1.;
  return a;
}

// A function that:
// - uses pass-by-reference to get an input of type reference-to-double
// - modifes the original variable through this reference
// - returns nothing
void add_one_passbyref(double& a)
{
  a = a + 1.;
}


// Main function
int main()
{

  double x = 1.;
  std::cout << "x = " << x << std::endl; 


  std::cout << "Will now run: add_one_passbyvalue(x)" << std::endl; 
  add_one_passbyvalue(x);

  std::cout << "x = " << x << std::endl; 


  std::cout << "Will now run: x = add_one_passbyvalue_return(x)" << std::endl; 
  x = add_one_passbyvalue_return(x);

  std::cout << "x = " << x << std::endl; 


  std::cout << "Will now run: add_one_passbyref(x)" << std::endl; 
  add_one_passbyref(x);

  std::cout << "x = " << x << std::endl; 


  // We're done
  return 0;
}
