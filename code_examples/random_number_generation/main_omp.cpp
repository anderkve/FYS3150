/*

See description in README.txt

Build: 
g++ main_omp.cpp -o main_omp.exe -fopenmp

Run: 
export OMP_NUM_THREADS=<number of threads>
./main_omp.exe

*/

#include "omp.h"  // OpenMP header
#include <random>
#include <chrono>
#include <iostream>


using namespace std;


// Main function
int main()
{

  // Use the system clock to get a seed
  unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
  // ...or set the base seed manually
  // unsigned int seed = 831923;

  // Create a <random> generator and distribution (uniform distribution 
  // on the integers 1 to 6) private to this thread
  mt19937 generator(seed);
  uniform_int_distribution<int> uniform_dist(1, 6);


  // Start a parallel region
  #pragma omp parallel
  {
    // Which thread is this?
    int thread_id = omp_get_thread_num();

    // Each thread gets to roll a die a few times:
    int n_rolls = 5;
    for (int i = 1; i <= n_rolls; i++)
    {
      // Here all threads will use a single, shared generator
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

