//
// Defintions for functions declared in utils.hpp
//

#include <sstream>
#include <iomanip>
// By including utils.hpp, we also include all 
// the headers included in utils.hpp (<string>, <vector>)
#include "utils.hpp"


// Return a string with a double in scientific notation
std::string scientific_format(double d, int width, int prec)
{
  std::stringstream ss;
  ss << std::setw(width) << std::setprecision(prec) << std::scientific << d;
  return ss.str();
}


// Return a string with a vector<double> in scientific notation
std::string scientific_format(const std::vector<double>& v, int width, int prec)
{
  std::stringstream ss;
  for(double elem : v)
  {
    ss << scientific_format(elem, width, prec);
  }
  return ss.str();
}
