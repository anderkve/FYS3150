# Project 3


## Introduction

In this project, you'll study the effects of a device used to trap charged particles. This device is known as a **Penning trap** and utilizes an electromagnetic field to trap the particles. In particular, CERN uses such a trap to trap anti-hydrogen to study the properties of the most basic anti-matter.

## Reminder on electrodynamics and classical mechanics

We'll provide a brief reminder on the necessary electrodynamics you need to understand the context and to set up proper mathematical formulations.

For simplicity, we'll assume that the charge $q$ of any particle is always positive in project, i.e $q > 0$.

The **electric field** $\mathbf{E}$ is related to the **electric potential** through the equation

$$
\mathbf{E} = -\nabla V,
$$ (e_field_pot)

where $\nabla$ denotes the gradient operator.

The electric field at a point $\mathbf{r}$ set up by point charges $\{q_1, ..., q_n\}$ distributed at points $\{\mathbf{r}_1, ..., \mathbf{r}_n\}$ is

$$
\mathbf{E} = \frac{1}{4\pi \epsilon_0}\sum_{j=1}^n q_j \frac{\mathbf{r}-\mathbf{r}_j}{|\mathbf{r}-\mathbf{r}_j|^3}
$$ (e_field_point_q)

The force $\mathbf{F}$ on a particle with charge $q$ from an external electric field $\mathbf{E}$ and magnetic field $\mathbf{B}$, known as the **Lorentz force**, is given by

$$
\mathbf{F} = q\mathbf{E} + q\mathbf{v}\times \mathbf{B},
$$ (lorentz_force)

where $\mathbf{v}$ is the velocity of the particle.

Finally, the time evolution of a particle is governed by Newton's second law given by

$$
m\ddot{\mathbf{r}} = \sum_i \mathbf{F}_i,
$$ (n2l)

where $m$ denotes the mass of the particle and $\ddot{\mathbf{r}} \equiv d^2\mathbf{r}/dt^2$.

## The Penning Trap

The Penning trap is built up by an electromagnetic field. The electric field part is defined by the electric potential

$$
V(x, y, z) = \frac{V_0}{2d^2}(2z^2 - x^2 - y^2),
$$ (penning_potential)

where $d$ defines a geometric constraint on the physical apparatus and $V_0$ is a physical parameter.

The electric field traps the particle in the $z$-direction, but the particle can still escape in the radial direction. Therefore,
in addition, a homogeneous magnetic field is imposed along the $z$-axis of the apparatus, i.e

$$
\mathbf{B} = B_0\hat{e}_z = (0, 0, B_0),
$$ (b_field)

where $B_0$ is a parameter. The magnetic field ensures entrapment in the radial direction.

## Problems

### The analytical part

For now, assume that we're dealing with a single particle with charge $q$ and mass $m$.

#### Problem 1

Derive the equations of motion and show that they can be written as

$$
\ddot{x} - \omega_0 \dot{y} - \frac{1}{2}\omega_z^2 x = 0,
$$ (x_eq)

$$
\ddot{y} + \omega_0 \dot{x} - \frac{1}{2}\omega_z^2 y = 0,
$$ (y_eq)

$$
\ddot{z} + \omega_z^2 z = 0.
$$ (z_eq)

where $\omega_0 \equiv qB_0/m$ and $\omega_z^2 = 2qV_0/(md^2)$.
Write down the general solution for equation {eq}`z_eq`.

#### Problem 2

Eqs. {eq}`x_eq` and {eq}`y_eq` introduces a challenge because the two equations are coupled.

Introduce a complex function $f(t) = x(t) + iy(t)$ and show that eqs. {eq}`x_eq` and {eq}`y_eq`
can be rewritten to a single differential equation for $f$ as

$$
\ddot{f} + i\omega_0 \dot{f} - \frac{\omega_z^2}{2}f = 0.
$$ (f_eq)

*Hint: Add the two equations and multiply one of them with the complex number $i$*.

#### Problem 3

Show that the general solution of eq. {eq}`f_eq` is

$$
f(t) = A_+ e^{-i\omega_+ t} + A_- e^{-i\omega_- t},
$$ (f_general_sol)

by assuming that $f \propto e^{-i\omega t}$.

Derive a necessary condition on $\omega_0$ and $\omega_z$ to obtain a bounded solution (i.e the particle becomes trapped inside the apparatus).

*Hint: The condition should be a consequence of the solutions $\omega_\pm$.*

#### Problem 4

Derive the general solutions $x(t)$ and $y(t)$ from eq. {eq}`f_general_sol`.

#### Problem 5
Show that the upper-bound and lower-bound on the distance of the particle from the origin in the $xy$-plane is given by

$$
R_+ = A_+ + A_- \quad \text{and} \quad R_- = |A_+ - A_-|,
$$
respectively.

#### Problem 6

To measure the validity of your code, you'll need an actual special solution you can use for comparison.

Assume we have a single charged particle with charge $q$ and mass $m$ in the Penning trap with the following
initial conditions:

$$
x(0) = x_0, \qquad \dot{x}(0) = 0,
$$

$$
y(0) = 0, \qquad \dot{y}(0) = v_0,
$$

$$
z(0) = z_0, \qquad \dot{z}(0) = 0.
$$


Find the special solution of $z(t)$. Show that

$$
A_+ = \frac{v_0 + \omega_- x_0}{\omega_- - \omega_+}, \qquad A_- = - \frac{v_0 + \omega_+ x_0}{\omega_- - \omega_+}.
$$


#### Problem 7
So far, we haven't considered more than a single particle in the trap. Consider a set of $n$ particles with charges $\{q_1, ..., q_n\}$
and masses $\{m_1, ..., m_n\}$. Derive a set of equations that accounts for *both* the force due to the external field set up
by the apparatus and the force due to the electric force among the charges themselves.


### Code development

In this part, you'll develop a code to simulate a set of $n$ particles with charges $\{q_1, ..., q_n\}$ and masses $\{m_1, ..., m_n\}$.
You are **expected** to write an **object-oriented** code in this project. Not doing so will severely reduce the points given for the code.
Don't worry, though. We'll help you to think about *how* you should structure and come with suggestions.
Also, once you write the parts we suggest below as object-oriented, you can write anything else using functions.
It's not necessarily a good idea to object-orient *everything*.

#### Problem 8

Create a class named `Particle` that should at least store the following properties of a single particle:
  - Charge
  - Mass
  - Position
  - Velocity

You are of course free to store add any attribute you need.

Some helpful advice:
  - The constructor should assign the attributes to member variables.
  - The constructor should initialize an `arma::vec` object for position and velocity.
  - To begin with, make all its attributes public. This makes it easier to use it together with other classes.

#### Problem 9

Create class named `PenningTrap` that should at least contain following attributes:
  - An `std::vector` containing multiple `Particle` objects. You can declare the object in the following way:

        ```c++
        std::vector<Particle> particles_; //std::vector who's elements are Particle objects.
        ```

  - An `arma::cube` storing the position of each particle at all time steps.
  - An `arma::cube` storing the velocity of each particle at all time steps.


Again, you are free to add any attribute you need.

For now, the `PenningTrap` class should contain methods (i.e member functions) for the following:
  - The electric and magnetic force due to the external fields from the physical apparatus.
  - The force due to the interaction among the particles (**wait with this part until you've checked your code without the interactions**).


#### Problem 10

Write a function or set of functions that implements Runge-Kutta 4. It should utilize your classes `PenningTrap` and `Particle` to
solve the equations of motion.

You may also object-orient this part, but it's not necessary.


#### Problem 11

It's time to test your code and check that it does what it's supposed to. You should *at least* do the following:

  - Create a plot of the particles motion in $xy$-plane with and without interactions. Make sure to use the same initial conditions in the two cases.
  - Create a 3D plot of the trajectory of two particles with and without interactions. Make sure to use the same initial conditions in the two cases.
  - Compute a *heatmap* of the maximum relative error as a function of $t$ and step size $h$ using the special solution derived earlier.
  - Compute the convergence rate of Runge-Kutta 4 using the formula

    $$
    r = \frac{1}{N}\sum_{i=1}^N\frac{\log (E_{i}/E_{i-1})}{\log (h_{i}/h_{i-1}) }.
    $$

  where $E_i = (\sum_{j=1}^N |y_j - \hat{y}_j|^p )^{1/p}$ is the $L^p$-norm for simulation $i$ with step size $h_i$.

   Here $y_j$ represents the analytical result at a time $t_j$ and $\hat{y}_j$ represents the numerical approximation. $p = 2$ is typically chosen. Another convenient choice is the $L^\infty$-norm given by $E_i = \max_j |y_j - \hat{y}_j|$,
  which you can deduce by computing $\lim_{p\to \infty}E_i$. You are free to use either of the two.

  You can think of the $L^p$-norm as a measure of the distance between the analytical solution and the numerical approximation at a finite set of times $t_j$.


#### Problem 12
From the perspective of an experimental physicist, it's natural to ask whether the entrapment of the particle
can sustain for a long enough period that actual measurements can be made. Therefore:

  - Measure how long you can keep a set of $n$ particles trapped as a function of $\omega_0$ and $\omega_z$.
  - For a specific choice of $\omega_z$ and $\omega_0$, measure how long you can trap a set of particles as a function of number of particles $n$.
