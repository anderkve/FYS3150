// Definitions for the LotteryMachine class

#include <vector>      // For vector
#include <string>      // For string
#include <stdlib.h>    // For rand (from C). For more powerful random number generation in C++ we should use <random>
#include <stdexcept>   // For runtime_error

#include "LotteryMachine.hpp"
#include "LotteryBall.hpp"


// Constructor that takes a vector of LotteryBall_collection as input
LotteryMachine::LotteryMachine(std::vector<LotteryBall> ball_collection_in)
{
  ball_collection = ball_collection_in;
}


// Method that adds a ball to the machine by copying an input LotteryBall
void LotteryMachine::add_ball(LotteryBall ball_in)
{
  ball_collection.push_back(ball_in);
}


// Method that adds n balls of of a given color. The balls are numbered 1 to n
void LotteryMachine::add_n_balls(int n, std::string color)
{
  for (int i=1; i <= n; i++)
  {
    // Create a new ball with the given number and color
    LotteryBall new_ball(color, i);

    // Add it to the collection, using the add_ball method above
    add_ball(new_ball);
  }
}


// Method that counts returns the number of balls, using the std::vector::size() method
int LotteryMachine::ball_count()
{
  return ball_collection.size();
}


// Method that empties the LotteryMachine, using the std::vector::clear() method
void LotteryMachine::clear_machine()
{
  ball_collection.clear();
}


// Throw an error if the machine is empty. Uses the std::vector::empty() method to check.
void LotteryMachine::error_if_empty()
{
  if(ball_collection.empty())
  {
    throw std::runtime_error("Can't sample an empty LotteryMachine, you know.");
  }
}


// Sample a ball and put it back
LotteryBall LotteryMachine::sample_ball_with_replacement()
{
  // Check that the machine isn't empty
  error_if_empty();

  // Get a random index between 0 and ball_collection.size()
  int ball_index = rand() % ball_collection.size();

  // Return (a copy of) that ball
  return ball_collection[ball_index];
}


// Sample a ball and *don't* put it back
LotteryBall LotteryMachine::sample_ball_without_replacement()
{
  // Check that the machine isn't empty
  error_if_empty();

  // Get a random index between 0 and ball_collection.size()
  int ball_index = rand() % ball_collection.size();

  // Copy the ball
  LotteryBall sampled_ball = ball_collection[ball_index];

  // Delete the ball from the collection, using the std::vector::erase method
  ball_collection.erase(ball_collection.begin() + ball_index);

  // Return the copyy
  return sampled_ball;
}

