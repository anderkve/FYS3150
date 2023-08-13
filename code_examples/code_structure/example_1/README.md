# Example code structure for C++ projects

There are different opinions on how to best organise C++ code, but a common guiding 
principle is that too much code repetition should be avoided. Here we present one standard 
approach to structuring C++ code:

- Put useful functions that you'll need again and again in dedicated 
  source files (`.cpp`). Place these source files in a folder named `src`.

- For each such source file, write a header file (`.hpp`) that only contains 
  the function *declarations*. Place these header files in a folder named `include`.

- In your main program(s), simply `#include` the header file with the relevant function 
  declaration and use the function in your main program.

Keep in mind that for this to work, the `.cpp` files in `src/` must be compiled and linked 
to the main program -- see the example compilation + linking commands below.

With this code structure you can typically write reasonably short and clear main programs 
that each just do a small number of tasks (e.g. computes one number of interest or performs 
one particular simulation), since the common code needed by all the main programs have been 
placed in some other files.


The example in this folder has two header files in the include directory:

- `include/utils.hpp`

  This could be your personal collection of utility functions, e.g. functions for 
  doing standard tasks like formatting a number nicely as a string.

- `include/clever_algorithms.hpp`

  This could be your collection of different algorithms for performing some computation.

The header files only show the function *declarations*. The complete code for the functions, 
i.e. the function *definitions*, live in the corresponding `.cpp` files 

- `src/utils.cpp`

- `src/clever_algorithms.cpp`

Finally, there are two small main programs 

- `main_test_algo_one.cpp`
- `main_timing.cpp`

that demonstrate how we can use these common functions in multiple different 
main programs by just including the relevant header files.


# Build and run the examples

- `main_test_algo_one.cpp`
  
  Build: 
  ```sh
  g++ main_test_algo_one.cpp src/*.cpp -I include -o main_test_algo_one.exe
  ```
  Run: 
  ```sh
  ./main_test_algo_one.exe
  ```

- `main_timing.cpp`

    Build: 
    ```sh
    g++ main_timing.cpp src/*.cpp -I include -o main_timing.exe
    ```
    Run: 
    ```
    ./main_timing.exe
    ```

