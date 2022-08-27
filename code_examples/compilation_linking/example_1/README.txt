Example of some compilation and linking basics

This will fail (header file not found):
g++ -c main.cpp 

This will work:
g++ -c main.cpp -I include

Can we now link main.o and create main.exe? Not yet...

This will fail (undefined reference):
g++ main.o -o main.exe

Need to first compile the second source file (src/utils.cpp):
g++ -c src/utils.cpp -I include

...and then link all the .o files together and create main.exe:
g++ main.o utils.o -o main.exe

Now we're ready to run our program:
./main.exe

----------------------------

To compile both source files and perform the linking all in one go:
g++ main.cpp src/utils.cpp -I include -o main.exe

