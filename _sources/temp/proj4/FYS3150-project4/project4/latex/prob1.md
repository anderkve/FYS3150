### 1

#### A)

| Spins in +1 | spin configuration                                           | $- J E(\vec{s}) = \sum\limits_{<k,l>}^Ns_ks_l$ | $M(\vec{s}) = \sum\limits_i^Ns_i$ | degeneracy |
| ----------- | ------------------------------------------------------------ | ---------------------------------------------- | --------------------------------- | ---------- |
| $4$         | $\begin{matrix} (1) & (1) \\1 & 1 & (1) \\ 1 & 1 & (1) \end{matrix}$ | $-J(2+2+2+2) = -8J$                            | $4$                               | $1$        |
| $3$         | $\begin{matrix} (1) & (1) \\1 & -1 & (1) \\ 1 & 1 & (1) \end{matrix}$ | $-J(0 -2 + 2 + 0) = 0$                         | $2$                               | $4$        |
| 2           | $\begin{matrix} (1) & (1) \\ -1 & -1 & (-1) \\ 1 & 1 & (1) \end{matrix}$ | $-J(0 + 0 + 0 + 0) = 0$                        | 0                                 | 4          |
| $2$         | $\begin{matrix} (-1) & (1) \\1 & -1 & (1) \\ -1 & 1 & (-1) \end{matrix}$ | $-J(-2-2-2-2)= 8J$                             | $0$                               | $2$        |
| $1$         | $\begin{matrix} (- 1) & (- 1) \\1 & - 1 & (1) \\ -1 & -1 & (-1) \end{matrix}$ | $-J(-2+0 + 0 + 2) = 0$                         | $-2$                              | $4$        |
| $0$         | $\begin{matrix} (-1) & (-1) \\ -1 & -1 & (-1) \\ -1 & -1 & (-1) \end{matrix}$ | $-J(2+2+2+2) = -8J$                            | $-4$                              | $1$        |

#### B)

$Z = \sum\limits_{\text{all possible} \vec{s}}e^{-\beta E(\vec{s})} = \sum\limits_{\text{all possible } \vec{s}}e^{\beta J \sum\limits_{<kl>}^Ns_ks_l}$



### 2

#### A)

Based on the table from 1A:

we have the possibilities: 2NJ, -2NJ, 0
$$
\Delta E
\begin{cases}
2NJ - 2NJ = 0 \\
2NJ - (- 2NJ) = 4NJ \\
2NJ - 0 = 2NJ \\
-2NJ - 2NJ = -4NJ \\
-2NJ - 0 = -2NJ \\
-2NJ + 2NJ = 0 \\
\end{cases}
$$
giving us the possibilities $4NJ, 2NJ, 0, -2NJ, -4NJ$



#### B)

make a lookup table for the 5 different values

### 3

Add an extra column mirroring the first one, and add one more element to each column, so we can mirror the first and last column, and the top and bottom row. Then iterate as normal, calculating $s_{i j}s_{i+1 j} + s_{ij}s_{i j+1}$ for each point