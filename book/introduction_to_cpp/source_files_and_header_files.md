# Source files and header files

A typical C++ code consists of
- **source files**, with names ending with `.cpp`
- **header files**, with names ending with `.hpp`

Header files can be _included_ in source files, using the `#include` command. Say we have two files, `my_header.hpp` and `main.cpp`:

```cpp
// File: my_header.hpp

#include <iostream>

void print_message()
{
  std::cout << "Hello, World!";
}
```

```cpp
// File: main.cpp

#include "my_header.hpp"

int main()
{
  print_message();

  return 0;
}
```

The line `#include "my_header.hpp"` simply tells the compiler to **insert the content of `my_header.hpp` here**. So the code that ends up being executed is completely equivalent to this single source file:

```cpp
#include <iostream>

void print_message()
{
  std::cout << "Hello, World!";
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


<!--
# Common directory layout

It is common in larger C++ projects to put all source files (`.cpp`) in a folder called `src/`, and all header files (`.hpp`) in a folder called (`include/`). So something like this:

```
./src/main.cpp
./src/utils.cpp
./include/utils.hpp
```
-->