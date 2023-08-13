# Code structure

There are different opinions on how to best organise C++ code, but a common guiding 
principle is that too much code repetition should be avoided. Here we present one standard 
approach to structuring C++ code:

- Put useful functions that you'll need again and again in dedicated 
  source files (`.cpp`). Place these source files in a folder named `src`.

- For each such source file, write a header file (`.hpp`) that only contains 
  the function *declarations*. Place these header files in a folder named `include`.

- In your main program(s), simply `#include` the header file with the relevant function 
  declaration and use the function in your main program.

Keep in mind that for this to work, the `.cpp` files in `src/` must be compiled and linked to the main program -- see the example compilation + linking commands in the next section.

With this code structure you can typically write reasonably short and clear main programs 
that each just do a small number of tasks (e.g. computes one number of interest or performs 
one particular simulation), since the common code needed by all the main programs have been 
placed in some other files.

You can find an example illustrating this structure [here](https://github.com/anderkve/FYS3150/tree/master/code_examples/code_structure/example_1).
