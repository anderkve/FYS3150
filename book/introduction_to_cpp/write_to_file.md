# Write to file

## Text output vs binary output
Below, we will look at some simple examples of how to write output to a file in human-readable (i.e. text) format. 

The alternative would be to save the data directly in some binary format. This has the benefit of typically producing much smaller file sizes. For example, storing a double-precision number (precision of ~15 decimal places) directly in binary requires 8 bytes, while storing the same number as text would require (at least) 1 byte per character. (E.g. the number "1.2345e+02" would require 10 bytes.) The downside of using a binary file format is that we can't simply open the file with a text editor and look at the content. Instead, the file must be read and interpreted by some program that knows exactly how the data was structured in the file when it was written -- in other words, a program that knows the given file format. A simple example of storing and reading data in binary format that may be very useful for this course is given on the [introduction to Armadillo](sec:intro_to_armadillo) page. 


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
  std::ofstream ofile(filename);

  // Send some text to this output file
  ofile << "Some output text" << std::endl;
  
  // All is well. Exit program with return code 0.
  return 0;
}
```

If you run the above program it should produce a file `output.txt` containing the single line "Some output text". Note that the line 

```c++
std::ofstream ofile(filename);
```
opens the file for *overwriting* any existing file content. If you rather want to *append* to an existing file, you can use the "append mode" as follows:

```c++
std::ofstream ofile(filename, std::ios::app);
```


## Example with nicely formatted numbers – before C++20

Below is a slightly more elaborate example. It computes y = x^2 for 101 points from x=0.0 to x=1.0 (i.e. with a stepsize of 0.01), 
and writes the x and y values to a file `x_y.txt` in a nicely formatted way. For this formatting, we use functionality from `<iomanip>`.

```c++
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

int main()
{
  // Set a filename
  std::string filename = "x_y.txt";

  // Create and open the output file. Or, technically, create 
  // an "output file stream" (type std::ofstream) and connect it to our filename.
  std::ofstream ofile(filename);

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
    // Update x and y values
    x = x_min + i*h;
    y = x*x;

    // Write a line with the current x and y values (nicely formatted) to file
    ofile << std::setw(width) << std::setprecision(prec) << std::scientific << x
          << std::setw(width) << std::setprecision(prec) << std::scientific << y
          << std::endl;
  }  

  // All is well. Exit program with return code 0.
  return 0;
}
```

After building and running this program, we can take a look at the ten first lines of `x_y.txt` to see what the formatted program output looks like:

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



## Example with nicely formatted numbers – after C++20

With C++20 we got the `<format>` library as part of the standard library. This allows us to do formatting in a way which will look simpler and more familiar if you come from e.g. Python. Here is the same example as above, but now using `<format>`:


```c++
#include <iostream>
#include <string>
#include <fstream>
#include <format>

int main()
{
  // Set a filename
  std::string filename = "x_y.txt";

  // Create and open the output file. Or, technically, create 
  // an "output file stream" (type std::ofstream) and connect it to our filename.
  std::ofstream ofile(filename);

  // Set some parameters for our computation
  double x_min = 0.0;
  double x_max = 1.0;
  int n_steps = 100;
  double h = (x_max - x_min) / n_steps;

  // Set the first x and y values
  double x = x_min;
  double y = x*x;

  // Loop over steps
  for (int i = 0; i <= n_steps; i++)
  {
    // Update x and y values
    x = x_min + i*h;
    y = x*x;

    // Write a line with the current x and y values (nicely formatted) to file
    ofile << std::format("{:12.4e}{:12.4e}", x, y) << std::endl;
  }  

  // All is well. Exit program with return code 0.
  return 0;
}
```

Depending on your compiler version, you may need to add the `-std=c++20` flag to build this program, e.g.

```sh
g++ -std=c++20 main.cpp -o main
``` 

Running the program should produce the a file identical to the one from the first example.

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


Finally, here's an example program demonstrating different uses of `std::format` to format numbers, here printed to screen:

```c++
#include <format>
#include <iostream>

int main()
{
    double x = 12345.6789;

    std::cout << std::format("default:            {}\n",         x);
    std::cout << std::format("fixed:              {:f}\n",       x);
    std::cout << std::format("fixed, 2 dec:       {:.2f}\n",     x);
    std::cout << std::format("scientific:         {:e}\n",       x);
    std::cout << std::format("scientific, 4 dec:  {:.4e}\n",     x);
    std::cout << std::format("width 20:           {:20.8e}\n",   x);
    std::cout << std::format("left-aligned:       {:<20.8e}|\n", x);
    std::cout << std::format("right-aligned:      {:>20.8e}|\n", x);

    return 0;
}
```

Running this program should give the following screen output:

```
default:            12345.6789
fixed:              12345.678900
fixed, 2 dec:       12345.68
scientific:         1.234568e+04
scientific, 4 dec:  1.2346e+04
width 20:                 1.23456789e+04
left-aligned:       1.23456789e+04      |
right-aligned:            1.23456789e+04|
```
