### Simple example of pass-by-value and pass-by-reference

The example in `main.cpp` illustrates the difference between using **pass-by-value** and **pass-by-reference** for the input arguments to a function. In short:

- Pass-by-value: The function recieves **a value**, copied to a new local variable that only lives inside this function

- Pass-by-reference: The function recieves **a reference to a pre-existing variable**, so that if the function modifies the reference, the original variable is modified.

To build and run the example, do:

```
g++ main.cpp -o main
./main
```

Read the code and code comments for further details.
