//
// A collection of useful functions
//


// First we add an "include guard". It ensures that this header file can 
// only end up being included *once* for the compilation of any given .cpp file
#ifndef __utils_hpp__  
#define __utils_hpp__

// Now we include headers we need
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


// Below we give some function *declarations*.
// The function *definitions* (the actual code) 
// lives in src/utils.cpp

// Return a string with a double in scientific notation
std::string scientific_format(double d, int width, int prec);

// Return a string with a vector<double> in scientific notation
std::string scientific_format(const std::vector<double>& v, int width, int prec);

#endif  // end of include guard __utils_hpp__