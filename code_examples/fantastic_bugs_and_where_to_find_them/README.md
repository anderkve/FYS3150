## How to spot where something goes wrong in your code?

### Tip 0:

- Indent your code properly. It makes it much easier to read the code flow and spot potential mistakes.


### Tip 1:

- Compile your code with the `-Wall` option, to see all warnings from the compiler. 

- To force yourself to fix all compiler warnings, you can add the `-Werror` option too, 
  which turns all compiler warnings into compiler *errors*, so that the compilation stops.


### Tip 2: 

- Add `cout` (aka print) statements to check values of variables
  at different places in your code.


### Tip 3: 

- When searching for problems in your code by inserting `cout` statements, 
  the special macros `__FILE__` and `__LINE__` are often useful. They will 
  be printed as the file name and line number. So you can for instance insert 
  a bunch of statements like this
  ```
  cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << endl;
  ```
  to get screen output like 
  ```
  DEBUG: main.cpp:35
  DEBUG: utils.hpp:12
  DEBUG: main.cpp:42
  DEBUG: main.cpp:67
  ```
  which can help you track down where a problem happens.


### Tip 4:

- If you suspect that the problem is reading beyond the limit of 
  a `std::vector`, replace any 
  ```    
  your_vector[i] 
  ```
  statements with 
  ```
  your_vector.at(i) 
  ```
  instead. That should lead to a runtime error, instead of the
  program just continuing with some garbage numbers.


### Tip 5:

- If your code *crashes* during runtime, and you don't know where/why,
  try running your program through the GNU debugger, `gdb`:
  ```
  gdb --args ./your_program
  ```
  This gives you a `gdb` command line. Start your program 
  with the command `r`. 

  When the code crashes, use the command `bt` (for *backtrace*)
  to (hopefully) get a list showing the *call stack*. This can 
  tell you what function your program is in at the time it crashes.

  To exit `gdb`, use the command `q`.

  To potentially get more information out of the `gdb` 
  call stack, like the exact line numbers for your code, 
  you can compile your code with more debug info included. 
  You do this by adding the flag `-g` to your build command:
  ```
  g++ your_program.cpp -g -o your_program
  ```

  If you don't get anything useful from `gdb`, e.g. the crash is
  such that the call stack is empty, go back to Tip 2 and 
  add a bunch of `cout` statements with `__FILE__` and `__LINE__`
  to track down the place it crashes.


### Tip 6:

- Keep in mind that if you have a memory error, e.g. from reading/writing 
  to memory outside some array/vector bound, your code might crash long 
  after the point where the actual bug is. Use `cout` statements to track
  the values of variables and look for any surprising behaviour.


### Tip 7:

- If you suspect a memory leak, stack overflow or similar, you can try
  installing the tool `valgrind` and run your program through it:
  ```
  valgrind ./your_program
  ```

  Valgrind outputs a report on potential memory issues in your program.



