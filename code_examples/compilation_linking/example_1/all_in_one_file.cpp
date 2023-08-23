// Everything from main.cpp, utils.hpp and utils.cpp 
// contained in a single-file program, to illustrate 
// the difference between function *declarations* 
// and function *definitions*.

// Build: g++ all_in_one_file.cpp -o all_in_one_file
// Usage: ./all_in_one_file 


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// Here we give some function *declarations*. 
// These are just single statements showing the 
// function names, argument types and return type.
// 
// The function *definitions* (the actual function
// code) can then be put below the main function.

// Return a string with a double in scientific notation
std::string scientific_format(double d, int width=20, int prec=10);

// Return a string with a vector<double> in scientific notation
std::string scientific_format(const std::vector<double>& v, int width=20, int prec=10);


// ----------


// Here's the main function, which makes use of one of 
// the functions we have declared above.

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


// ----------


// Here we give the actual *definitions* of the 
// two scientific_format functions declared above.

// Return a string with a double in scientific notation
std::string scientific_format(double d, int width, int prec)
{
  std::stringstream ss;
  ss << std::setw(width) << std::setprecision(prec) << std::scientific << d;
  return ss.str();
}


// Return a string with a vector<double> in scientific notation
std::string scientific_format(const std::vector<double>& v, int width, int prec)
{
  std::stringstream ss;
  for(double elem : v)
  {
    ss << scientific_format(elem, width, prec);
  }
  return ss.str();
}

