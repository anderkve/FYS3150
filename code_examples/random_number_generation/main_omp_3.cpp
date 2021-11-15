/*

See description in README.txt

Build: 
g++ main_omp_3.cpp src/omp_rng.cpp -I include -o main_omp_3.exe -fopenmp

Run: 
export OMP_NUM_THREADS=<number of threads>
./main_omp_3.exe

*/

#include "omp.h"  // OpenMP header
#include <random>
#include <chrono>
#include <iostream>
#include "omp_rng.hpp"


using namespace std;


// Main function
int main()
{

  // Use the system in omp_rng.hpp to create one random number generator per thread.
  omp_rng::initialize_omp_rng_container(123024);  // Set base seed manually
  // omp_rng::initialize_omp_rng_container(-1);  // Set base seed to -1 to seed using the system clock

  // Start a parallel region
  #pragma omp parallel
  {
    // Which thread is this?
    int thread_id = omp_get_thread_num();

    // Each thread gets to roll a die a few times:
    int n_rolls = 5;
    for (int i = 1; i <= n_rolls; i++)
    {
      // When called inside a parallel region, the random number functions in omp_rng will 
      // use the random number generator of the current thread.
      int result = omp_rng::get_random_int_1_6();

      #pragma omp critical
      {
        cout << "thread " << thread_id << ":  roll " << i << ":  result = " << result << endl;
      }
    }

  } // End parallel region


  // And we're done
  return 0;
}

