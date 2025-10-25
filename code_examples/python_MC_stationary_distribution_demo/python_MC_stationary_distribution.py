import numpy as np

# Markov chain example: A random walk on the cycle of integers 1 to 6.
# The matrix A is the transition matrix and the example shows how 
# repeated multiplication of the tranistion matrix gives a limiting 
# matrix A^infty that contains the stationary distribution on each row, 
# *if* the chain is not cyclic.


# Example 1: The limiting matrix A^infty should
# have the stationary distribution 
# A = np.array([
#   [0.50, 0.25, 0.00, 0.00, 0.00, 0.25],
#   [0.25, 0.50, 0.25, 0.00, 0.00, 0.00],
#   [0.00, 0.25, 0.50, 0.25, 0.00, 0.00],
#   [0.00, 0.00, 0.25, 0.50, 0.25, 0.00],
#   [0.00, 0.00, 0.00, 0.25, 0.50, 0.25],
#   [0.25, 0.00, 0.00, 0.00, 0.25, 0.50],
# ])

# Example 2: This chain has a deterministic switching between even and odd numbers, 
# (it's periodic in a sense) so we don't simply get the stationary on each row of 
# the limiting matrix A^infty
A = np.array([
  [0.00, 0.50, 0.00, 0.00, 0.00, 0.50],
  [0.50, 0.00, 0.50, 0.00, 0.00, 0.00],
  [0.00, 0.50, 0.00, 0.50, 0.00, 0.00],
  [0.00, 0.00, 0.50, 0.00, 0.50, 0.00],
  [0.00, 0.00, 0.00, 0.50, 0.00, 0.50],
  [0.50, 0.00, 0.00, 0.00, 0.50, 0.00],
])


print()
print("Transition matrix A:")
print(A)
print()
print("------------------")
print()

A_pow_ip1 = A
for i in range(1,100):

    print(f"Matrix multiplication: A^{i} * A = A^{i+1}")
    A_pow_ip1 = np.matmul(A_pow_ip1, A)
    print(f"Matrix A^{i+1}:")
    print(A_pow_ip1)
    print()
