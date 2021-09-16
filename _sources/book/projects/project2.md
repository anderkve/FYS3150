# Project 2

## Practicalities

- **Deadline**: Monday, September 27, 23:59.
- **Format:** 
  - A pdf document, typeset in LaTeX, with answers to all the problems below. You deliver the pdf on Canvas.
  - Code (with comments, of course) on a GitHub repo, with the repo link provided in the pdf documentet.
  - You *must* deliver via your group on Canvas (even if you are working alone).

- **Not a complete report:** For project 2 we do not require you to write a proper scientific report --- only a document with an answer for each problem. But the quality of the presentation still matters, of course. So pay attention to figures, figure captions, grammar, etc.

- **Collaboration:** We *strongly* encourage you to collaborate with others, in groups up to four students. The group hands in a single pdf. Remember to list everyone's name in the pdf.

- **Reproducibility:** Your code should be available on a GitHub repo. You can refer to relevant parts of your code in your answers. Make sure to include a README file in the repo that briefly explains how the code is organized, and how it should be compiled and run in order to reproduce your results.

- **Figures:** Figures included in your LaTeX document should be made as vector graphics (e.g. `.pdf` files), rather than raster graphics (e.g. `.png` files). If you are making plots with `matplotlib.pyplot` in Python, this is as simple as calling `plt.savefig("figure.pdf")` rather than `plt.savefig("figure.png")`.

- **We recommend using Armadillo:** For this project we recommend using Armadillo to work with matrices and vectors.


## Introduction

The main topics of this project are 

- scaling of equations
- eigenvalue problems
- code testing (*unit testing*).

Our example of an eigenvalue problem is a special case of a one-dimensional buckling beam. Consider the following situation:

- A horizontal beam of length $L$.
- We let $u(x)$ be the vertical displacement of the beam at horizontal position $x$, with $x \in [0,L]$.
- A force $F$ is applied at the endpoint ($x=L$), *directed into the beam*, i.e. towards $x=0$. 
- The beam is fastened with *pin endpoints*, meaning that $u(0)=0$ and $u(L)=0$, but the endpoints are allowed to rotate ($u'(x) \neq 0$).
- We are *not* studying a time-dependent system here -- we are simply interested in the different static shapes the beam can take due to the applied force.

We can then describe this situation with the second-order differential equation

$$ 
\gamma \frac{d^2 u(x)}{dx^2} = - F u(x),
$$ (bb_eq_1)

where $\gamma$ is some constant defined by material properties like rigidity. However, the equation we will actually be working with is the scaled equation

$$ 
\frac{d^2 u(\hat{x})}{d\hat{x}^2} = - \lambda u(\hat{x}),
$$ (bb_eq_2)

where $\hat{x} \equiv x/L$ is a dimensionless (unitless) varible, $\hat{x} \in [0,1]$, and $\lambda = \frac{F L^2}{\gamma}$. (See problem 1.)

----
**Discretization:** We discretize this by dividing our $\hat{x}$ range into $n$ parts, i.e. we will have $n+1$ points $\hat{x}_0$, $\hat{x}_1$, $\ldots$, $\hat{x}_{n-1}$, $\hat{x}_{n}$. Thus we have a stepsize 

$$
h = \frac{\hat{x}_{\text{max}} - \hat{x}_{\text{min}}}{n} = \frac{1 - 0}{n} = \frac{1}{n}
$$

and our $\hat{x}_i$ points are given by 

$$
\hat{x}_i = \hat{x}_0 + ih, \quad i=0,1,\ldots,n.
$$

From this dicretization we get the following set of equations for $v_i$ (our approximations to the exact $u_i$):

$$
\frac{-v_{i+1} + 2v_i -v_{i-1}}{h^2} = \lambda v_i.
$$

By inserting the boundary conditions $v_0=0$ and $v_n=0$ we can write this as the linear algebra eigenvalue problem 

$$
\mathbf{A} \vec{v} = \lambda \vec{v}
$$ (bb_eq_3)

where 
- the elements of the vector $\vec{v}$ are $\vec{v} = [v_1, \ldots, v_{n-1}]$; and 
- $\mathbf{A}$ is tridiag($a$, $d$, $a$), with 
  - $a = -1/h^2$
  - $d = 2/h^2$ 
- *Note:* In contrast to project 1, we here keep the factor $1/h^2$ as part of the definition of $\mathbf{A}$.

To solve this matrix equation means finding the pairs of eigenvalues and eigenvectors, ($\lambda^{(i)}, \vec{v}^{(i)}$), that satify Eq. {eq}`bb_eq_3`. These eigenvectors are then our discretized approximations to the true *eigenfunctions* $u^{(i)}(\hat{x})$ that are the solutions of the differential equation in Eq. {eq}`bb_eq_2`.

-----

**Notation:** We will use $N$ to denote the size of the matrix, so that $\mathbf{A}$ is an $N \times N$ matrix, and $\vec{v}$ a column vector of length $N$. Make sure not to confuse $N$ with the number of *steps* in our discretization of $\hat{x}$ ($n$ steps), or the number of $\hat{x}_i$ points ($n+1$ points). They are related as $N = n-1$.

-----
**Analytical solutions:** For a given matrix size $N \times N$, the eigenvalue problem in Eq. {eq}`bb_eq_3` with the tridiagonal matrix $\mathbf{A} = \text{tridiag}(a,d,a)$ has the following set of analytical eigenvalues and eigenvectors:

$$
\lambda^{(i)} = d + 2 a \cos\left(\frac{i \pi}{N+1}\right), \quad i = 1,\ldots,N
$$

$$
\vec{v}^{(i)} = \left[\sin\left(\frac{i \pi}{N+1}\right), \sin\left(\frac{2 i \pi}{N+1}\right), \ldots, \sin\left(\frac{N i \pi}{N+1}\right)\right]^T,\quad i = 1,\ldots,N
$$

----
**Scaling of eigenvectors:** Remember that if $\vec{v}$ is an eigenvector of $\mathbf{A} \vec{v} = \lambda \vec{v}$, then a scaled vector $c \vec{v}$ (where $c$ is some constant) is an equally good eigenvector. When presenting your results, and when comparing to results from Armadillo, it will be useful to scale each eigenvector to have unit norm (i.e. vector length 1). You can do this easily using the Armadillo function `arma::normalise` described [here](http://arma.sourceforge.net/docs.html#normalise).


## Problems

### Problem 1
With the definition $\hat{x} \equiv x/L$, show that Eq. {eq}`bb_eq_1` can be written as Eq. {eq}`bb_eq_2`.


### Problem 2
Jacobi's rotation algorithm is based on an important property of orthogonal transformations that we will show here. Assume that 

- $\vec{v}_i$ is a set of *orthonormal* basis vectors, i.e. that $\vec{v}_i^T \cdot \vec{v}_j = \delta_{ij}$.
- $\mathbf{U}$ is an *orthogonal* transformation matrix, i.e. that $\mathbf{U}^T = \mathbf{U}^{-1}$.

Show that transformations with $\mathbf{U}$ preserves orthonormality, i.e. show that the set of vectors $\vec{w}_i = \mathbf{U} \vec{v}_i$ is also an orthonormal set.


### Problem 3
Before we get started with implementing the Jacobi rotation algorithm, let's make sure that we can set up the tridiagonal matrix $\mathbf{A}$ correctly. So, write a short program that:

- sets up the tridiagonal $\mathbf{A}$ for $N=6$;
- solves $\mathbf{A} \vec{v} = \lambda \vec{v}$ using Armadillo's `arma::eig_sym`, described [here](http://arma.sourceforge.net/docs.html#eig_sym);
- checks that the eigenvalues and eigenvectors from Armadillo agrees with the analytical result for $N=6$. (Remember scaling of eigenvectors, as discussed above.)


### Problem 4
An important part of the Jacobi algorithm is to have a function that can identify the largest (in absolute value) off-diagonal element of a matrix. Here we specialize to the case of a *symmetric* matrix. 

**a)** Write a C++ function that can identify the largest off-diagonal element of a matrix. A suggestion is to write a function that 

- has return type `double`
- takes an Armadillo matrix as input
- takes *references* to two integers as input
- identifies the largest off-diagonal element in the matrix (under the assumption of a symmetric matrix)
- writes the matrix indices for this element to the two integer elements
- returns the value of this matrix element

A simple function signature could then be 

```c
double max_offdiag_symmetric(arma::mat A, int& k, int &l),
```

Or, to avoid copying the (potentially large) matrix A every time we run the function, we could simply pass in a reference to A. Since the function `max_offdiag_symmetric` won't be modifying the matrix in any way, we should make this explicit by using a `const` reference, like this:

```c
double max_offdiag_symmetric(const arma::mat& A, int& k, int &l)
```

**b)** Write a small test code that tests the above function using the matrix

$$
A = 
\begin{bmatrix}
1 & 0 & 0 & 0.5\\
0 & 1 & -0.7 & 0\\
0 & -0.7 & 1 & 0\\
0.5 & 0 & 0 & 1
\end{bmatrix}
$$



### Problem 5
**a)** Write a code implementation of Jacobi's rotation algorithm for solving Eq. {eq}`bb_eq_3`. See the code snippets at the end of this page for a suggested code structure.

**b)** Let $\mathbf{A}$ be of size $6 \times 6$. Test your code by checking that the eigenvalues and eigenvectors you get agree with the analytical results for $N=6$.


### Problem 6
Now let's look at how many similarity transformations we need before we reach a result where all non-diagonal matrix elements are close to zero. 

**a)** Try to estimate how the number of required transformations scale with the matrix size $N$ for your code when solving Eq. {eq}`bb_eq_3`. Present your scaling data either in a table or a plot (or both).

**b)** What scaling behaviour would you expect to see if $\mathbf{A}$ was a dense matrix?


### Problem 7
**a)** For a discretization of $\hat{x}$ with $n=10$ steps, solve Eq. {eq}`bb_eq_3` using your Jacobi code and make a plot of the three eigenvectors corresponding to the three lowest eigenvalues. The plot should show vector elements $v_i$ against the corresponding positions $\hat{x}_i$. 

Since we are effectively showing the solutions to a differential equation, your plot should also include the boundary points $(\hat{x}_0, v_0)$ and $(\hat{x}_n, v_n)$.

Plot the corresponding analytical eigenvectors (extended with the boundary points) in the same plot.

**b)** Make the same plot for discretization of $\hat{x}$ with $n=100$ steps.


### Problem 8 (if you have time)

*Will add a bonus challenge here*







## Code snippets

*We will add code examples here shortly*
