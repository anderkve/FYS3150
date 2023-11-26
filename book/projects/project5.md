# Project 5

```{note}
There will probably be small updates to the project description in the coming days, so check back regularly!
```

## Practicalities

- **Deadline**: Tuesday, December 12, 23:59.
- **Format:**
  - A scientific report, typeset in LaTeX *using the provided template* (see [this page](../writing_reports/introduction_to_latex.md)), delivered as a pdf file on Canvas.
  - Code (with comments, of course) on a UiO GitHub repo ([github.uio.no](https://github.uio.no/)), with the URL to you repo written in the pdf document. 
  - You *must* deliver via your group on Canvas (even if you are working alone).

- **Collaboration:** We strongly encourage you to collaborate with others, in groups of up to four students. The group hands in a single pdf. Remember to list everyone's name in the pdf.

- **Reproducibility:** Your code should be available on a GitHub repo. You can refer to relevant parts of your code in your answers. Make sure to include a README file in the repo that briefly explains how the code is organised, and how it should be compiled and run in order for others to reproduce your results.

- **Figures:** Figures included in your LaTeX document should preferrably be made as vector graphics (e.g. `.pdf` files), rather than raster graphics (e.g. `.png` files).


## Introduction

The goal of this project is to simulate the two-dimensional time-dependent Schrödinger equation, and use it to study a double-slit-in-a-box setup and variations thereof. In short, you will write a simulation that can give results [`like this`](https://www.dropbox.com/s/76sdq2ecp0ekiin/animation.mp4?dl=0). (Note that you will not be required to animate your results, but it's quite instructive and fun to do so.)

The key methodological aspects of the projects are:
- Understanding partial differential equations (PDEs)
- Applying the Crank-Nicolson method in 2+1 dimensions
- Working with complex numbers in code
- Getting them indices straight...
- Using conserved quantities as stability checks

## The Schrödinger equation

The general formulation of the time-dependent Schrödinger equation is 

$$
i \hbar \frac{d}{dt} |\Psi\rangle = \hat{H} |\Psi\rangle,
$$

where $\hat{H}$ is some Hamiltonian operator and $|\Psi\rangle$ is the quantum state ([whatever that is](https://plato.stanford.edu/entries/qt-issues/#OntoIssu)). While we're not really sure what the quantum state *is*, we do know it is related to probability ([whatever that is](https://plato.stanford.edu/entries/probability-interpret/)) through the [Born rule](https://en.wikipedia.org/wiki/Born_rule), which we will use extensively in this project. More details below.



We will now consider the case of *a single, non-relativistic particle in two dimensions*. If we work in "position space", the quantum state $|\Psi\rangle$ can then be expressed through a *complex-valued* function $\Psi(x,y,t)$, historically called the *the wave function*. The Schrödinger equation then becomes

$$
i \hbar \frac{\partial}{\partial t} \Psi(x,y,t) = -\frac{\hbar^2}{2m} \left( \frac{\partial^2}{\partial x^2} + \frac{\partial^2}{\partial y^2} \right) \Psi(x,y,t) + V(x,y,t) \Psi(x,y,t).
$$

Here the terms $-\frac{\hbar^2}{2m} \frac{\partial^2 \Psi}{\partial x^2}$ and $-\frac{\hbar^2}{2m} \frac{\partial^2 \Psi}{\partial y^2}$ are expressions of the kinetic energy, corresponding to $\frac{p^2}{2m}$ from classical physics, with $m$ being the particle mass. The external environment is encoded in *the potential* $V$. We will only consider the case of a *time-independent* potential, $V = V(x,y)$.

When working in position space like this, the Born rule takes the form

$$
p(x,y\,;t) = |\Psi(x,y,t)|^2 = \Psi^*(x,y,t) \, \Psi(x,y,t),
$$

where $p(x,y\,;t)$ denotes the probability density for detecting the particle at position $(x,y)$ if we perform a position measurement at time $t$. The star in $\Psi^*$ denotes complex conjugation.


To keep things simple, we will in this project assume that all dimensionful variables have been scaled away, leaving us with a "bare" Schrödinger equation on the form

$$
i \frac{\partial u}{\partial t} = -\frac{\partial^2 u}{\partial x^2} - \frac{\partial^2 u}{\partial y^2} + v(x,y) u.
$$ (schr_eq)

So in this equation *all the variables are dimensionless*, which means you do not have to worry about units for this project. Our goal is to solve equation {eq}`schr_eq` numerically to determine the evolution of the "wave function" $u(x,y,t)$ in the presence of some potential $v(x,y)$.

In our new notation the Born rule takes the form

$$
p(x,y;t) = |u(x,y,t)|^2 = u^*(x,y,t) \, u(x,y,t).
$$

assuming the wave function $u(x,y,t)$ has been properly normalised.


```{note}
In this course we don't expect any background knowledge in quantum mechanics, so you are not expected to discuss a lot of quantum mechanics in your report. That is, you can simply view the Schrödinger equation as a particular type of differential equation given by equation {eq}`schr_eq`, where the solution is some complex-valued function $u(x,y,t)$, and where we have a rule for connecting this $u(x,y,t)$ to a probability distribution.
```


```{note}
*For those with some quantum mechanics background:* A question that sometimes come up during this project is how the wave function $\Psi(x,y,t)$ actually is related to the state $|\Psi\rangle$, so here's a short answer. (Again, you are not expected to discuss any of this in your reports.) 

Consider the one-dimensional case and for simplicity assume that we have discretised time and space (notation $x_i$ and $t_n$). To work in position space we can express $|\Psi\rangle$ in terms of a set of orthonormal basis states $|x_i\rangle$. (These are eigenstates of the position operator, $\hat{X} |x_i \rangle = x_i |x_i\rangle$). In doing this, the now-discretised wavefunction $\Psi(x_i,t_n) \equiv \Psi_i^n$ simply corresponds to the complex coefficients in this way of expressing $|\Psi\rangle$:

$$
|\Psi\rangle = \Psi_1^n |x_1 \rangle + \Psi_2^n |x_2 \rangle + \Psi_3^n |x_3 \rangle + \ldots,
$$

and correspondingly 

$$
\langle \Psi| =  \langle x_1 | \Psi^{n*}_1 + \langle x_2 | \Psi^{n*}_2 + \langle x_3 | \Psi^{n*}_3 \ldots
$$

Since the states $|x_i\rangle$ are orthonormal, i.e. $\langle x_i|x_j\rangle = \delta_{ij}$, we have that the wavefunction value for position $x_i$ and time $t_n$ can be viewed as the overlap between the current state $|\Psi\rangle$ and the basis state $|x_i\rangle$:

$$
\langle x_i | \Psi \rangle = \Psi_i^n.
$$

Assuming that we make a position measurement at time $t_n$, the probability $P(x_i;t_n)$ (not probability density, since we now work with discretised space) that the outcome will be $x_i$ can be expressed as 

$$
P(x_i;t_n) = | \langle x_i | \Psi \rangle |^2 = |\Psi_i^n|^2 = \Psi^{n*}_i \, \Psi^n_i.
$$

In this notation, the normalization condition for the total probability can be viewed as 

$$
1 &= \langle \Psi | \Psi \rangle\\ 
  &= \big[ \langle x_1 | \Psi^{n*}_1 + \langle x_2 | \Psi^{n*}_2 + \ldots \big] \; \big[ \Psi^n_1 |x_1 \rangle + \Psi^n_2 |x_2 \rangle + \ldots \big]\\ 
  &= \Psi^{n*}_1 \, \Psi^n_1 + \Psi^{n*}_2 \, \Psi^n_2 + \ldots \\
  &= P(x_1;t) + P(x_2;t) + \ldots
$$
```



## Notation

Below we define the basic notation we will use for this project. 

- $x \in [0,1]$, $y \in [0,1]$, $t \in [0,T]$.
- We'll use an equal step size $h$ in both the $x$ and $y$ directions.
- $x \rightarrow x_i = i h$, with $i = 0, 1, \ldots, M-1$. (Don't confuse this index $i$ with the imaginary unit $i$ appearing in the Schrödinger equation!)
- $y \rightarrow y_j = j h$, with $j = 0, 1, \ldots, M-1$.
- $t \rightarrow t_n = n \Delta t$, with $n = 0, 1, \ldots, N_t-1$.
- $u(x,y,t) \rightarrow u(ih,jh,n \Delta t) \equiv u_{ij}^n$. Note that the superscript $n$ here is simply a time index --- we have not raised $u_{ij}$ to the $n$-th power!
- The matrix $U^n$ is a matrix with elements $u_{ij}^n$.
- $v(x,y) \rightarrow v(ih,jh) \equiv v_{ij}$.
- The matrix $V$ is a matrix with elements $v_{ij}$.

Note:

- $M$ is the number of *points* along the $x$ axis, including the boundary points. Thus, the $x$ axis has been discretised using $M-1$ *steps*, and there are $M-2$ "internal points" $x_1, \ldots, x_{M-2}$, i.e. excluding the boundary points $x_0$ and $x_{M-1}$.
- Similarly for the $y$ axis, again with $M$ being the number of *points*.
- We will mix index notation with and without commas as needed for clarity. So keep in mind that e.g. $u_{ij}$ and $u_{i,j}$ mean the same thing.


## Initial and boundary conditions

Throughout this project we will assume Dirichlet boundary conditions in the $xy$ plane:

- $u(x=0, y, t) = 0$
- $u(x=1, y, t) = 0$
- $u(x, y=0, t) = 0$
- $u(x, y=1, t) = 0$

This assumption simplifies the implemention of the Crank-Nicolson scheme quite a bit, so keep in mind that the code we write will have this assumption baked in from the beginning.

For the initial wave function $u(x,y,t=0)$ we will typically use a quantum mechanical Gaussian wavepacket, to be specified in the problems below.


## Problems

### Problem 0

Not really a problem but an advice: Before diving into this project, take a look at the [Armadillo documentation](http://arma.sourceforge.net/docs.html) to see how you can work with complex numbers. For instance, look up terms like `cx_double`, `cx_vec`, `cx_mat`, etc. 

In practice, this simply means having your Armadillo objects filled with the standard `std::complex<double>` type in C++. You should read about that [here](https://en.cppreference.com/w/cpp/numeric/complex) and take a look at the examples. 

PS: You might also find `sp_cx_mat` in Armadillo very useful at some point...


### Problem 1

Show analytically that by discretizing equation {eq}`schr_eq` according to the Crank-Nicolson approach, you end up with the expression

$$
u_{ij}^{n+1}  -  r \left[u_{i+1,j}^{n+1} - 2u_{ij}^{n+1} + u_{i-1,j}^{n+1}\right]  -  r \left[u_{i,j+1}^{n+1} - 2u_{ij}^{n+1} + u_{i,j-1}^{n+1}\right]  +  \frac{i \Delta t}{2} v_{ij} u_{ij}^{n+1} \\
= u_{ij}^n  +  r \left[u_{i+1,j}^n - 2u_{ij}^n + u_{i-1,j}^n\right]  +  r \left[u_{i,j+1}^n - 2u_{ij}^n + u_{i,j-1}^n\right]  -  \frac{i \Delta t}{2} v_{ij} u_{ij}^n,
$$ (CN_eq1)

where $r \equiv \frac{i \Delta t}{2 h^2}$.


### Problem 2

One of the tricky things when implementing Crank-Nicolson with two spatial dimensions is getting the matrices and all the different indices right. When taking into account our choice of simple boundary conditions, equation {eq}`CN_eq1` can be expressed in matrix form as 

$$
A \,\vec{u}^{n+1} = B \,\vec{u}^{n}.
$$ (CN_eq2)

Here the vector $\vec{u}^n$ (and similarly $\vec{u}^{n+1}$) is a column vector that contains the $u^n_{ij}$ values for *all the internal points* of the $xy$ grid at time step $n$. In row-form it would look like this:

$$
\vec{u}^n = \left[(u_{1,1}^n, u_{2,1}^n, \ldots, u_{M-2,1}^n), (u_{1,2}^n, u_{2,2}^n, \ldots u_{M-2,2}^n), \ldots, (u_{1,M-2}^n \ldots u_{M-2,M-2}^n)\right].
$$

The parentheses are just added to make it clear where there is a change in the second index $j$. Thus the $\vec{u}$ vectors have length $(M-2)^2$, and the matrices $A$ and $B$ are thus (potentially very large) matrices of size $(M-2)^2 \times (M-2)^2$. 

Now we need some code to help us get this straight in our program:

- Write a code snippet that translates a pair of indices $(i,j)$ into a corresponding single index $k$ that gives the position of $u^n_{ij}$ in the vector $\vec{u}^n$.

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


```{note}
If you want to implement your own solver to solve $A \, \vec{u}^{n+1} = \vec{b}$, keep in mind that in the lectures we have discussed several different types of methods for solving matrix equations, including some that are easy to implement but that we haven't used in any previous project...
```


### Problem 4

Write a part of your program that can set up the initial state $u_{ij}^0$ based on the following expression for an unnormalised Gaussian wave packet

$$
u(x,y,t=0) = e^{-\frac{(x-x_c)^2}{2 \sigma_x^2} - \frac{(y-y_c)^2}{2 \sigma_y^2} + i p_x x + i p_y y}.
$$
  
Here $x_c$ and $y_c$ are the coordinates of the centre of the initial wave packet, $\sigma_x$ and $\sigma_y$ are the initial widths of the wave packet in the $x$ and $y$ directions, and $p_x$ and $p_y$ are the wave packet momenta.

Make sure that the initial state $u_{ij}^0$ satisfies the boundary conditions. 

Also, add code that normalises your initial state such that 

$$
\sum\limits_{i,j} u^{0*}_{ij} \, u^0_{ij} = 1,\\
$$

i.e. that the total probability in our 2D probability function $p^n_{ij} = u^{n*}_{ij} \, u^n_{ij}$ starts out normalized to 1.

```{note}
By requiring that $\sum\limits_{i,j} p^n_{ij} = 1$, rather than requiring $\sum\limits_{i,j} p^n_{ij} h^2 = 1$, we interpret $p^n_{ij}$ as a *probability*, not a probability *density*. That is, $p^n_{ij}$ is the probability that at time step $n$ is associated with a small grid cell of area $h^2$ centered on $(x, y) = (x_i, y_j)$.
```


### Problem 5

Write a part of your program that initialises the potential $V$. To construct the barriers used for the double-slit (and other configurations) we will simply set the elements $v_{ij}$ of $V$ that correspond to points inside the barriers to some high constant value $v_{ij} = v_0$. As our starting point we will use the following double-slit setup:

- Wall thickness in the $x$ direction: 0.02
- Wall position (centre) in the $x$ direction: 0.5
- Length of the wall piece separating the two slits (the $y$ distance between the inner edges of the two slits): 0.05
- Slit aperture (opening in the $y$ direction): 0.05
- Ensure that the slit setup is symmetric around $y = 0.5$. (So for the double-slit, the wall piece separating the two slits should be centered on $y = 0.5$.)


In Problem 9 you will also use single-slit and triple-slit configurations.

```{note}
If you want to simulate new potential configurations without having to hard-code the potentials in your program or specify a very long list of command-line arguments, you can consider using an input text file to specify the potential configuration. See the [introduction to Armadillo](sec:intro_to_armadillo) page for an easy example of how to read a text data table with Armadillo, or take a look at the [read from file](sec:read_from_file) page for an example using only the standard C++ library.
```

### Problem 6

Put everything together into a program that does (at least) the following:

1. Set the simulation parameters. It may be useful to read some or all of these as command-line input, or from an input file. The main simulation parameters are $h$, $\Delta t$, $T$, $x_c$, $\sigma_x$, $p_x$, $y_c$, $\sigma_y$, $p_y$ and $v_0$. 

2. Set up the potential matrix, $V$. 

3. Set up the initial state matrix, $U^0$.

4. Set up the matrices $A$ and $B$ required by the Crank-Nicolson approach.

5. Run the loop over time steps and store each new state $U^n$. You can either write every new state directly to file during the loop, or store them in memory and write everything to file after the loop. (Armadillo's `cx_cube` might be useful.)



### Problem 7

```{note}
Note that for this problem the output file can become large-ish (~200MB as binary file) if you save the full simulation, i.e. the full wave function at each time step.
```

In theory, the total probability ($= 1$) in the probability function $p^n_{ij} = u^{n*}_{ij}\,u^n_{ij}$ should be conserved over time. This is a nice consistency check to make sure your code works as it should.

- First run your simulation with the settings $h = 0.005$, $\Delta t = 2.5\times10^{-5}$, $T = 0.008$, $x_c = 0.25$, $\sigma_x = 0.05$, $p_x = 200$, $y_c = 0.5$, $\sigma_y = 0.05$, $p_y = 0$ and $v_0 = 0$, i.e. without any double-slit barrier.

- Make a plot of the deviation of the total probability from 1.0 as a function of time. (If the deviations are too small to be visible in your plot, consider plotting the data in a different way...)

- Run the simulation again, but now with a double-slit barrier switched on. Use $v_0 = 1\times10^{10}$ and the double-slit configuration from Problem 5, and make the initial state broader in the $y$-direction by setting $\sigma_y = 0.10$.

- Make a similar plot of the deviation of the total probability from 1.0 as a function of time.

```{note}
Keep in mind that how accurately you should expect the probability to be conserved will depend on what type of approach you have chosen for solving the matrix equation in Problem 3.
```


### Problem 8

Run your simulation with the following settings: $h = 0.005$, $\Delta t = 2.5\times10^{-5}$, $T = 0.002$, $x_c = 0.25$, $\sigma_x = 0.05$, $p_x = 200$, $y_c = 0.5$, $\sigma_y = 0.20$, $p_y = 0$ and $v_0 = 1\times10^{10}$. Use the double-slit configuration from Problem 5.


- Make three colourmap plots that illustrate the time evolution of the 2D probability function $p^n_{ij} = u^{n*}_{ij}\,u^n_{ij}$. Use the times $t = 0$, $t = 0.001$ and $t = 0.002$. (Feel free to make more plots if you want, but at least include these time steps.)

- For the same time steps, also make colourmap plots that show $\text{Re}(u_{ij})$ and $\text{Im}(u_{ij})$.

```{note}
When making the colourmap plots, it may be a good idea adjust the colour scale to the maximum of $p^n_{ij}$ at each time step independently. Then you avoid the problem that the shape of the probability function becomes difficult to see for time steps where it is very broad and flat.

You may also consider not using $p^n_{ij}$ as the $z$ axis (colour) value, but rather some tranformation of $p^n_{ij}$ like $\sqrt{p^n_{ij}}$, to more clearly see the structures in the low-probability regions. However, this comes with the cost that the plots become somewhat harder to interpret. But regardless of your choice, make sure to specify exactly what quantity the values on the colour scale represent.
```


### Problem 9

- Assume that we measure the particle with a detector screen at $x = 0.8$ (spanning the entire $y$ axis) at time $t = 0.002$. Using your simulation results from Problem 8, make a plot that shows the detection probability along this screen at this time. 

  Since we assume that we do indeed detect the particle *somewhere* along this line, you should normalise the one-dimensional probability function to sum to 1.0. Or in other words, you should plot $p(y\,|\,x=0.8\,;\,t=0.002)$, not $p(x,y\,;\,t=0.002)$ along $x=0.8$.

- Adjust your code to also simulate single-slit and triple-slit experiments. Like for the double-slit case, use slits with aperture 0.05 and use walls of $y$-length 0.05 to separate each pair of slits (in the triple-slit case). For each case, make a plot of the same 1D probability function as above, i.e. $p(y\,|\,x=0.8\,;\,t=0.002)$.


### Problem X

If you find it useful, feel free to make some animations of your simulation and put links to these in your report! (However, don't overdo it --- your report will be more readable if the reader doesn't have to switch between the report and watching animations all the time.)


--------


### Code snippets

Here's a python example demonstrating how you can use matplotlib to animate 2D colourmap plots:

```python
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


#
# Let's generate a dummy time series for a function z(x,y,t)
#

# Set up a 2D xy grid
h = 0.005
x_points = np.arange(0, 1+h, h)
y_points = np.arange(0, 1+h, h)
x, y = np.meshgrid(x_points, y_points, sparse=True)

# Array of time points
dt = 0.005
t_points = np.arange(0, 1+dt, dt)

# A function for a Gaussian that is travelling 
# in the x direction and broadening as time passes
def z(x,y,t):
    v = 0.5
    x_c = 0.2
    sigma_x = 0.025 + 0.15 * t
    return 1. / (2 * np.pi * np.sqrt(sigma_x)) * np.exp(-0.5 * (x - x_c - v * t)**2 / sigma_x**2)

# Fill z_data_list with f(x,y,t)
z_data_list = []
for t in t_points:
    z_data = z(x, y, t)
    z_data_list.append(z_data)


#
# Now the list z_data_list contains a series of "frames" of z(x,y,t), 
# where each frame can be plotted as a 2D image using imshow. Let's
# animate it!
#

# Some settings
fontsize = 12
t_min = t_points[0]
x_min, x_max = x_points[0], x_points[-1]
y_min, y_max = y_points[0], y_points[-1]

# Create figure
fig = plt.figure()
ax = plt.gca()

# Create a colour scale normalization according to the max z value in the first frame
norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(z_data_list[0]))

# Plot the first frame
img = ax.imshow(z_data_list[0], extent=[x_min,x_max,y_min,y_max], cmap=plt.get_cmap("viridis"), norm=norm)

# Axis labels
plt.xlabel("x", fontsize=fontsize)
plt.ylabel("y", fontsize=fontsize)
plt.xticks(fontsize=fontsize)
plt.yticks(fontsize=fontsize)

# Add a colourbar
cbar = fig.colorbar(img, ax=ax)
cbar.set_label("z(x,y,t)", fontsize=fontsize)
cbar.ax.tick_params(labelsize=fontsize)

# Add a text element showing the time
time_txt = plt.text(0.95, 0.95, "t = {:.3e}".format(t_min), color="white", 
                    horizontalalignment="right", verticalalignment="top", fontsize=fontsize)

# Function that takes care of updating the z data and other things for each frame
def animation(i):
    # Normalize the colour scale to the current frame?
    norm = matplotlib.cm.colors.Normalize(vmin=0.0, vmax=np.max(z_data_list[i]))
    img.set_norm(norm)

    # Update z data
    img.set_data(z_data_list[i])

    # Update the time label
    current_time = t_min + i * dt
    time_txt.set_text("t = {:.3e}".format(current_time))

    return img

# Use matplotlib.animation.FuncAnimation to put it all together
anim = FuncAnimation(fig, animation, interval=1, frames=np.arange(0, len(z_data_list), 2), repeat=False, blit=0)

# Run the animation!
plt.show()

# # Save the animation
# anim.save('./animation.mp4', writer="ffmpeg", bitrate=10000, fps=15)  # The fps (frames per second) sets the animation speed
```

