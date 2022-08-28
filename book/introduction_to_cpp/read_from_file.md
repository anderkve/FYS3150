(sec:read_from_file)=
# Read from file

Here we will look at a simple example of how to read a set of numbers from a text file. Our two most common use cases for reading from file are

1. that our computation/simulation needs some input data; or
2. that we need to pass in many control parameters (step sizes, tolerances, etc.) for our program.

For the example below we will assume that the numbers are organised in a table that we should read row by row. A simple table format is most suitable for the first case above. For the second case, if you are writing a code that needs a large number of configuration parameters, you probably want to use some standard structured file format, e.g. [YAML](https://en.wikipedia.org/wiki/YAML), which you can use with C++ via external libraries such as [yaml-cpp]( https://yaml-cpp.docsforge.com/).

## Minimal example

Assume we have a data table file `x_y_fxy.dat` that look like this:

```
#        x           y      f(x,y)
0.0000e+00  0.0000e+00  0.0000e+00
0.0000e+00  1.9635e-01  3.8553e-02
0.0000e+00  3.9270e-01  1.5421e-01
0.0000e+00  5.8905e-01  3.4698e-01
0.0000e+00  7.8540e-01  6.1685e-01
1.9635e-01  0.0000e+00  1.9635e-01
1.9635e-01  1.9635e-01  2.4247e-01
1.9635e-01  3.9270e-01  3.6569e-01
1.9635e-01  5.8905e-01  5.6599e-01
1.9635e-01  7.8540e-01  8.4336e-01
3.9270e-01  0.0000e+00  3.9270e-01
3.9270e-01  1.9635e-01  4.6150e-01
3.9270e-01  3.9270e-01  6.0723e-01
3.9270e-01  5.8905e-01  8.2971e-01
3.9270e-01  7.8540e-01  1.1288e+00
5.8905e-01  0.0000e+00  5.8905e-01
5.8905e-01  1.9635e-01  6.9558e-01
5.8905e-01  3.9270e-01  8.7831e-01
5.8905e-01  5.8905e-01  1.1363e+00
5.8905e-01  7.8540e-01  1.4688e+00
7.8540e-01  0.0000e+00  7.8540e-01
7.8540e-01  1.9635e-01  9.4459e-01
7.8540e-01  3.9270e-01  1.1780e+00
7.8540e-01  5.8905e-01  1.4829e+00
7.8540e-01  7.8540e-01  1.8566e+00
```

The following code will read this file and save the rows in a vector of vectors using only the standard C++ library. The example also shows how the comment line starting with `#` can be ignored when reading the data.

```{note}
You can also use Armadillo to very easily read a data table --- see the [introduction to Armadillo](sec:intro_to_armadillo) page.
```

```c++
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

int main()
{
  // Set the filename
  std::string filename = "x_y_fxy.dat";

  // A vector of vectors to store the the rows in the input file
  std::vector< std::vector<double> > input_data;

  // Create a filestream instance "myfile" and use it to read the file
  std::fstream myfile;
  myfile.open(filename);
  if (myfile.is_open())  // This checks that the file was opened OK
  {
    // Some temporary variables we'll use
    std::string line;
    double x, y, f;

    // Read file line by line
    while (std::getline(myfile, line))
    {
      // Skip lines with "#" at the first position
      if (line.at(0) == '#')
      {
        continue;
      }
      else
      {
        // Parse the string (line) and interpret it as three 
        // double variables (x, y, f)
        std::stringstream mysstream(line);
        mysstream >> x >> y >> f;

        // Save the three values in a new vector in input_data
        std::vector<double> triplet = {x, y, f};
        input_data.push_back(triplet);
      }
    }
  }
  else
  {
    std::cout << "Unable to open the file " << filename;
  }

  // Close the input file
  myfile.close();


  //
  // (Now do something useful with the data...)
  //


  // All is well. Exit program with return code 0.
  return 0;
}
```

In a larger program, it's usually better to write a separate function for reading data from file rather than placing this code directly in the main program.


