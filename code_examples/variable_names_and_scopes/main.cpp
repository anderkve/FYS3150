#include <iostream>

int main()
{

  // Here we declare and assign value
  // to a variable 's' living in the outer scope
  int s = 10;

  if (true)
  {
    // Here we have entered a new local scope.

    // Here we declare and assign value to another variable, 
    // confusingly also named 's', that only lives in this inner scope
    std::string s = "Hello!";

    // While inside this local scope, the local variable 's' will take 
    // precedence over the 's' variable from the outer scope. So
    // the following line will print 'Hello!' to screen.
    std::cout << s << std::endl;

    // Next we do something dangerous! On the line below we may think we 
    // are changing the value of the 's' from the outer scope, since that 's' 
    // was of type integer. But since the local 's' takes precedence, what
    // we actually do is assign the *integer* 20 as the value to the string-type 
    // local variable 's'. That is nonsensical (technical word: "undefined behaviour"),
    // and the only thing you can know for sure is that the local string variable 's' 
    // will no longer contain the value "Hello"
    s = 20;

    // So when we now print the local 's' to screen, we will most likely get a blank line
    std::cout << s << std::endl;
  }

  // Now we are back in the outermost scope. The string variable 's' that existed inside the 
  // if block no longer exists. So there is now only one 's' variable, namely our original integer s = 10, 
  // which will now be printed to screen.
  std::cout << s << std::endl;

  return 0;
}

