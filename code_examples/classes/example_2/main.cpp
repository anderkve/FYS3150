#include <iostream>    // For cout, endl
#include <vector>      // For vector
#include <string>      // For string
#include <stdlib.h>    // For rand (from C). For more powerful random number generation in C++ we should use <random>
#include <time.h>      // For time (from C)
#include <stdexcept>   // For runtime_error


// ==========================


class LotteryBall
{
  // Private stuff 
  // (No one is allowed to change the color or number of a LotteryBall -- that's cheating!)
  private:

    std::string color_;  // The underscore is just a one possible naming convention for private variables
    int number_;

  // Public stuff
  public:

    // Constructor
    LotteryBall(std::string color_in, int number_in)
    {
      color_ = color_in;
      number_ = number_in;
    }

    // Method that returns the color
    std::string color()
    {
      return color_;
    }

    // Method that returns the number
    int number()
    {
      return number_;
    }

    // Method that returns a string with info in the form "color number"
    std::string info()
    {
      std::string info_string = color_ + " " + std::to_string(number_);
      return info_string;
    }

};


// ==========================


class LotteryMachine
{
  // Private stuff 
  private:

    // The LotteryMachine holds a collection of LotteryBalls
    std::vector<LotteryBall> ball_collection;


  // Public stuff
  public:

    // Constructor that creates an empty LotteryMachine
    LotteryMachine() {}

    // Constructor that takes a vector of LotteryBall_collection as input
    LotteryMachine(std::vector<LotteryBall> ball_collection_in)
    {
      ball_collection = ball_collection_in;
    }

    // Method that adds a ball to the machine by copying an input LotteryBall
    void add_ball(LotteryBall ball_in)
    {
      ball_collection.push_back(ball_in);
    }

    // Method that adds n balls of of a given color. The balls are numbered 1 to n
    void add_n_balls(int n, std::string color)
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
    int ball_count()
    {
      return ball_collection.size();
    }

    // Throw an error if the machine is empty. Uses the std::vector::empty() method to check.
    void error_if_empty()
    {
      if(ball_collection.empty())
      {
        throw std::runtime_error("Can't sample an empty LotteryMachine, you know.");
      }
    }

    // Sample a ball and put it back
    LotteryBall sample_ball_with_replacement()
    {
      // Check that the machine isn't empty
      error_if_empty();

      // Get a random index between 0 and ball_collection.size()
      int ball_index = rand() % ball_collection.size();

      // Return (a copy of) that ball
      return ball_collection[ball_index];
    }

    // Sample a ball and *don't* put it back
    LotteryBall sample_ball_without_replacement()
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
};


// ==========================


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