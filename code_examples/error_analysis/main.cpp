// 
// This program computes an approximation to the second derivative of
// u(x) = exp(2x) at a single point x, using different stepsizes h
// 
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

// 
// Useful functions
// 

// Example function: u(x) = exp(2x)
double u(double x)
{
  return exp(2.*x);
}

// Exact second derivative: u''(x) = 4 exp(2x)
double calc_d2u_exact(double x)
{
  return 4.*exp(2.*x);
}

// Approximation of second derivative: (u(x+h) - 2*u(x) + u(x-h)) / h^2 
double calc_d2u_approx(double x, double h)
{
  return (u(x+h) - 2*u(x) + u(x-h)) / (h*h);
}



// 
// Main program
// 

int main()
{
  // Parameters for output formatting
  int width = 18;
  int prec  = 10;

  // Example point: 
  double x = 2.0;

  // Exact 
  double d2u_exact = calc_d2u_exact(x);

  // Range of stepsizes
  double hmin = 1.0e-8;
  double hmax = 1.0;

  // Output a header 
  std::cout << "#" << std::setw(width-1) << "stepsize"
            << std::setw(width) << "d2u_approx"
            << std::setw(width) << "d2u_exact"
            // Note: Well compute the errors when analyzing and plotting the results
            // << std::setw(width) << "abs_error"
            // << std::setw(width) << "rel_error"
            // << std::setw(width) << "log10(rel_error)"
            << std::endl;

  // Loop over increasing stepsizes
  double h = hmin;
  while(h <= hmax)
  {
    // Compute approximate second derivative
    double d2u_approx = calc_d2u_approx(x, h);

    // Output to screen
    std::cout << std::setw(width) << std::setprecision(prec) << std::scientific << h
              << std::setw(width) << std::setprecision(prec) << std::scientific << d2u_approx 
              << std::setw(width) << std::setprecision(prec) << std::scientific << d2u_exact
              // Note: We could have computed the errors here and written them to the table
              //       (see code below), but we'll instead compute those when plotting
              // << std::setw(width) << std::setprecision(prec) << std::scientific << fabs((d2u_exact - d2u_approx))
              // << std::setw(width) << std::setprecision(prec) << std::scientific << fabs((d2u_exact - d2u_approx) / d2u_exact) 
              // << std::setw(width) << std::setprecision(prec) << std::scientific << log10(fabs((d2u_exact - d2u_approx) / d2u_exact))
              << std::endl;

    // Increase stepsize
    h = h * 10.;
  }

  // Done
  return 0;
}