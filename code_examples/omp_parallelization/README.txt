main_threadsafety.cpp
---------------------

Simple example code that illustrates how a code can be *non-threadsafe* unless
you pay attention to whether a variable is *shared* among threads (all threads 
modify same variable in memory) or *private* (each thread is working with its
own separate instance of the variable.)

- Comment in one of the code parts in the example (part 1, 2 or 3)

- Build with: 

    g++ main_threadsafety.cpp -fopenmp -o main_threadsafety.exe

- Set the number of threads to use by setting the environment variable OMP_NUM_THREADS, e.g.
  with the command "export", like this:

    export OMP_NUM_THREADS=4

- Run with:

    ./main_threadsafety.exe

- To see example of thread-unsafe code, uncomment part 2 of the code, recompile 
  and run as follows:
  
    export OMP_NUM_THREADS=10
    ./main_threadsafety.exe > output.txt    # piping the output to a file
    cat output.txt                     # look at the output 
    cat output.txt | grep "thread: 2"  # look at output for thread 2

  You will probably see that for many of the threads, other threads have
  incremented the value of x between every increment from the thread you
  are looking at. 



main_no_omp.cpp
---------------

A dummy example of a program with a two-loop structure. The outer loop is
a loop over n_A values of some variable 'A', from A_min to A_max. 

For each value of A, there is an inner loop counting up to "n_cycles" and doing 
a dummy computation with that A value as input. 

This example code in main_no_omp.cpp is *not* parallelized.

- Build with:

    g++ -O3 main_no_omp.cpp -o main_no_omp.exe

- Run as:

    ./main_no_omp.exe <A_min> <A_max> <n_A> <n_cycles> <output_file_name>

- To run an example that takes a little bit of time (~40 seconds on my laptop), 
  try for instance this:

    ./main_no_omp.exe 0 4 401 1000000 output.dat

- To time it, run it through the "time" command:
    
    time ./main_no_omp.exe 0 4 401 1000000 output.dat

  (Focus on the "real" row of the time output.)


This non-parallized program can be used to demonstrate the simplest (and sometimes 
useful) approach to parallelization, namely just running multiple instances of the same
program with different inputs (and writing to different output files). 

- For instance you start the same program from two different terminal windows, with different input/output:

    time ./main_no_omp.exe 0 2 201 1000000 output.dat.part1
    time ./main_no_omp.exe 2 4 201 1000000 output.dat.part2

  and then combine the data files into one by doing e.g. this:

    cat output.dat.part1 output.dat.part2 > output.dat

To be a bit more fancy, you can do everything from one terminal window by starting separate 
runs "in the background" by adding "&" to the command.

  - Try starting two runs in the background like this

    ./main_no_omp.exe 0 2 201 1000000 output.dat.part1 &
    ./main_no_omp.exe 2 4 201 1000000 output.dat.part2 &

- To see the running jobs, run the command "jobs" command.

- To abort a running job, you can either kill the process code (use the "top" command),
  or bring the job to the foreground ("fg" command), e.g. do this to stop job number 1:

    jobs
    fg 1
    <ctrl-c>

- Again output files can be combined with "cat":

    cat output.dat.part1 output.dat.part2 > output.dat  



main_omp_outer_loop.cpp
-----------------------

Similar to main_no_omp.cpp, but now using OpenMP to parallelize the 
outer loop. The line "#pragma omp for" divides the outer for loop
among the available threads.

To avoid thread conflicts in the output, the code is set up so that 
each thread writes data to it's own output file. These files can then
be combined later, e.g. using the "cat" command.

- Build like this (note the "-fopenmp" flag):

    g++ -O3 main_omp_outer_loop.cpp -fopenmp -o main_omp_outer_loop.exe

- Set the number of threads to use, e.g.

    export OMP_NUM_THREADS=4

- Run like this:

    ./main_omp_outer_loop.exe <A_min> <A_max> <n_A> <n_cycles_per_thread> <output_file_name>

- So a run that includes timeing with the "time" command could be:

    time ./main_omp_outer_loop.exe 0 4 401 1000000 output.dat

- Look at the output files



main_omp_inner_loop_inmem.cpp
-----------------------------

Similar to main_omp_outer_loop.cpp, but now storing the results from all threads
in memory during the run (in a shared armadillo matrix) and only writing a single 
output file at the end.

- Build like this (now also with the -laramdillo flag):

    g++ -O3 main_omp_outer_loop_inmem.cpp -fopenmp -o main_omp_outer_loop_inmem.exe

- Run like this:

    ./main_omp_outer_loop_inmem.exe <A_min> <A_max> <n_A> <n_cycles_per_thread> <output_file_basename>

  after having set OMP_NUM_THREADS (see above)



main_omp_inner_loop.cpp
-----------------------

Similar to main_omp_outer_loop.cpp, but now using OpenMP to parallelize the 
inner loop (a loop with n_cycles_per_thread iterations). 

As the variable name suggestes, in this example we treat n_cycles_per_thread 
as the number of cycles *per thread*, i.e. we don't use "#pragma omp for" 
to split up the inner loop. This is then an example of performing similar 
computations on each thread and taking an average as the combined result.

(For instance, in the case of MCMC, the threads could represent independent
"walkers" that each should perform n_cycles_per_thread iterations of the MCMC 
algorithm, before the combined results are formed.)

In this example the results from different threads are combined before
the parallel block ends, and then just the single (main) thread writes to
file, so no need for multiple output files.

(Build and run using similar commands as above.)

