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


## (When you should not be) using namespace

Towards the top of `.cpp` files you will often see a line like 

```cpp
using namespace std;
```

and similar for other namespaces, e.g. 

```cpp
using namespace arma;
```

if the code is using parts of the Armadillo library. What e.g. `using namespace std;` means is effectively *let me access everything from the `std` namespace without first writing `std::`*. (It's analogous to doing e.g. `from numpy import *` in a Python program that is using the numpy library.) 

Here's an example program that uses `cout` rather than `std::cout` to print a message to screen:

```cpp
#include <iostream>

using namespace std;

int main()
{
  cout << "Hello, World!\n";

  return 0;
}
```

Using this `using namespace` trick in your source files (`.cpp`) is usually fine. Just remember that in programs that involve many different libraries/namespaces, it may be important for code readability to actually write out the namespaces, since they tell us where you are getting different functions/variables/classes from.

**However**, you should **not put** `using namespace` **lines in your header files (`.hpp`)**. Doing this is generally regarded very bad practice. The reason is that if you do e.g. 

```cpp
using namespace some_namespace;
```

in a header file, this line will also affect all `.cpp` files (all compilation units) that include your header file at the beginning. So you end up "polluting" the main namespace of that `.cpp` file with everything from `some_namespace`, even though the person who wrote that `.cpp` file probably just included your header file to get access to some specific variables/functions/classes from your code. And if `some_namespace` e.g. contained a variable `some_variable`, this means that the person writing the `.cpp` file would get a surprising error message if they happened to also have a variable named `some_variable` in their code.







