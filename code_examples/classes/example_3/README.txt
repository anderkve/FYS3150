Example 3 of classes in C++
---------------------------

(This is the same as example_2, but with more proper file organization.)

This example illustrates how to unrelated classes can work 
nicely together. In this case one class (LotteryMachine)
contains a collection of instances of another class (LotteryBall), 
and performs operations with them.

Files:
- include/LotteryMachine.hpp
- src/LotteryMachine.cpp
- include/LotteryBall.hpp
- src/LotteryBall.cpp


How to build and run the examples
---------------------------------

Build: g++ main.cpp src/LotteryBall.cpp src/LotteryMachine.cpp -I include/ -o main
Run: ./main


