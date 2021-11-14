/*

See description in README.txt

Build: 
g++ main_rng_in_class_omp.cpp -o main_rng_in_class_omp.exe -fopenmp

Run: 
export OMP_NUM_THREADS=<number of threads>
./main_rng_in_class_omp.exe

*/

#include "omp.h"  // OpenMP header
#include <random>
#include <chrono>
#include <iostream>


using namespace std;


// Let's define a class RandomWalker here. In a larger code we should use 
// separate RandomWalker.hpp and RandomWalker.cpp files for this (and not use
// "using namespace std" in the header file).

class RandomWalker
{

public:
  // Member variables that hold a <random> generator 
  // and distribution (uniform distribution [0,1)).
  mt19937 generator;
  uniform_real_distribution<double> uniform_dist = uniform_real_distribution<double>(0.0 ,1.0);

  // Current state
  int current_state = 0;


  // Constructor
  RandomWalker() { }

  // Generate random state by adding or subtracting 1
  void generate_new_state()
  {
    double r = uniform_dist(generator);
    if (r < 0.5)
    {
      current_state--;
    }
    else
    {
      current_state++;;
    }
  }
};



// Main function
int main()
{

  // Use the system clock to get a base seed
  unsigned int base_seed = chrono::system_clock::now().time_since_epoch().count();

  // Start a parallel region
  #pragma omp parallel
  {
    // Which thread is this?
    int thread_id = omp_get_thread_num();

    // Create a RandomWalker that is private to this thread
    RandomWalker my_walker;

    // Seed the generator in my_walker with a seed that is unique for this thread
    unsigned int my_seed = base_seed + thread_id;
    my_walker.generator.seed(my_seed);

    // Print starting position. Using a omp critical block just to avoid
    // multiple threads sending output to cout at the same time, as that can become
    // a bit messy.
    #pragma omp critical
    {
      cout << "thread " << thread_id << ":  my_walker.current_state = " << my_walker.current_state << endl;
    }

    // Take my_walker for a random walk
    int n_steps = 10;
    for (int i = 0; i < n_steps; i++)
    {
      my_walker.generate_new_state();

      #pragma omp critical
      {
        cout << "thread " << thread_id << ":  my_walker.current_state = " << my_walker.current_state << endl;
      }
    }

  } // End parallel region


  // And everyone agreed it had been a nice walk.
  return 0;
}

