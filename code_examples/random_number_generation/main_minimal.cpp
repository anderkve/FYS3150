/*

See description in README.txt

Build: 
g++ main_minimal.cpp -o main_minimal

Run: 
./main_minimal

*/

#include <random>
#include <chrono>
#include <iostream>


using namespace std;


int main()
{
  // Construct a Mersenne Twister 19937 random number generator with a given seed
  mt19937 generator(1583023);

  // Construct a distribution object for the uniform distribution on [0,1)
  uniform_real_distribution<double> my_distribution(0.0 ,1.0);

  // Draw a sample from the distribution by passing in the generator
  cout << "my_distribution(generator): " << my_distribution(generator) << endl;


  // We're done here
  return 0;
}

