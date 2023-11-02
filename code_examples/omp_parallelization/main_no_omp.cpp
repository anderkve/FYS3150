/*
See description in README.txt

Build: 
g++ -O3 main_no_omp.cpp -o main_no_omp

Run: 
./main_no_omp <A_min> <A_max> <n_A> <n_cycles> <output_file_name>

*/

// #include "omp.h"  // Not needed here, since this example doesn't use OpenMP
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
  const int n_cycles = atoi(argv[4]);
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

    double dummy_result = A;
    for (int j = 0; j < n_cycles; ++j)
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
  }


  // And all was well
  return 0;
}