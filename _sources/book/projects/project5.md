# Project 5

```{note}
This project description is still somewhat incomplete. It will be completed in the next couple of days.
```

## Practicalities

- **Deadline**: Monday, December 13, 23:59.
- **Format:**
  - A scientific report, typeset in LaTeX, delivered as a pdf file on Canvas.
  - Code (with comments, of course) on a GitHub repo, with the repo link provided in your report.
  - You *must* deliver via your group on Canvas (even if you are working alone).

- **Collaboration:** We strongly encourage you to collaborate with others, in groups of up to four students. The group hands in a single pdf. Remember to list everyone's name in the pdf.

- **Reproducibility:** Your code should be available on a GitHub repo. You can refer to relevant parts of your code in your answers. Make sure to include a README file in the repo that briefly explains how the code is organized, and how it should be compiled and run in order for others to reproduce your results.

- **Figures:** Figures included in your LaTeX document should preferrably be made as vector graphics (e.g. `.pdf` files), rather than raster graphics (e.g. `.png` files).


## Introduction

The goal of this project is to simulate the two-dimensional time-dependent Schrödinger equation, and use it to study a double-slit-in-a-box setup and variations thereof. In short, you will write a simulation that can give results [`like this`](https://www.dropbox.com/s/76sdq2ecp0ekiin/animation.mp4?dl=0). (Note that you will not be required to animate your results, but it's quite instructive and fun to do so.)

The key methodological aspects of the projects are:
- Understanding partial differential equations (PDEs)
- Applying the Crank-Nicholson method in 2+1 dimensions
- Working with complex numbers in code
- Getting them indices straight...
- Using conserved quantities as stability checks

## The Schröding equation

The general formulation of the time-dependent Schrödinger equation is 

$$
i \hbar \frac{d}{dt} |\Psi\rangle = \hat{H} |\Psi\rangle,
$$

where $\hat{H}$ is some Hamiltonian operator and $|\Psi\rangle$ is the quantum state ([whatever that is](https://plato.stanford.edu/entries/qt-issues/#OntoIssu)). While we're not really sure what the quantum state *is*, we do know it is related to probability ([whatever that is](https://plato.stanford.edu/entries/probability-interpret/)) through the [Born rule](https://en.wikipedia.org/wiki/Born_rule), which we will use extensively in this project. More details below.


We will now consider the case of a *a single, non-relativistic particle in two dimensions*. If we work in "position space", the quantum state $|\Psi\rangle$ can then be expressed as a *complex valued* function $\Psi(x,y,t)$, historically called the *the wave function*. The Schrödinger equation then becomes

$$
i \hbar \frac{\partial}{\partial t} \Psi(x,y,t) = -\frac{\hbar^2}{2m} \left( \frac{\partial^2}{\partial x^2} + \frac{\partial^2}{\partial y^2} \right) \Psi(x,y,t) + V(x,y,t) \Psi(x,y,t).
$$

Here the terms $-\frac{\hbar^2}{2m} \frac{\partial^2 \Psi}{\partial x^2}$ and $-\frac{\hbar^2}{2m} \frac{\partial^2 \Psi}{\partial y^2}$ are expressions of the kinetic energy, corresponding to $\frac{p^2}{2m}$ from classical physics, with $m$ being the particle mass. The external environment is encoded in *the potential* $V$. We will only consider the case of a *time-independent* potential, $V = V(x,y)$.

When working in position space like this, the Born rule takes the form

$$
p(x,y\,;t) = |\Psi(x,y,t)|^2 = \Psi^*(x,y,t) \, \Psi(x,y,t),
$$

where $p(x,y\,;t)$ denotes the probability density for detecting the particle at position $(x,y)$ if we made a position measurement at time $t$. 


To keep things simple, we will in this project assume that all dimensionful variables have been scaled away, leaving us with a "bare" Schrödinger equation on the form

$$
i \frac{\partial u}{\partial t} = -\frac{\partial^2 u}{\partial x^2} - \frac{\partial^2 u}{\partial y^2} + v(x,y) u.
$$ (schr_eq)

So in this equation *all the variables are dimensionless*, which means you do not have to worry about units for this project. Our goal is to solve equation {eq}`schr_eq` numerically to determine the evolution of the "wave function" $u(x,y,t)$ in the presence of some potential $v(x.y)$.

In our new notation the Born rule takes the form

$$
p(x,y;t) = |u(x,y,t)|^2 = u^*(x,y,t) \, u(x,y,t).
$$

assuming the wave function $u(x,y,t)$ has been properly normalized.



## Notation

Below we define the basic notation we will use for this project. 

- $x \in [0,1]$, $y \in [0,1]$, $t \in [0,T]$.
- We'll use equal an equal step size $h$ in both the $x$ and $y$ directions.
- $x \rightarrow x_i = i h$, with $i = 0, 1, \ldots, M-1$. (Don't confuse this index $i$ with the imaginary unit $i$ appearing in the Schrödinger equation!)
- $y \rightarrow y_j = j h$, with $j = 0, 1, \ldots, M-1$.
- $t \rightarrow t_n = n \Delta t$, with $n = 0, 1, \ldots, N_t-1$.
- $u(x,y,t) \rightarrow u(ih,jh,n \Delta t) \equiv u_{ij}^n$. Note that the superscript $n$ here is simply a time index --- we have not raised $u_{ij}$ to the $n$-th power!
- The matrix $U$^n is a matrix with elements $u_{ij}^n$.
- $v(x,y) \rightarrow v(ih,jh) \equiv v_{ij}$.
- The matrix $V$^n is a matrix with elements $v_{ij}^n$.

Note:

- $M$ is the number of *points* along the $x$ axis, including the boundary points. Thus, the $x$ axis has been discretized using $M-1$ *steps*, and there are $M-2$ "internal points" $x_1, \ldots, x_{M-2}$, i.e. excluding the boundary points $x_0$ and $x_{M-1}$.
- Similarly for the $y$ axis, again with $M$ being the number of *points*.
- We will mix index notation with and without commas as needed for clarity. So keep in mind that e.g. $u_{ij}$ and $u_{i,j}$ mean the same thing.


## Intial and boundary conditions

Throughout this project we will assume Dirchlet boundary conditions in the $xy$ plane:

- $u(x=0, y, t) = 0$
- $u(x=1, y, t) = 0$
- $u(x, y=0, t) = 0$
- $u(x, y=1, t) = 0$

This assumption simplifies the implemention of the Crank-Niocolson scheme quite a bit, so keep in mind that the code we write will have this assumption baked in from the beginning.

For the initial wave function $u(x,y,t=0)$ we will typically use a quantum mechanical Gaussian wavepacket, to be specified in the problems below.


## Problems

### Problem 0

Not really a problem but an advice: Before diving into this project, take a look at the [Armadillo documentation](http://arma.sourceforge.net/docs.html) to see how you can work with complex numbers. For instance, look up terms like `cx_double`, `cx_vec`, `cx_mat`, etc. 

In practice, this simply means having your Armadillo objects filled with the standard `std::complex<double>` type in C++. You should read about that [here](https://en.cppreference.com/w/cpp/numeric/complex) and take a look at the examples. 

PS: You might also find `sp_cx_mat` in Armadillo very useful at some point...


### Problem 1

Show analytically that by discretizing equation {eq}`schr_eq` according to the Crank-Nicolson approach, you end up with this expression:

$$
u_{ij}^{n+1}  -  r \left[u_{i+1,j}^{n+1} - 2u_{ij}^{n+1} + u_{i-1,j}^{n+1}\right]  -  r \left[u_{i,j+1}^{n+1} - 2u_{ij}^{n+1} + u_{i,j-1}^{n+1}\right]  +  \frac{i \Delta t}{2} v_{ij} u_{ij}^{n+1} \\
= u_{ij}^n  +  r \left[u_{i+1,j}^n - 2u_{ij}^n + u_{i-1,j}^n\right]  +  r \left[u_{i,j+1}^n - 2u_{ij}^n + u_{i,j-1}^n\right]  -  \frac{i \Delta t}{2} v_{ij} u_{ij}^n
$$ (CN_eq1)


### Problem 2

One of the tricky things when implementing Crank-Nicolson with two spatial dimensions is getting the matrices and all the different indices right. When taking into account our choice of simple boundary conditions, equation {eq}`CN_eq1` can be expressed in matrix form as 

$$
A \,\vec{u}^{n+1} = B \,\vec{u}^{n}.
$$ (CN_eq2)

Here the vector $\vec{u}^n$ (and similarly $\vec{u}^{n+1}$) is a column vector that contains the $u_{ij}$ values for *all the internal points* of the $xy$ grid at time step $n$. In row-form it would look like this:

$$
\vec{u}^n = \left[(u_{1,1}^n, u_{2,1}^n, \ldots, u_{M-2,1}^n), (u_{1,2}^n, u_{2,2}^n, \ldots u_{M-2,2}^n), \ldots, (u_{1,M-2}^n \ldots u_{M-2,M-2}^n)\right].
$$

The parentheses are just added to make it clear where there is a change in the second index $j$. Thus the $\vec{u}$ vectors have length $(M-2)^2$, and the matrices $A$ and $B$ are thus (potentially very large) matrices of size $(M-2)^2 \times (M-2)^2$. 

Now we need some code to help us get this straight in our program:

- Write a code snippet that translates a pair of indices $(i,j)$ into a corresponding single index $k$ that gives the position of $u_{ij}$ in the vector $\vec{u}$.

- Start with $(M-2)=3$ as a concrete example and write a code snippet that can take a number $r$ and two lenght-9 vectors $\vec{a}$ and $\vec{b}$ and produce the following matrices:

  $$
  A = 
  \begin{bmatrix}
  a_0 &  -r  &  0   &  -r   &   0   &  0    &  0   &  0    &  0    \\
  -r  &  a_1 &  -r  &  0    &   -r  &  0    &  0   &  0    &  0    \\
  0   &  -r  &  a_2 &  0    &   0   &  -r   &  0   &  0    &  0    \\
  -r  &  0   &  0   &  a_3  &   -r  &  0    &  -r  &  0    &  0    \\
  0   &  -r  &  0   &  -r   &   a_4 &  -r   &  0   &  -r   &  0    \\
  0   &  0   &  -r  &  0    &   -r  &  a_5  &  0   &  0    &  -r   \\
  0   &  0   &  0   &  -r   &   0   &  0    &  a_6 &  -r   &  0    \\
  0   &  0   &  0   &  0    &   -r  &  0    &  -r  &  a_7  &  -r   \\
  0   &  0   &  0   &  0    &   0   &  -r   &  0   &  -r   &  a_8  \\
  \end{bmatrix}
  $$

  $$
  B = 
  \begin{bmatrix}
  b_0 &  r   &  0   &  r    &   0   &  0    &  0   &  0    &  0    \\
  r   &  b_1 &  r   &  0    &   r   &  0    &  0   &  0    &  0    \\
  0   &  r   &  b_2 &  0    &   0   &  r    &  0   &  0    &  0    \\
  r   &  0   &  0   &  b_3  &   r   &  0    &  r   &  0    &  0    \\
  0   &  r   &  0   &  r    &   b_4 &  r    &  0   &  r    &  0    \\
  0   &  0   &  r   &  0    &   r   &  b_5  &  0   &  0    &  r    \\
  0   &  0   &  0   &  r    &   0   &  0    &  b_6 &  r    &  0    \\
  0   &  0   &  0   &  0    &   r   &  0    &  r   &  b_7  &  r    \\
  0   &  0   &  0   &  0    &   0   &  r    &  0   &  r    &  b_8  \\
  \end{bmatrix}
  $$

  If you look closely you will see that the matrix structure is based on submatrices of size $(M-2) \times (M-2)$. Make sure your code works for a general value of $(M-2)$, even though we're testing it for the simple case $(M-2)=3$.

- Now you are ready to write a function for your program that, using inputs $M$, $h$, $\Delta t$ and the matrix $V$ as input, can fill two $(M-2)^2 \times (M-2)^2$ matrices $A$ and $B$ according to the above pattern, with

  $$
  a_k &= 1 + 4r + \frac{i \Delta t}{2} v_{ij},\\
  b_k &= 1 - 4r - \frac{i \Delta t}{2} v_{ij}.
  $$

  (Here the $i$ in $i \Delta t$ is again the imaginary unit.)



### Problem 3

When we have the matrices $A$ and $B$, finding the next $\vec{u}^{n+1}$ from the current $\vec{u}^n$ in a time loop can be done in two steps:

  1. Perform the matrix multiplication $B \, \vec{u}^n = \vec{b}$.

  2. Solve the matrix equation $A \, \vec{u}^{n+1} = \vec{b}$ for the unknown $\vec{u}^{n+1}$.

Given what you know about matrix $A$, discuss which approaches might be well-suited to solve $A \, \vec{u}^{n+1} = \vec{b}$. For your code you can either implement a solver yourself or use a built-in solver in Armadillo.


### Problem 4

- Write a part of your program that can set up the initial state $u_{ij}^0$ based on the following expression for a Gaussian wave packet

  $$
  u(x,y,t=0) = \ldots \textbf{[to be added]}
  $$

  Make sure that your initial state $u_{ij}^0$ satisfies the boundary conditions. Also add code that normalizes your initial state such that 

  $$
  \sum\limits_{i,j} u_{ij}^* u_{ij} = 1,
  $$

  i.e. that the total probability in our 2D probability distribution $p_{ij} = u_{ij}^* u_{ij}$ starts out normalized to 1.


### Problem 5

Write a part of your program that initializes the potential $V$. To construct the barriers used for the double-slit (and other configurations) we will simply set the elements $v_{ij}$ of $V$ that correspond to points inside the barriers to some high constant value $v_{ij} = v_0$.


### Problem 6

Put everything together into a program that... **[details to be added]**


### Problem 7

The total probability ($= 1$) in the probability distribution $p_{ij} = u_{ij}^* u_{ij}$ should be conserved over time. This is a nice consistency check for our code. Run your simulation with the following settings **[to be added]** and make a plot of the total probability as function of time. 



### Problem 8

Run your simulation with the following settings **[to be added]**. 

- Make (at least) three colourmap plots that illustrate the time evolution of the 2D probability distribution given by $p_{ij} = u_{ij}^* u_{ij}$.

- For the same time steps, also make colourmap plots that show $\text{Re}(u_{ij})$ and $\text{Im}(u_{ij})$.


### Problem 9

- Run your simulation with the following settings **[to be added]**. Make a plot of the 1D probability distribution for detecting the particle along a strip near the right-hand wall (i.e. the screen position in a normal double-slit experiment).

- Adjust your code to also simulate single-slit and triple-slit experiments. Run your simulations with the following settings **[to be added]**. Plot similar 1D probability distributions as in the previous problem, i.e. 1D probability distributions along the right-hand wall.


### Problem X

If you find it useful, feel free to make some animations of your simulation and put links to these in your report! (However, don't overdo it --- your report will be more readable if the reader doesn't have to switch between the report and watching animations all the time.)


<!-- 
### Problem 10

Run your simulation with the following settings **[to be added]** and for a total time of **[to be added]**. Make a plot that shows the probability of detecting the particle in the left half of the box, $Prob(\text{detect particle in region} x < 0.5)$, as a function of time. 
 -->


### Code snippets

Here we might add suggestions for code layout, and some short code snippets.


<!-- 

$$
A = 
\begin{bmatrix}
a_0 & -r  &  0   & 0      &     -r  &  0  &  0   & 0      &     0   &  0  &  0   & 0      &   0   &  0  &  0      & 0       \\
-r  & a_1 & -r   & 0      &     0   & -r  &  0   & 0      &     0   &  0  &  0   & 0      &   0   &  0  &  0      & 0       \\
0   & -r  &  a_2 & -r     &     0   &  0  & -r   & 0      &     0   &  0  &  0   & 0      &   0   &  0  &  0      & 0       \\
0   &  0  &  -r  & a_3    &     0   &  0  &  0   & -r     &     0   &  0  &  0   & 0      &   0   &  0  &  0      & 0       \\
-r  &  0  &  0   & 0      &     a_4 & -r  &  0   & 0      &     -r  &  0  &  0   & 0      &   0   &  0  &  0      & 0       \\
0   & -r  &  0   & 0      &     -r  & a_5 & -r   & 0      &     0   & -r  &  0   & 0      &   0   &  0  &  0      & 0       \\
0   &  0  & -r   & 0      &     0   & -r  &  a_6 & -r     &     0   &  0  & -r   & 0      &   0   &  0  &  0      & 0       \\
0   &  0  &  0   & -r     &     0   &  0  &  -r  & a_7    &     0   &  0  &  0   & -r     &   0   &  0  &  0      & 0       \\
0   &  0  &  0   & 0      &     -r  &  0  &  0   & 0      &     a_8 & -r  &  0   & 0      &   -r  &  0  &  0      & 0       \\
0   &  0  &  0   & 0      &     0   & -r  &  0   & 0      &     -r  & a_9 & -r   & 0      &   0   & -r  &  0      & 0       \\
0   &  0  &  0   & 0      &     0   &  0  & -r   & 0      &     0   & -r  &  a_{10} & -r  &   0   &  0  & -r      & 0       \\
0   &  0  &  0   & 0      &     0   &  0  &  0   & -r     &     0   &  0  &  -r  & a_{11} &   0   &  0  &  0      & -r      \\
0   &  0  &  0   & 0      &     0   &  0  &  0   & 0      &     -r  &  0  &  0   & 0      &   a_{12} & -r  &  0   & 0       \\
0   &  0  &  0   & 0      &     0   &  0  &  0   & 0      &     0   & -r  &  0   & 0      &   -r  & a_{13} & -r   & 0       \\
0   &  0  &  0   & 0      &     0   &  0  &  0   & 0      &     0   &  0  & -r   & 0      &   0   & -r  &  a_{14} & -r      \\
0   &  0  &  0   & 0      &     0   &  0  &  0   & 0      &     0   &  0  &  0   & -r     &   0   &  0  &  -r     & a_{15}  \\
\end{bmatrix}

$$

 -->

<!-- 
Assume a $2 \times 2$ lattice with periodic boundary conditions.

- **a)** Summarize all possible states of the system by setting up a table with four coloumns showing the following quantities
  - number of spins in state +1
  - total energy
  - total magnetization
  - degeneracy

- **b)** Find analytical expressions for 
  - $Z$
  - $\langle \epsilon \rangle$
  - $\langle \epsilon^2 \rangle$
  - $\langle |m| \rangle$
  - $\langle m^2 \rangle$
  - the specific heat capacity (normalized to number of spins):

  $$
  C_V = \frac{1}{N} \frac{1}{k_B T^2}(\langle E^2 \rangle - \langle E \rangle^2) 
  $$

  - the susceptibility (normalized to number of spins): 

  $$
  \chi = \frac{1}{N} \frac{1}{k_B T}(\langle M^2 \rangle - \langle |M| \rangle^2)
  $$
  
We will use these analytical results to test our code.

```{note}
There was a typo in a previous version, where $C_V$ and $\chi$ were defined using $\epsilon$ and $m$ rather than $E$ and $M$. This is now corrected, along with the normalization factor $\frac{1}{N}$ in front to enusure that we normalize the heat capacity and susceptibility to the total number of spins in the system. Apologies for the confusion!
```


### Problem 2

In our Monte Carlo code we will repeatedly need the Boltzmann factor $e^{-\beta \Delta E}$, where 

$$
\Delta E = E_{\textrm{after}} - E_{\textrm{before}}
$$

is the energy shift due to *flipping a single spin*.

**a)** Consider a 2D lattice of arbitrary size. Show that there are only five possible values $\Delta E$ can take.

**b)** How can you use this result to avoid repeatedly calling the exponential function `exp(...)` in your code?


### Problem 3

There are many ways to implement periodic boundary conditions. The simplest is a set of if-tests. That works (and may be a useful starting point!), but if-tests inside loops can slow down your code. (It can hinder compiler optimizations.) Can you come up with a more efficient way of implementing periodic boundary conditions in your code?


### Problem 4

Time to actually write some code! 

**a)** Implement a code for the Ising model which uses the Markov Chain Monte Carlo approach to sample spin configurations $\mathbf{s}$ and computes 

  - $\langle \epsilon \rangle$
  - $\langle |m| \rangle$
  - $C_V$
  - $\chi$

**b)** Validation: For a temperature of $T = 1.0\,J/k_B$, compare your results to the analytical results from Problem 1. (Feel free to compare for other temperature values as well, or simply make plots of these quantities versus temperature.)

**c)** How many **Monte Carlo cycles** do you need to get good agreement with the analytical result? (Here *one Monte Carlo cycle* corresponds to *$N$ attempted spin flips*.)


### Problem 5

Now we will use a lattice with size $L=20$ and study the **burn-in time** (or **equilibration time**), measured in number of Monte Carlo cycles. 

**a)** Make plots that show how the numerical estimates of $\langle \epsilon \rangle$ and $\langle |m| \rangle$ evolve with the number of Monte Carlo cycles. You should produce graphs for temperatures $T = 1.0\,J/k_B$ and $T = 2.4\,J/k_B$, and starting from *ordered* (all spins pointing the same way) and *unordered* (random) initial states. 

**b)** Based on these plots, how long would you say the burn-in time is?

**c)** What is the argument for not using the samples generated during the burn-in time? 


### Problem 6

Now let's move beyond mere expectation values and see how we can use our MCMC to estimate the full probability distribution for $\epsilon$. 

For $L=20$, approximate the probability function $p_{\epsilon}(\epsilon;T)$ for $T = 1.0\,J/k_B$ and $T = 2.4\,J/k_B$ by creating normalized histograms of generated $\epsilon$ samples. (Keep an eye on bin widths and remember that $\epsilon$ is not a continuous variable.) Comment on your results, in particular on the variance of the two distributions. 
 

### Problem 7

Now parallelize your code using either OpenMP or MPI. Perform some timing tests to estimate the speed-up factor resulting from the parallelization.

```{note}
As discussed in the lectures, there are basically three different approaches you can take here, corresponding to three different levels at which you can parallelize your code:

1. *At the temperature level:* You can parallelize the outer loop over temperature values (see Problem 8, which is where parallelization becomes important)
2. *At the level of MCMC "walkers":* You can use multiple threads to perform multiple independent MCMC runs in parallel and combine their results.
3. *At the level of spin flipping:* You could parallelize the part of the code where you generate new states by attempting to flip N spins.

We recommend you do either approach 1 or 2. (You only need to do one approach.) Approach 1 is probably the easiest. Approach 2 is the standard approach to parallelizing a single MCMC run (i.e. when there isn't any scan over some external parameter, like $T$ in our case.) Approach 3 would by far be the most complicated and it is probably also the least efficient. 
```

### Problem 8

Now we will start investigating phase transitions. 

```{note}
For a brief introduction to the phase transition of the 2D Ising model, see Chapters 13.4 and 13.4.1 of Morten Hjort-Jensen's lecture notes. See also the brief theoretical summary for Problem 9.
```

- **a)** For lattices of size $L = 40,60,80,100$ (and higher if you want), make plots of $\langle \epsilon \rangle$, $\langle |m| \rangle$, $C_V$ and $\chi$ as function of temperature $T$. (Plot the results for different $L$ values in the same figure.) Focus on temperatures in a range around $T \in [2.1, 2.4]\,J/k_B$. Make sure to use sufficiently small temperature steps, at least in the region where the graphs change most rapidly.

- **b)** Do you see an indication of a phase transition?

- **c)** What is the critical temperature $T_c(L)$ for the different lattice sizes $L$? Use the $\chi$ or $C_V$ results to determine $T_c(L)$.

```{note}
Some suggestions in case you are short on time because the code is slower than expected: 

- Make sure you're not running way more temperature points than necessary. As suggested in the lectures, first run a scan with large T steps, to roughly identify the subregion of $T$ values where the graphs change most quickly. (E.g. only 10 points on the suggested $T$ range can be sufficient here.) Then run a second scan that zooms in on the much smaller $T$ range needed to identify $T_c$. Again, you can probably get good results with as few as 10 $T$ points -- though more points always make for better results. 

- If you're having trouble with OpenMP/MPI parallelisation, remember that to just make sure you get the numerical results you need, you can always do "dummy parallelisation" by just running multiple instances of your program. (Use separete terminal windows, or run your program in the background with the `&` command, e.g. `./main.exe <command line options> &`. You can view your background jobs with `jobs` and bring them to the foreground with `fg <job number>`.) This "manual" way of splitting up tasks works well assuming that your program can take options like `L`, `Tmin`, `Tmax`, `deltaT` (or `n_Tsteps`) as command-line arguments.

- Perhaps you can afford to reduce the number of Monte Carlo cycles a bit and still get decent results? E.g. halving the number of cycles should half the program runtime.

- Keep in mind that you don't need to finish all the runs for Problem 8 to get started on Problem 9. To get a first result for Problem 9 you basically only need to identify $T_c$ for two of the $L$ values in Problem 8. So you can do Problem 9 in parallel with the runs for Problem 8, and then just update your plots/numbers as new runs in Problem 8 finishes. 
```



### Problem 9

The critical temperature for an *infinite* ($L=\infty$) 2D Ising model was found analytically by Lars Onsager in 1944. The result is

$$
T_c(L=\infty) = \frac{2}{\ln(1 + \sqrt{2})}\,J/k_B \approx 2.269\,J/k_B
$$ 

Our task now is to try to numerically estimate $T_c(L=\infty)$ using our numerical results for $T_c(L)$ of *finite* systems.

Using your set of $L$ and $T_c(L)$ values from Problem 8 as data points, and the scaling relation

$$
T_c(L) - T_c(L=\infty) = a L^{-1}
$$ (scaling_relation)

where $a$ is a constant, extract an estimate for $T_c(L=\infty)$ and compare it to Onsager's analtical result.

```{note}
Hint: If you are unsure about how to approach this, try to first plot your data points in such a way that they, according to the relation above, should fall on a straight line.
```

```{note}
Hint 2: If you find that doing a linear fit (a.k.a. linear least squares, a.k.a. linear regression, ...) could be useful, we don't expect you to discuss that method in detail in your report. Feel free to simply apply one of the many tools available, e.g. `scipy.stats.linregress`.
```


**Theoretical background:** *What follows here is a very brief summary. For more information see Chapters 13.4 and 13.4.1 of Morten Hjort-Jensen's lecture notes, and references therein.* 

One of the many fascinating aspects of so-called critical phenomena is that vastly different physical systems can exhibit the same behaviour close to their critical point (here: critical temperature). This behaviour is decsribed by power laws, with exponents called *critical exponents*. For the *infinite* 2D Ising model, the mean magnetization, heat capacity and susceptibility behave as 

$$
\langle |m| \rangle &\propto |T - T_c(L=\infty)|^{\beta}\\
C_V &\propto |T - T_c(L=\infty)|^{-\alpha}\\
\chi &\propto |T - T_c(L=\infty)|^{-\gamma}
$$

for temperatures $T$ close to $T_c$, with critical exponents $\beta=1/8$, $\alpha=0$ and $\gamma=7/4$. Both $C_V$ and $\chi$ diverge near $T_c$. Similarly, the *correlation length* (here: the typical lenght scale of regions with aligned spins) $\xi$ also diverges near the critical point,

$$
\xi \propto |T - T_c(L=\infty)|^{-\nu}
$$ (corr_length)

with critical exponent $\nu = 1$. However, since we are studying a *finite* system, the largest correlation length is $\xi = L$, which we associate with the critical temperature of the finite system, $T = T_c(L)$. Inserting this into equation {eq}`corr_length` gives rise to equation {eq}`scaling_relation` above.

Using this relation we see that, when $T$ is close to $T_c(L)$, we expect the mean magnetization, heat capacity and susceptibility to depend on the system size $L$ as 

$$
\langle |m| \rangle &\propto L^{-\beta/\nu}\\
C_V &\propto L^{\alpha/\nu}\\
\chi &\propto L^{\gamma/\nu}.
$$

**Good luck!** 

----

### Code snippets

- See the code snippets in [`code_examples/omp_parallelization`](https://github.com/anderkve/FYS3150/tree/master/code_examples/omp_parallelization) for some simple examples on parallelization using OpenMP.

- For some illustrations on how you can use the C++ `<random>` library for random number generation, see code examples in [`code_examples/random_number_generation`](https://github.com/anderkve/FYS3150/tree/master/code_examples/random_number_generation). These examples use a Mersenne Twister generator. Some of the examples demonstrate how one can do seeding when working with multiple OpenMP threads.

 -->
