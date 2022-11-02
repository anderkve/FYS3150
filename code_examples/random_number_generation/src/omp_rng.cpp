#include <random>
#include <chrono>
#include "omp_rng.hpp"

using namespace std;

namespace omp_rng
{

  // Initialize the omp_rng_container according to the number of threads
  void initialize_omp_rng_container(unsigned int base_seed)
  {

    // Let thread 0 add one generator to omp_rng_container for each thread
    #pragma omp parallel
    {
      // Which thread am I?
      int thread_id = omp_get_thread_num();    

      // Let thread 0 do the admin work
      if (thread_id==0)
      {
        // How many threads available in total?
        int n_threads = omp_get_num_threads();

        // If the base_seed isn't set, use the system clock
        if (base_seed == -1)
        {
          base_seed = chrono::system_clock::now().time_since_epoch().count();
        }

        // Add one generator per thread. Seed each generator with base_seed + thread number
        for (int i = 0; i < n_threads; i++)
        {
          mt19937 my_generator(base_seed + i);
          omp_rng_container.push_back(my_generator);
        }

      }

      // Don't let any thread run past this point and try using 
      // the random number generators until thread 0 is done creating them
      #pragma omp barrier

    } // End parallel region

  }


  // Sample a random double in [0.0, 1.0)
  double get_random()
  {
    static uniform_real_distribution<double> distribution(0.0, 1.0);

    // Sample a number using the generator for the current thread
    int thread_id = omp_get_thread_num();
    double r = distribution(omp_rng_container.at(thread_id));

    return r;
  }


  // Sample a random integer 0 or 1
  int get_random_int_0_1()
  {
    static uniform_int_distribution<int> distribution(0,1);

    // Sample a number using the generator for the current thread
    int thread_id = omp_get_thread_num();
    int r = distribution(omp_rng_container.at(thread_id));

    return r;
  }


  // Sample a random integer from 1 to 6
  int get_random_int_1_6()
  {
    static uniform_int_distribution<int> distribution(1,6);
    
    // Sample a number using the generator for the current thread
    int thread_id = omp_get_thread_num();
    int r = distribution(omp_rng_container.at(thread_id));

    return r;
  }

}
