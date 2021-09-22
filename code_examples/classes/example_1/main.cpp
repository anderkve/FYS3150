#include <iostream>
#include <vector>

// By writing a class we're creating a new *variable type* that we can use in our programs.
// 
// Here's an example class "IntPair" which simply holds two integers:
class IntPair
{
  public:
    int a;
    int b;
}; // <-- Class bodies end with semicolons!


// Since we now have a new type, we can also write functions that use this type as input/output.
// 
// Here's an example that recieves a reference-to-IntPair and uses it to set the two integers 
// in the pair to zero.
void set_pair_to_zero(IntPair& ip_in)
{
  ip_in.a = 0;
  ip_in.b = 0;
}


// 
// Main program
// 
int main()
{

  // We can create a variable of type IntPair. 
  IntPair my_ip;

  // We can access and modify IntPair member variables that are public
  my_ip.a = 100;
  my_ip.b = 200;

  // Let's print the variables stored in my_ip
  std::cout << "my_ip.a = " << my_ip.a << ", my_ip.b = " << my_ip.b << std::endl;
  std::cout << std::endl;

  // Let's try passing a reference to my_ip to the function set_pair_to_zero
  set_pair_to_zero(my_ip);

  // And let's print the integers again
  std::cout << "my_ip.a = " << my_ip.a << ", my_ip.b = " << my_ip.b << std::endl;
  std::cout << std::endl;


  // And we can of course create a container holding many instances of our new type.
  // Let's create a vector with three IntPair instances.
  std::vector<IntPair> my_intpair_collection(3);

  // Let's initialize each of them
  my_intpair_collection[0].a = 1;
  my_intpair_collection[0].b = 2;

  my_intpair_collection[1].a = 10;
  my_intpair_collection[1].b = 20;

  my_intpair_collection[2].a = 100;
  my_intpair_collection[2].b = 200;

  // Let's loop through the collection and print each IntPair instance
  for(IntPair& ip : my_intpair_collection)
  {    
    std::cout << "The current IntPair instance in my_intpair_collection: ip.a = " << ip.a << ", ip.b = " << ip.b << std::endl;
  }
  std::cout << std::endl;


  // We're done and all is well.
  return 0;
}