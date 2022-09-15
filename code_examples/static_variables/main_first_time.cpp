#include <iostream>

using namespace std;


void some_function()
{
  static bool first = true;

  // Do this only the first time this function is called
  if (first)
  {
    cout << "First time!" << endl;
    first = false;
  }

  cout << "Every time!" << endl;
}



int main()
{

  some_function();
  some_function();
  some_function();

  return 0;
}




