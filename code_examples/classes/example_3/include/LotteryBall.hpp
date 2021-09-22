// Declaration of the LotteryBall class

#ifndef __LotteryBall_hpp__  
#define __LotteryBall_hpp__

#include <string>


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
    LotteryBall(std::string color_in, int number_in);

    // Method that returns the color
    std::string color();

    // Method that returns the number
    int number();

    // Method that returns a string with info in the form "color number"
    std::string info();

};

#endif