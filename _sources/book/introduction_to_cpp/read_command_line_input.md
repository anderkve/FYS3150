# Read command line input

We often want to run our program repeatedly for new choices of the program settings, such as new step sizes, matrix sizes, output filenames, etc. In these cases it is useful if our program can read options directly from the command line, e.g. that we can execute our program with a command like 
```sh
./main.exe 100 output_n_100.txt 
```
to run with n=100 steps in our discretized computation, and have the results written to an output file `output_n_100.txt`. 

The `main` function in a C++ program can read command-line input via two standard function arguments called `argc` and `argv`:

```c++
int main(int argc, char* argv[])
```

- The "argument counter" `argc` is just an integer (`int`) that contains the number of provided input arguments.

- The "argument vector" `argv` contains the command-line input stored as strings. So you can think of `argv` as effectively being a vector of strings, but because C++ uses the same approach as C to reading command-line input, the actual variable type for `argv` looks slightly awkward: `char* argv[]` (or equivalently, `char** argv`). What this says is that `argv` is an *array with elements of type pointer-to-character*, which is a C-way of storing a vector of strings. In practice it doesn't matter much -- we'll anyway immediately extract the elements of `argv` and convert them into the types we expect.

Note that the first element, `argv[0]`, always contains the name of the executable file itself. So `argv` is never empty, and correspondingly, the smallest possible value for `argc` is 1. This corresponds to the user running the program without any input arguments, e.g. as 
```sh
./main.exe
```


Below is a minimal example that demonstrates how to read an integer, a floating-point number and a string from the command line. The program also implements a quick check that it has been called with the correct number of arguments.


```c++
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{

  // 
  // Check number of command-line arguments
  // 

  if (argc != 4)  // Expect 3 command-line arguments
  {
    // Get the name of the executable file
    std::string executable_name = argv[0];

    std::cerr << "Error: Wrong number of input arguments." << std::endl;
    std::cerr << "Usage: " << executable_name << " <some integer> <some double> <some string>" << std::endl;

    // Exit program with non-zero return code to indicate a problem
    return 1;   
  }

  // 
  // Save the command-line arguments as different variables
  // 

  int some_integer = atoi(argv[1]);    // atoi converts argv[2] to an integer
  double some_double = atof(argv[2]);  // atof converts argv[3] to a floating-point number
  std::string some_string = argv[3];   // no type conversion needed


  //
  // Some dummy code that uses the input arguments
  // 

  std::cout << "Got the following input: "
            << "some_integer: " << some_integer << ", "
            << "some_double: " << some_double << ", "
            << "some_string: " << some_string
            << std::endl;


  // All is well. Exit program with return code 0.
  return 0;
}
```

Running this program as 

```sh
./main.exe 100 3.14 hello
```

should now produce the output

```sh
Got the following input: some_integer: 100, some_double: 3.14, some_string: hello
```

On the other hand, running with the wrong number of input arguments, e.g.
```sh
./main.exe 100 3.14
```

should produce some output like this:

```sh
Error: Wrong number of input arguments.
Usage: ./main.exe <some integer> <some double> <some string>
```

