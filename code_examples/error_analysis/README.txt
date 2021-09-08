An example that explores the error in an approximation of the second derivative of u(x) = exp(2x)


main.cpp
--------
C++ code that computes the second derivative of u(x) at a point xi using different stepsizes.
Outputs the result to a file output.txt.

Build command: g++ main.cpp -o main.exe
Run command: ./main.exe


plot.py
-------
Python script that reads the data in output.txt and generates plots of the absolute error, 
relative error and log10(relative error). Plots are saved as pdf files.

Run command: python3 plot.py

