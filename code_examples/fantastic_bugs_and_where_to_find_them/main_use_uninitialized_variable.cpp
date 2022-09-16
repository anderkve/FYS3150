#include <iostream>
using namespace std;

int main()
{
  int a1, a2, a3, a4;

  a1 = 1;
  a2 = 2;
  // Forgot to initialize a3
  a4 = 4;


  int b = 0;

  b += a1;
  b += a2;
  b += a3;  // Here we're using the uninitialized a3
  b += a4;

  cout << "b: " << b << endl;
  
  return 0;
}
