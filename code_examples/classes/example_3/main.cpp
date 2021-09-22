#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <stdlib.h>    // For rand (from C). For more powerful random number generation in C++ we should use <random>
#include <time.h>      // For time (from C)

#include "LotteryBall.hpp"
#include "LotteryMachine.hpp"


// 
// Main program
// 
int main()
{
  // Let's seed the random number generator (rand) with the current time.
  // (We'll discuss random numbers more properly when we get to Monte Carlo methods)
  srand(time(NULL));

  // Create an empty LotteryMachine .
  // (This is calling the LotterMachine constructor that takes no arguments.)
  LotteryMachine my_machine;

  // Let's fill it with 5 blue and 5 red LotteryBalls
  my_machine.add_n_balls(5, "red");
  my_machine.add_n_balls(5, "blue");

  // Let's create a special LotteryBall with color "gold"
  LotteryBall golden_ball("gold", 1);

  // Add it to the machine
  my_machine.add_ball(golden_ball);


  // Let's sample *with* replacement and print the result
  int n_samples = 5;

  std::cout << std::endl;
  std::cout << "Machine has " << my_machine.ball_count() << " balls." << std::endl;
  std::cout << "Will now sample " << n_samples << " balls with replacement:" << std::endl;

  for(int i=1; i<=n_samples; i++)
  {
    LotteryBall sampled_ball = my_machine.sample_ball_with_replacement();
    std::cout << "  sample " << i << ": " << sampled_ball.info() << std::endl;
  }


  // Let's sample *without* replacement and print the result
  n_samples = 5;

  std::cout << std::endl;
  std::cout << "Machine has " << my_machine.ball_count() << " balls." << std::endl;
  std::cout << "Will now sample " << n_samples << " balls without replacement:" << std::endl;

  for(int i=1; i<=n_samples; i++)
  {
    LotteryBall sampled_ball = my_machine.sample_ball_without_replacement();
    std::cout << "  sample " << i << ": " << sampled_ball.info() << std::endl;
  }

  // We're done and all is well.
  return 0;
}