// The LotteryMachine class

#ifndef __LotteryMachine_hpp__  
#define __LotteryMachine_hpp__

#include <string>
#include <vector>
#include <LotteryBall.hpp>  // Some of the declarations below need the LotteryBall type


class LotteryMachine
{
  // Private stuff 
  private:

    // The LotteryMachine holds a collection of LotteryBalls
    std::vector<LotteryBall> ball_collection_;

  // Public stuff
  public:

    // Constructor that creates an empty LotteryMachine
    LotteryMachine() {}

    // Constructor that takes a vector of LotteryBall_collection as input
    LotteryMachine(std::vector<LotteryBall> ball_collection_in);

    // Method that adds a ball to the machine by copying an input LotteryBall
    void add_ball(LotteryBall ball_in);

    // Method that adds n balls of of a given color. The balls are numbered 1 to n
    void add_n_balls(int n, std::string color);

    // Method that counts returns the number of balls, using the std::vector::size() method
    int ball_count();

    // Throw an error if the machine is empty. Uses the std::vector::empty() method to check.
    void error_if_empty();

    // Sample a ball and put it back
    LotteryBall sample_ball_with_replacement();

    // Sample a ball and *don't* put it back
    LotteryBall sample_ball_without_replacement();
};


#endif