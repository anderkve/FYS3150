# Project 4: Ising Model

## Preqrequisites

In order to run the code, you will need to have the following installed on your machine:

- C++ compiler
- Python
- [Armadillo](https://arma.sourceforge.net/)
- OpenMP (It comes with most compilers, but you might need to install it separately if you have a Mac)

You might need to edit the `Makefile` to include the correct path to the Armadillo library.

The make file will run g++-12 if you have mac and g++ if you have other OS.

## Building the Code

First navigate to the project directory, then make the code:

```bash
cd project4
make
```

To run the code, you can use the following command:

```bash
# Execute the built files
echo "Executing built files..."
cd build/
for file in *.exe; do
    echo "Running $file"
    ./$file
done
```

Then navigate back if you havent, and run the python scripts to generate the plots:

```bash
python plot_all.py
```

## Notes

`phase_transition_improved.cpp`is intentionally left out of the `Makefile` as it takes a long time to run. You can run it by uncommenting the line in the `Makefile` and running `make` again.
