### Writing numpy binary files (.npy) from C++

This example demonstrates how we can save Armadillo matrices or cubes to file in numpy's binary file format (.npy files). This makes it easy to read the data we generate into Python scripts without having to use the pyarma package to import files written in Armadillo's binary format. (It seems like pyarma no longer actively maintained.)

To write numpy files directly from C++ we make use of the open-source and header-only library `libnpy`, by Leon Merten Lohse, see https://github.com/llohse/libnpy.

Since this is a header-only library, all you need to use it is to copy the header file `include/npy.hpp` into the `include` directory of your own code, and of course make sure to have `-Iinclude` in your build command.


#### main.cpp

This is a minimal example program that defines two helper functions, `write_cx_mat_to_npy_file` and `write_cx_mat_to_npy_file` and demonstrates how to use these to store an `arma::cx_mat` and an `arma::cx_cube` to `.npy` files. 

Build:
```
g++ -O2 main.cpp -o main -I./include -larmadillo
```

Run:
```
./main
```

This should produce two binary files: `matrix_A.npy` and `cube_C.npy`.



#### read_npy_file.py

A minimal Python example that demonstrates how the read the above `.npy` files.

Run:
```
Python read_npy_file.py
```
