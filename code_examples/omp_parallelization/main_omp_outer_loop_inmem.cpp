/*
See description in README.txt

Build: 
g++ -O3 main_omp_outer_loop_inmem.cpp -fopenmp -o main_omp_outer_loop_inmem

Run: 
./main_omp_outer_loop_inmem <A_min> <A_max> <n_A> <n_cycles_per_thread> <output_file_basename>

*/

#include "omp.h"  // OpenMP header
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <assert.h>
#include <cmath>
#include <armadillo>


using namespace std;
using namespace arma;

int main(int argc, const char* argv[])
{

  // Check number of command line arguments
  assert(argc == 6);

  // Read command line arguments
  const double A_min = atof(argv[1]);
  const double A_max = atof(argv[2]);
  const int n_A = atoi(argv[3]);
  const int n_cycles_per_thread = atoi(argv[4]);
  const string output_file_basename = argv[5];

  // Matrix to store results
  // All threads will write to this matrix simultaneously, but to separate rows.
  mat results = mat(n_A, 2, fill::zeros);

  
  // 
  // Outer loop over A values
  // 

  const double delta_A = (A_max - A_min) / (n_A - 1);  // n_A points correspond to (n_A - 1) intervals

  #pragma omp parallel // Start parallel region
  {

    // Here we start the parallelized loop over A
    #pragma omp for
    for (int i = 0; i < n_A; ++i)
    {

      double A = A_min + i * delta_A;

      // 
      // Inner loop with some computation for the given A value
      // 

      double dummy_result = A;

      for (int j = 0; j < n_cycles_per_thread; ++j)
      {
        
        // 
        // Some fancy computations go here...
        // 

        // For now let's do something silly, like adding 0 in a computationally expensive way
        dummy_result += ( log10(pow(10,dummy_result)) - log(exp(dummy_result)) ) + ( log10(pow(10,dummy_result)) - log(exp(dummy_result)) ) ;

      }

      // Write all our results for this A step to the results matrix (shared for all threads)
      results(i,0) = A;
      results(i,1) = dummy_result;

    } // End parallelized loop over A

  } // End entire parallel region


  // // Write results to file in the armadillo's default binary format
  // string output_file_name = output_file_basename + ".bin";
  // results.save(output_file_name);

  // Write results to file in csv format
  string output_file_name = output_file_basename + ".csv";
  results.save(output_file_name, csv_ascii);


  // And all was well
  return 0;
}




