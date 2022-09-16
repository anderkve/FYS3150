// A collection of memory errors
#include <iostream>
#include <vector>
using namespace std;


void write_beyond_limit()
{
  int x[2];
  x[2] = 10;
}


int main()
{

  // Writing beyond the limit of our array.

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;

  int x[2];
  x[2] = 10;

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;



  // Same error again, but now inside a function

  // cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;

  // write_beyond_limit();

  // cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;



  // Stack overlow :)
  // Trying to store a large variable on the stack
  // rather than on the heap.

  // int v[10000000];



  // Not deleting a new'd pointer. (Gives memory leak.)

  // int *x = new int();
  // (Do some stuff.)
  // Forgot delete statement here.



  // Deleting a new'd pointer twice.

  // int *x = new int();
  // // (Do some stuff.)
  // delete x;
  // delete x;


  return 0;
}
