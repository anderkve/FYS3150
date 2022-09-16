#include <iostream>
#include "my_header.hpp"

using namespace std;

int main()
{

  // 
  // Some code here
  // 

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;


  // 
  // Some more code here
  // 

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;


  // Let's call the function dummy_function from my_header.hpp

  dummy_function();


  // 
  // Some more code here  
  // 

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;

  // 
  // Let's crash the program here, shall we?
  // 

  abort();


  // 
  // Some more code here  
  // 

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;


  // 
  // Some more code here  
  // 

  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;


  return 0;
}

