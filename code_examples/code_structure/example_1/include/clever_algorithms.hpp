//
// A collection of "clever" algorithms
//

// First we add an "include guard". It ensures that this header file can 
// only end up being included *once* for the compilation of any given .cpp file
#ifndef __clever_algorithms_hpp__  
#define __clever_algorithms_hpp__

// Algorithm one: adds 1000 to the input number in a silly way.
// Note: Here we use "call by reference" (the & in the argument). This
// means that this function can change the value of the original input
// variable, instead of returning a new variable. (Hence "void" as return type.)
void algorithm_one(double& result);

// Algorithm two: adds 1000 to the input number in a twice as silly way
void algorithm_two(double& result);

#endif  // end of include guard __utils_hpp__