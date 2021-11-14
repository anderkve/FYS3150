#ifndef __omp_rng_hpp__  
#define __omp_rng_hpp__

#include "omp.h"
#include <vector>
#include <random>
#include <chrono>

// Put this in its own namespace, just to keep things tidy and neat
namespace omp_rng
{

  // Create a single, global vector to store mt19937 generators
  static std::vector<std::mt19937> omp_rng_container;

  // Initialize the omp_rng_container according to the number of threads
  void initialize_omp_rng_container(unsigned int base_seed=-1);

  // 
  // Below we can add functions that use the generators in 
  // omp_rng_container to sample from various distributions
  // 

  // Sample a random double in [0.0, 1.0)
  double get_random();

  // Sample a random integer 0 or 1
  int get_random_int_0_1();

  // Sample a random integer from 1 to 6
  int get_random_int_1_6();

}

#endif
