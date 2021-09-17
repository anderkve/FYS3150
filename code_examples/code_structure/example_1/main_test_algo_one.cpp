// 
// A program that tests algorithm_one
// 
#include <iostream>
#include <chrono>
#include "utils.hpp"
#include "clever_algorithms.hpp"

int main()
{
  double sum = 0.0;
  std::cout << "Value of variable 'sum' before running algorithm_one: " << scientific_format(sum) << std::endl;

  // Note: since the function "algorithm_one" uses call-by-reference (see the function signature 
  // in include/clever_algorithms.hpp), the function can change the value of the original variable 
  // "sum" that we pass as input.
  algorithm_one(sum);

  std::cout << "Value of variable 'sum' after running algorithm_one: " << scientific_format(sum) << std::endl;

  // Done
  return 0;
}