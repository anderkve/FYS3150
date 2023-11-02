/*

See description in README.txt

Build: 
g++ main_omp_2.cpp -o main_omp_2 -fopenmp

Run: 
export OMP_NUM_THREADS=<number of threads>
./main_omp_2

*/

#include "omp.h"  // OpenMP header
#include <random>
#include <chrono>
#include <iostream>


using namespace std;


// Main function
int main()
{

  // Use the system clock to get a base seed
  // unsigned int base_seed = chrono::system_clock::now().time_since_epoch().count();
  // ...or set the base seed manually
  unsigned int base_seed = 3599446834;


  // Start a parallel region
  #pragma omp parallel
  {
    // Which thread is this?
    int thread_id = omp_get_thread_num();

    // Create a <random> generator and distribution (uniform distribution 
    // on the integers 1 to 6) private to this thread
    mt19937 generator;
    uniform_int_distribution<int> uniform_dist(1, 6);

    // Seed the generator with a seed that is unique for this thread
    unsigned int my_seed = base_seed + thread_id;
    generator.seed(my_seed);


    // Print the seed. Using a omp critical block just to avoid
    // multiple threads sending output to cout at the same time, 
    // as that can become a bit messy.
    #pragma omp critical
    {
      cout << "thread " << thread_id << ":  my_seed = " << my_seed << endl;
    }


    // Each thread gets to roll a die a few times:
    int n_rolls = 5;
    for (int i = 1; i <= n_rolls; i++)
    {
      int result = uniform_dist(generator);

      #pragma omp critical
      {
        cout << "thread " << thread_id << ":  roll " << i << ":  result = " << result << endl;
      }
    }

  } // End parallel region


  // And we're done
  return 0;
}

