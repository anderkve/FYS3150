/*
See description in README.txt

Build: 
g++ -O3 main_omp_outer_loop.cpp -fopenmp -o main_omp_outer_loop

Run: 
./main_omp_outer_loop <A_min> <A_max> <n_A> <n_cycles_per_thread> <output_file_name>

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

  
  // 
  // Outer loop over A values
  // 

  const double delta_A = (A_max - A_min) / (n_A - 1);  // n_A points correspond to (n_A - 1) intervals

  #pragma omp parallel // Start parallel region
  {

    // Prepare for file output
    static int print_prec = 10;

    // Each thread will get its own output file name
    const int my_thread = omp_get_thread_num();
    ofstream ofile;
    string my_output_file_name = output_file_name + ".thread_" + to_string(my_thread);
    ofile.open(my_output_file_name.c_str(), ofstream::trunc);  // ofstream::trunc makes sure old content is deleted

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

      // Write results for this A value
      ofile << setprecision(print_prec) << scientific << A << ", "
            << setprecision(print_prec) << scientific << dummy_result << endl;

    } // End parallelized loop over A

  } // End entire parallel region

  // And all was well
  return 0;
}




