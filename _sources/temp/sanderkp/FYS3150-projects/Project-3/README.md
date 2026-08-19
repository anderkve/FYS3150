problem 5 and 6: g++ test.cpp src/particle_problem5.cpp src/penningtrap_problem6.cpp -I include -larmadillo -o main_test
problem 8: g++ main_problem8.cpp src/particle_problem5.cpp src/penningtrap_problem6.cpp -I include -larmadillo -o main_prob8

In PenningTrap: if you use the Euler_evolve or RK4_evolve methods i recomend you use timesteps to be 0.0...1 with however many
zeros you need and a number between 1 and 0 with only zeros ending in a 2 or a 1 depending on what you use for time.
Furthermore should time be a integer
