/*

See description in README.txt

Build: 
g++ main_basics.cpp -o main_basics

Run: 
./main_basics

*/

#include <random>
#include <chrono>
#include <iostream>


using namespace std;


int main()
{
  // Get a seed from the system clock
  unsigned int seed = chrono::system_clock::now().time_since_epoch().count();

  // ...or set one manually
  // unsigned int seed = 1840371;

  cout << "seed: " << seed << endl;
  cout << endl;


  // Construct a Mersenne Twister 19937 random number generator
  mt19937 generator;

  // Seed it with our seed
  generator.seed(seed);

  // The generator can generate random integers between the 
  // values generator.min() and generator.max()
  cout << "generator.min(): " << generator.min() << endl;
  cout << "generator.max(): " << generator.max() << endl;
  cout << endl;

  
  // In many cases we want to transform the generator samples into 
  // samples from some other basic probability distribution. 
  // To do that we can use the distribution classes from <random>, 
  // see here: https://www.cplusplus.com/reference/random/ 

  // First example: We'll construct a distribution object "my_01_pdf" that 
  // transforms generator samples into random samples of the integers 0 or 1
  uniform_int_distribution<int> my_01_pdf(0,1);

  // Now we can generate random numbers by passing the generator to the distribution:
  cout << "my_01_pdf(generator): " << my_01_pdf(generator) << endl;
  cout << "my_01_pdf(generator): " << my_01_pdf(generator) << endl;
  cout << "my_01_pdf(generator): " << my_01_pdf(generator) << endl;
  cout << "my_01_pdf(generator): " << my_01_pdf(generator) << endl;
  cout << endl;


  // Second example: Now let's transform generator samples into samples 
  // from a Gaussian pdf:
  normal_distribution<double> my_gaussian_pdf(0.0,1.0);
  cout << "my_gaussian_pdf(generator): " << my_gaussian_pdf(generator) << endl;
  cout << "my_gaussian_pdf(generator): " << my_gaussian_pdf(generator) << endl;
  cout << "my_gaussian_pdf(generator): " << my_gaussian_pdf(generator) << endl;
  cout << "my_gaussian_pdf(generator): " << my_gaussian_pdf(generator) << endl;
  cout << endl;


  // We're done here
  return 0;
}

