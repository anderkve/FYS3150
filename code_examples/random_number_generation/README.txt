main_minimal.cpp
----------------

An very minimal example using the <random> library. 


main_basics.cpp
----------------

A slightly more detailed example explaining some <random> basics. 


main_omp.cpp
------------

An example using <random> together with OpenMP parallelization, 
where each thread gets its own random number generator with its 
own unique seed constructed from a base seed.


main_omp_2.cpp
--------------

Similar to main_omp.cpp, but now we've created a simple system in 
include/omp_rng.hpp and src/omp_rng.cpp that makes it easy to 
create and use one random number generator per OpenMP thread.


main_rng_in_class.cpp
---------------------

An example of how a <random> generator can live inside a class,
in this case a RandomWalker example class.


main_rng_in_class_omp.cpp
-------------------------

Similar to main_rng_in_class.cpp, but now also including OpenMP parallelization.
Each thread gets its own RandomWalker, and the <random> generater in each
RandomWalker instance is seeded with a seed unique to the thread.
