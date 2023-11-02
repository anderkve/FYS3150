/*
See description in README.txt

Build: 
g++ -O3 main_omp_inner_loop.cpp -fopenmp -o main_omp_inner_loop

Run: 
./main_omp_inner_loop <A_min> <A_max> <n_A> <n_cycles_per_thread> <output_file_name>

*/

#include "omp.h"  // OpenMP header
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <assert.h>
#include <cmath>


using namespace std;

int main(int argc, const char* argv[])
{

  // Check number of command line arguments
  assert(argc == 6);

  // Read command line arguments
  const double A_min = atof(argv[1]);
  const double A_max = atof(argv[2]);
  const int n_A = atoi(argv[3]);
  const int n_cycles_per_thread = atoi(argv[4]);
  const string output_file_name = argv[5];

  // Prepare for file output
  const int print_prec = 10;
  ofstream ofile;
  ofile.open(output_file_name.c_str(), ofstream::trunc);  // ofstream::trunc makes sure old content is deleted


  // 
  // Outer loop over A values
  // 

  const double delta_A = (A_max - A_min) / (n_A - 1);  // n_A points correspond to (n_A - 1) intervals

  for (int i = 0; i < n_A; ++i)
  {

    double A = A_min + i * delta_A;

    // 
    // Inner loop with some computation for the given A value
    // 

    double dummy_result = 0;

    #pragma omp parallel // Start parallel region
    {
      const int n_threads = omp_get_num_threads();
      const double weight = 1.0 / n_threads;

      double my_dummy_result = A;

      // In this example we *don't* ask OpenMP to split up the inner loop (with "#pragma omp for").
      // Rather, n_cycles_per_thread refers to the number of cycles for each thread. 
      //
      // So if we want faster execution speed while keeping the total number of cycles constant, we
      // we could run with more threads and reduce n_cycles_per_thread value correspondingly.

      // If we rather want to perform more cycles (e.g. collect more MCMC samples) in the same total 
      // time, we simply increase the number of threads and keep n_cycles_per_thread unchanged
      for (int j = 0; j < n_cycles_per_thread; ++j)
      {

        // 
        // Some fancy computations go here...
        // 

        // For now let's do something silly, like adding 0 in a computationally expensive way
        my_dummy_result += ( log10(pow(10,my_dummy_result)) - log(exp(my_dummy_result)) ) + ( log10(pow(10,my_dummy_result)) - log(exp(my_dummy_result)) ) ;

      } // End parallelized loop

      // Now let dummy_result be average result across threads
      #pragma omp critical
      {
        dummy_result += weight * my_dummy_result;
      }

    } // End entire parallel region


    // Write results for this A value
    ofile << setprecision(print_prec) << scientific << A << ", "
          << setprecision(print_prec) << scientific << dummy_result << endl;

  } // End parallelized loop over A

  // And all was well
  return 0;
}




