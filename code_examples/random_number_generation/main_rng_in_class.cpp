/*

See description in README.txt

Build: 
g++ main_rng_in_class.cpp -o main_rng_in_class.exe

Run: 
./main_rng_in_class.exe

*/

#include <random>
#include <chrono>
#include <iostream>


using namespace std;


// Let's define a class RandomWalker here. In a larger code we should use 
// separate RandomWalker.hpp and RandomWalker.cpp files for this (and not use
// "using namespace std" in the header file.)

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
  // Create a RandomWalker. Let's call him Mr. Walker.
  RandomWalker mr_walker;


  // Seed the generator in mr_walker using the system clock
  unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
  mr_walker.generator.seed(seed);

  // Seed the generator in mr_walker with the specific seed
  // mr_walker.generator.seed(120473);


  // Print starting position
  cout << "mr_walker.current_state = " << mr_walker.current_state << endl;


  // Take Mr Walker for a random walk
  int n_steps = 10;
  for (int i = 0; i < n_steps; i++)
  {
    mr_walker.generate_new_state();
    cout << "mr_walker.current_state = " << mr_walker.current_state << endl;
  }


  // It's been a nice walk. Bye, Mr Walker.
  return 0;
}

