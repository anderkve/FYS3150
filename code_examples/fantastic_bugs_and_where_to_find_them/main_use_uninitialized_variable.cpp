#include <iostream>
using namespace std;

int main()
{
  int x1, x2;
  double x3, x4;

  x1 = 1;
  x2 = 2;

  // Forgot to initialize x3
  x4 = 10.;


  double b = 0.;

  b += x1;
  b += x2;

  b = b / x3;   // Here we're using the uninitialized x3
  b = b * x4;

  cout << "b: " << b << endl;
  
  return 0;
}
