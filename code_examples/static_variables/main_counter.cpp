#include <iostream>

using namespace std;


void some_function()
{
  static int counter = 0;
  counter += 1;

  cout << "Number of some_function calls: " << counter << endl;
}



int main()
{

  some_function();
  some_function();
  some_function();

  return 0;
}




