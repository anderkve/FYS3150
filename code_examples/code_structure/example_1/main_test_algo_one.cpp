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
  std::cout << "sum before running algorithm_one: " << scientific_format(sum) << std::endl;

  algorithm_one(sum);

  std::cout << "sum after running algorithm_one: " << scientific_format(sum) << std::endl;



  // Done
  return 0;
}