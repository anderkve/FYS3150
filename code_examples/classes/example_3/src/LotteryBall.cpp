// Definitions for the functions in the LotteryBall class

#include "LotteryBall.hpp"


// Constructor
LotteryBall::LotteryBall(std::string color_in, int number_in)
{
  color_ = color_in;
  number_ = number_in;
}


// Method that returns the color
std::string LotteryBall::color()
{
  return color_;
}


// Method that returns the number
int LotteryBall::number()
{
  return number_;
}


// Method that returns a string with info in the form "color number"
std::string LotteryBall::info()
{
  std::string info_string = color_ + " " + std::to_string(number_);
  return info_string;
}


