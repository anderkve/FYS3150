### Example error analysis 

This example explors the error in an approximation of the second derivative of u(x) = exp(2x).


#### main.cpp

C++ code that computes the second derivative of u(x) at a point xi using different stepsizes.
Outputs the results to screen in a nice table.

Build command: 
```
g++ main.cpp -o main
```

Run command: 
```
./main
```

We can pipe the output to a file `output.txt`:
```
./main > output.txt
```

#### plot.py

Python script that reads the data from a file `output.txt` and generates plots of the absolute error, 
relative error and log10(relative error). Plots are saved as pdf files.

Run command: 
```
python3 plot.py
```
