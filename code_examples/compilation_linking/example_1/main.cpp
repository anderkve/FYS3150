// A simple program that prints two numbers in different ways.
// Intended for demonstration of compilation and linking.

#include <iostream>
#include "utils.hpp"

int main()
{
  double d1 = 0.000001234567;
  double d2 = 14324.0001;

  // Do some printing
  std::cout << d1 << ", " << d2 << std::endl;

  // Do some nice printing
  int width = 20;
  int prec = 10;
  std::cout << std::setw(width) << std::setprecision(prec) << std::scientific << d1 << ", "
            << std::setw(width) << std::setprecision(prec) << std::scientific << d2 << std::endl;

  // Do some nice printing with the help of our utils function
  std::cout << scientific_format(d1, width, prec) << ", "
            << scientific_format(d2, width, prec) << std::endl;

  return 0;
}