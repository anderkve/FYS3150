#include <cmath>

extern "C"
{
  double integrand(double x)
  {
    return 2. * (2.0 + std::sin(2 * M_PI * x * x));
  }
}
