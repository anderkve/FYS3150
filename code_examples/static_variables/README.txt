A couple of examples that demonstrate the 
use of static variables in functions.


main_first_time.cpp
-------------------
A simple program illustrating how a static bool can be
used to make a function perform some special task
only the first time it is run (e.g. read a data file).

Build command: g++ main_first_time.cpp -o main_first_time.exe
Run command: ./main_first_time.exe


main_counter.cpp
----------------
A simple program illustrating how a static integer can be
used as counter for the function itself to count how
many times it's been called.

Build command: g++ main_counter.cpp -o main_counter.exe
Run command: ./main_counter.exe


