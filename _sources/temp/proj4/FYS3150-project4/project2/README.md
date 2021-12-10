To compile the project run `make all`. This will generate 5 exectuable files.

`test_tridiag.out` tests that the analytical and numerical solution in Armadillo are more or less the same.

`test_max_offdiag_symmetric.out` tests that the implementation for finding the biggest offdiagonal element in max_ofdiag_symmetric.cpp is correct.

`test_jacobi_eigensolver.out` tests that the implementation of the jacobi eigensolver in jacobi_eigensolver.cpp is correct

`estimate_rotations.out` calculates the number of transformations needed with a matrix of size N and writes this to file

`solve_diff.out` solves the discretized version of the matrix equation $A \vec{v}=\lambda v$ and writes the result to file

There is also 2 scripts for plotting:
    `plot_rotation_results.py` plots the data from `estimate_rotations.out`
    `plot_solve_diff.py` plots the data from `solve_diff.out`