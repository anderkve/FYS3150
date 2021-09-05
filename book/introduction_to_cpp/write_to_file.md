# Write to file

## Text output vs binary output
Below we will look at some simple examples of how to write output to a file in human-readable (i.e. text) format. 

The alternative would be to save the data directly in some binary format. This has the benefit of typically producing much smaller file sizes. For example, storing a double-precision number (precision of ~15 decimal places) directly in binary requires 8 bytes, while storing the same number as text would require (at least) 1 byte per character. (E.g. the number "1.2345e+02" would require 10 bytes.) The downside of using a binary file format is that we can't simply open the file with a text editor and look at the content. Instead the file must be read and interpreted by some program that knows exactly how the data was structured in the file when it was written -- in other words, a program that knows the given file format. A simple example of storing and reading data in binary format that may be very useful for this course is given on the [introduction to Armadillo](sec:intro_to_armadillo) page. 


```{note}
There exists many professional file formats for binary data, with dedicated libraries for reading/writing such files using different programming languages. One example is the `hdf5` format -- see [this](https://en.wikipedia.org/wiki/Hierarchical_Data_Format) Wikipedia page if you want to learn more.
```

## Minimal example

Here is a minimal example of how to write some text to a file. Note that we need the type `ofstream`, declared in the `<fstream>` header of the standard C++ library:

```c++
#include <iostream>
#include <string>
#include <fstream>

int main()
{
  // Set a filename
  std::string filename = "output.txt";

  // Create and open the output file. Or, technically, create 
  // an "output file stream" (type std::ofstream) and connect 
  // it to our filename.
  std::ofstream ofile;
  ofile.open(filename);

  // Send some text to this output file
  ofile << "Some output text" << std::endl;
  
  // Close the output file
  ofile.close();

  // All is well. Exit program with return code 0.
  return 0;
}
```

If you run the above program it should produce a file `output.txt` containing the single line "Some output text". Note that the line 

```c++
ofile.open(filename);
```
opens the file for *overwriting* any existing file content. If you rather want to *append* to an existing file, you can use the "append mode" as follows:

```c++
ofile.open(filename, std::ofstream::app);
```


## Example with nicely formatted numbers

Below is a slightly more elaborate example. It computes y = x^2 for 101 points from x=0.0 to x=1.0 (i.e. with a stepsize of 0.01), 
and writes the x and y values to a file `x_y.txt` in a nicely formatted way. For this formatting we use functionality from `<iomanip>`.

```c++
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>


// Main program
int main()
{
  // Set a filename
  std::string filename = "x_y.txt";

  // Create and open the output file. Or, technically, create 
  // an "output file stream" (type std::ofstream) and connect it to our filename.
  std::ofstream ofile;
  ofile.open(filename);

  // Set some parameters for our computation
  double x_min = 0.0;
  double x_max = 1.0;
  int n_steps = 100;
  double h = (x_max - x_min) / n_steps;

  // Some width and precision parameters we will use to format the output
  int width = 12;
  int prec  = 4;

  // Set the first x and y values
  double x = x_min;
  double y = x*x;

  // Loop over steps
  for (int i = 0; i <= n_steps; i++)
  {
    // Write a line with the current x and y values (nicely formatted) to file
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x
          << std::setw(width) << std::setprecision(prec) << std::scientific << y
          << std::endl;

    // Update x and y values
    x += h;
    y = x*x;
  }  

  // Close the output file
  ofile.close();

  // All is well. Exit program with return code 0.
  return 0;
}
```

We can take a look at the ten first lines of `x_y.txt` to see what the formatted program output looks like:

```sh
head -10 x_y.txt
```

Output:

```sh
  0.0000e+00  0.0000e+00
  1.0000e-02  1.0000e-04
  2.0000e-02  4.0000e-04
  3.0000e-02  9.0000e-04
  4.0000e-02  1.6000e-03
  5.0000e-02  2.5000e-03
  6.0000e-02  3.6000e-03
  7.0000e-02  4.9000e-03
  8.0000e-02  6.4000e-03
  9.0000e-02  8.1000e-03
```

We see that each number is written in scientific notation (`std::scientific`), has four decimals (`std::setprecision(...)`), 
and takes up a width of 12 characters (`std::setw(...)`) in the file; 2 blank spaces plus 10 characters for the actual number. By using two blank spaces between numbers we ensure that the formatting will still look nice even if some numbers get a minus sign in front.





