#include <iostream>
#include <vector>

using namespace std;

int main()
{

  // Fill a vector v = {10, 20, ..., 100}
  vector<int> v;
  for (int i = 1; i <= 10; i++)
  {
    v.push_back(i * 10);
  }

  
  // Bug: Reading beyond the last element of a vector. 

  // Let's first do it using the the [] operator. 
  // Now anything can happen...
  for (int j = 0; j < 50; j++)
  {
    cout << "j: " << j << "  " << "v[j]: " << v[j] << endl;    
  }


  cout << endl;
  cout << endl;


  // Do it again, but now using .at(). 
  // This at least gives a sensible runtime error message. 
  // If we also compile with the g++ -g debug option, the GNU 
  // debugger (gdb) can often tell us the exact line where the
  // problem is.
  for (int j = 0; j < 50; j++)
  {
    cout << "j: " << j << "  " << "v.at(j): " << v.at(j) << endl;    
  }


  return 0;
}

