### Project repository for project 4

Group members: Frida Marie Engøy Westby, Marius Torsvoll, Jon Alexander Prøitz, Sverre Wehn Noremsaune



### About the repo

This repo contains code for simulating a phase transition in a ferromagnet using the 2D Ising model. The `lattice.cpp`file can be used as a library in your own code, but might need some tweaks to suit your needs. The program will output its data files in the `data/`repository.



Special requirements: OpenMP

To compile the project, run `make all`. 

To run the project, we highly recommend using the `run_project.sh`script, as this sets up the necessary folders and recompiles the project if needed. The script might need permission to run, which can be done with `chmod a+x run_project.sh`. The script will also run the plotting script, `plot.sh` (which might also need permission to run), to generate the necessary folders and feed files as needed to the python scripts that actually handle the plotting. This can be run separately from the `run_project.sh` script as soon as you have generated the necessary data files.