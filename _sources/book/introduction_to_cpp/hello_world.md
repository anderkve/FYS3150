(sec:hello_world)=
# Hello World

The classic first example of a C++ program is the "Hello World" program:

```cpp
// Look, our first C++ program!

#include <iostream>

int main()
{
  // Print a message to screen
  std::cout << "Hello, World!\n";

  // Return 0 when done
  return 0;
}
```

If you want to execute it right away, try pasting the code into the online editor+compiler at [cpp.sh](http://cpp.sh/) and hit the "Run" button. As you probably have guessed, this program simply prints
```sh
Hello, World!
```
to screen. (On [cpp.sh](http://cpp.sh/) you get the output in the "execution" window below the editor.)

The program illustrates some C++ basics: 

- Comments start with `//`

- The line `#include <iostream>` includes standard C++ functionality for input/output. (More about that later.) This enables us to use `std::cout` in our code. The `#include` lines in C++ are a bit like the `import` lines in Python.

- A valid C++ program must have a function called `main` with **return type** `int` (integer):
  ```cpp
  int main()
  {
    ...
  }
  ```

- Program statements end with semicolons (`;`).

- To write output to screen we use `std::cout` (pronounced "see-out").

- Here `std::` indicates that `cout` lives in the standard C++ library. Technically, `std` is the **namespace** (more on that later). This is analogous to how the Python code `math.sqrt(2)` says that `sqrt` lives in the `math` package.
 
- The `return` keyword ends a function. Since the `main` function has return type `int`, we return an integer: `return 0;` Returning 0 from the main function indicates that the program completed successfully.

So far, so good --- next, let's look at how we can run this program on our own computer.
