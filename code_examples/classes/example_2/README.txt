Example 2 of classes in C++
---------------------------

This example illustrates how to unrelated classes can work 
nicely together. In this case one class (LotteryMachine) 
contains a collection of instances of another class (LotteryBall), 
and performs operations with them.

For easy viewing, this example is also contained in a single main.cpp file.

In general, the code should have been organized into multiple files, e.g. something 
like this:

- include/LotteryMachine.hpp
- src/LotteryMachine.cpp
- include/LotteryBall.hpp
- src/LotteryBall.cpp

See example_3 for the same example but structured using multiple files as suggested above.


How to build and run the examples
---------------------------------

Build: g++ main.cpp -o main
Run: ./main


