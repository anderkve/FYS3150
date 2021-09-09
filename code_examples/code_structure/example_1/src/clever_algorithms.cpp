//
// Definitions for the algorithms declared in clever_algorithms.hpp
//

#include "clever_algorithms.hpp"


// Algorithm one: adds 1000 to the input number in a silly way
void algorithm_one(double& result)
{
  // Spend some time doing addition
  for(int i=0; i<1000000; i++)
  {
    result += 0.001;
  }
}


// Algorithm two: adds 1000 to the input number in a twice as silly way
void algorithm_two(double& result)
{
  // Spend some more time doing addition
  for(int i=0; i<2000000; i++)
  {
    result += 0.0005;
  }
}

