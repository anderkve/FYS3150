### main_minimal.cpp

An very minimal example using the `<random>` library. 


### main_basics.cpp

A slightly more detailed example explaining some `<random>` basics. 


### main_omp.cpp

A first example using `<random>` together with OpenMP parallelization. 
In this example all threads call a common random number generator. 
This is OK for the `<random>` library, which is designed to deal with this
without being super slow. However, with this simple setup 
the results will not be perfectly reproducible even when starting with 
a fixed seed. The reason is that the random numbers in the deterministic series
of numbers can end up on different threads in different runs of the code 
(due to small variations in speed). But in many cases this can be an OK tradeoff
to keep the code very simple.


### main_omp_2.cpp

An example similar to `main_omp.cpp`, but here each thread gets its 
own random number generator with its own unique seed constructed 
from a base seed. This demonstrates how `<random>` can be combined 
with parallelization in a perfectly reproducible manner.


### main_omp_3.cpp

Similar to `main_omp_2.cpp`, but now we've created a simple system in 
`include/omp_rng.hpp` and `src/omp_rng.cpp` that makes it easy to 
create and use one random number generator per OpenMP thread.


### main_rng_in_class.cpp

An example of how a `<random>` generator can live inside a class,
in this case a RandomWalker example class.


### main_rng_in_class_omp.cpp

Similar to `main_rng_in_class.cpp`, but now also including OpenMP parallelization.
Each thread gets its own `RandomWalker`, and the `<random>` generater in each
`RandomWalker` instance is seeded with a seed unique to the thread.
