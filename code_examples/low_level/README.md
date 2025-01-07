# Welcome!

This is a README for a now work in progress.
I will be adding some low level optimisation examples along with some tips, tricks and useful links (not the video game character).

##### A note on the language here used:
The text may appear less serious than the information presented.
Many of the things presented in this subdirectory may prove useful in a general sense and in some cases critical for adequate performance.
The language used is more jovial with some attempts to jokes as this is the nature of low-level optimisation in my personal opinion.
It is not strictly necessary to apply optimisation techniques all the time everywhere but rather only on the occasions where necessary (more on **when** later).
In most cases, for me at least, low-level optimisation takes the form of a mini-game driven by the question "_Can I make it go faster?_" where it becomes a fun pastime rather than work.
As such, I have chosen to apply a language that shows just that:
>low-level optimisation is fun.

## What will come

In this directory I will push examples of
1. [ ] Array of structures (AoS) vs Structure of Arrays (SoA)
   2. [ ] ... vs Entity Component System (ECS)
3. [ ] The cost of an arithmetic operation
4. [ ] The order of arithmetic operations (it matters)
5. [ ] Superscalar CPU, i.e. built-in parallelisation between float and integer operations
6. [ ] Fixed point arithmetics

## The project

I believe the best way to learn to optimise (or simply program) at low-level is to have a project.
Therefore I have set out to write a complete program which **you** can play around with and in which **I** can show you how to apply the different optimisation techniques.
When I write "complete program" I mean complete with regard to the checklist above; you are free to take the code and expand or reduce it in whichever way you fancy, and please feel free to do so!

For the project I will simulate a 2D box with points (holes) of high attraction in which a number of small particles will be injected.
To begin the particles will not interact with each other nor will the holes interact between each other.
If I find the time and courage I will add a Graphic User Interface, which will probably help with finding errors and also it might look nice.

First the full program will be written without optimisation.
Once the program works I will implement optimisations through `inline` functions via their respective header files.
Each implemented optimisation can be found in the subsections for the different optimisation techniques (see **What will come**), where they will be presented along with the necessary background information to understand _why_ and/or _how_ it works.

[//]: # (### Rules for each shape)

[//]: # ()
[//]: # (Each shape will interact with other shapes based on their individual and unique set of rules.)

[//]: # (As a general rule the shapes are not allowed to overlap.)

[//]: # (These are the rules for **circles**:)

[//]: # (* experiences an equal attractive force to squares and triangles)

[//]: # (* experiences a repulsive force to other circles)

[//]: # (* can pass through the edges of the box to appear on the opposite side of where it exited)

[//]: # ()
[//]: # (The **squares** have the rules:)

[//]: # (* If it touches a triangle its size is reduced by half)

[//]: # (* If it touches a circle its size is increased by a fourth)

[//]: # (* If the size of the square is outside of MINIMUM < x < MAXIMUM it is deleted)

[//]: # (* Is bounded by the box)

[//]: # (* OPTIONAL: experiences an attractive force toward the shape that will change the size of the square toward &#40;MAXIMUM - MINIMUM&#41; / 2)

[//]: # (* OPTIONAL: experiences a repulsive force from the shape that would delete it)

[//]: # ()
[//]: # (The **triangles** have the rules:)

[//]: # (* deleted if it hits three different shapes in a row or three triangles in a row)

[//]: # (* duplicates if it hits the edge of the box)

### Simulation

All particles will have the same entry point with velocities randomised within a range.
To update their positions and velocities I will be using Heun's method.