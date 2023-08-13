# Source files and header files

A typical C++ code consists of
- **source files**, with names ending with `.cpp`
- **header files**, with names ending with `.hpp`

Header files can be _included_ in source files, using the `#include` command. Say we have two files, `my_header.hpp` and `main.cpp`:

**`my_header.hpp`:**
```cpp
#include <iostream>

void print_message()
{
  std::cout << "Hello, World!\n";
}
```

**`main.cpp`:**
```cpp
#include "my_header.hpp"

int main()
{
  print_message();

  return 0;
}
```

The line `#include "my_header.hpp"` in `main.cpp` simply tells the compiler to **insert the content of `my_header.hpp` here before compiling**. So the code that ends up being compiled is completely equivalent to this single `.cpp` file:

```cpp
#include <iostream>

void print_message()
{
  std::cout << "Hello, World!\n";
}

int main()
{
  print_message();

  return 0;
}
```

(And this code is of course equivalent to the code you would get if you replaced `#include <iostream>` with the full content of `iostream.hpp` from the standard C++ library. But let's not do that...)


```{note}
When including our own header files, we use the syntax `#include "someheader.hpp"`, rather than `#include <someheader>`.
```

In in larger C++ projects it is common to put all source files (`.cpp`) in a folder called `src/`, and all header files (`.hpp`) in a folder called (`include/`). More on this in the next section. 

