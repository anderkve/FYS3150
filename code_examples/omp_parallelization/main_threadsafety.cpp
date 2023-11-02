/*
See description in README.txt

Build: 
g++ main_threadsafety.cpp -fopenmp -o main_threadsafety

Run: 
./main_threadsafety

*/

#include "omp.h"  // OpenMP header
#include <iostream>

using namespace std;


int main(int argc, const char* argv[])
{

  // ==================================

  // Part 1:
  // 
  // A non-parallelized dummy code that we'll use as starting point
  // for the parallelized examples below

  int x = 0;

  int thread_num = omp_get_thread_num();  // This will just return 0, since we're not in a parallel block
  
  for (int i = 0; i < 5; i++)
  {

    // Waste some time, to emulate some computation
    double d = 0;
    for (int j = 0; j < 1000; j++) 
    { 
      d += 1.0;
    } 

    // Print current state
    cout << "thread: " << thread_num << "    x memory address: " << &x << "    x value: " << x << endl;

    // Move it
    x += 1;
  }


  // ==================================


  // Part 2: 
  // 
  // Parallelized code where the variable x is declared outside
  // the parallel region and is therefore shared among all the 
  // threads. 
  // 
  // Unless this design is intentional, this is an example
  // of a non-threadsafe code, where computations on different
  // threads can interfere with each other as they modify the same
  // part of memory.

  // int x = 0;

  // #pragma omp parallel
  // {
  //   int thread_num = omp_get_thread_num();

  //   for (int i = 0; i < 5; i++)
  //   {

  //     // Waste some time, to emulate some computation each thread must do
  //     double d = 0;
  //     for (int j = 0; j < 1000; j++) 
  //     { 
  //       d += 1.0;
  //     } 

  //     // Print current state
  //     #pragma omp critical  // <-- Code in a "ciritical block" is only run one thread at a time. Avoids garbled screen output.
  //     {
  //       cout << "thread: " << thread_num << "    x memory address: " << &x << "    x value: " << x << endl;
  //     }

  //     // Move it
  //     x += 1;
  //   }
  // }


  // ==================================


  // Part 3: 
  // 
  // Same as part 2, but now the declaration of the variable x
  // is moved inside the parallel region. As a consequence, 
  // this variable is private to each thread. That is, each
  // thread is working with each own instance of the variable x.
  // (Notice how the printout shows that each thread has a unique memory 
  //  address for its varible x.)

  // #pragma omp parallel
  // {
  //   int x = 0;
  
  //   int thread_num = omp_get_thread_num();

  //   for (int i = 0; i < 5; i++)
  //   {

  //     // Waste some time, to emulate some computation each thread must do
  //     double d = 0;
  //     for (int j = 0; j < 1000; j++) 
  //     { 
  //       d += 1.0;
  //     } 

  //     // Print current state
  //     #pragma omp critical
  //     {
  //       cout << "thread: " << thread_num << "    x memory address: " << &x << "    x value: " << x << endl;
  //     }

  //     // Move it
  //     x += 1;
  //   }
  // }


  // And all was well
  return 0;
}