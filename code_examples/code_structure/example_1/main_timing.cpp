// 
// A program that performs timing of algorithm_one and algorithm_two
// 
#include <iostream>
#include <chrono>
#include "utils.hpp"
#include "clever_algorithms.hpp"


int main()
{

  int n_repetitions = 1000;

  // 
  // Time algorithm one
  // 

  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i=0; i < n_repetitions; i++)
  {
    double sum = 0.0;
    algorithm_one(sum);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  double avg_duration_seconds_algo_one = std::chrono::duration<double>(t2 - t1).count() / double(n_repetitions);

  // 
  // Time algorithm two
  // 

  t1 = std::chrono::high_resolution_clock::now();
  for (int i=0; i < n_repetitions; i++)
  {
    double sum = 0.0;
    algorithm_two(sum);
  }
  t2 = std::chrono::high_resolution_clock::now();
  double avg_duration_seconds_algo_two = std::chrono::duration<double>(t2 - t1).count() / double(n_repetitions);

  // Print results
  std::cout << "avg_duration_seconds_algo_one: " << scientific_format(avg_duration_seconds_algo_one) << std::endl;
  std::cout << "avg_duration_seconds_algo_two: " << scientific_format(avg_duration_seconds_algo_two) << std::endl;

  // Done
  return 0;
}