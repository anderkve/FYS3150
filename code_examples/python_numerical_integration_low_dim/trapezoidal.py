import numpy as np
import matplotlib.pyplot as plt


#
# Integrand function
#

def f(x):
    return np.exp(x)


#
# Main script
#

x_min = 0.0
x_max = 2.0

eps = 1.0e-8


# Compute T_1
x_vals = np.array([x_min, x_max])
h = x_vals[1] - x_vals[0]
T_1 = 0.5 * h * np.sum(f(x_vals))

# Compute T_2
x_vals = np.linspace(x_min, x_max, 3)
h = x_vals[1] - x_vals[0]
x_vals_new = x_vals[1:-1:2]
T_2 = 0.5 * T_1 + h * np.sum(f(x_vals_new))

# Relative difference
rel_diff = np.abs((T_2 - T_1) / T_1)
print(f"rel_diff: {rel_diff:.10e}")

# Run while loop
j = 2
T_j = T_2
while rel_diff > eps:

    # Compute T_{j+1}
    x_vals = np.linspace(x_min, x_max, 2*j + 1)
    h = x_vals[1] - x_vals[0]
    x_vals_new = x_vals[1:-1:2]
    T_jp1 = 0.5 * T_j + h * np.sum(f(x_vals_new))

    # Relative difference
    rel_diff = np.abs((T_jp1 - T_j) / T_j)

    # Some output
    print()
    print(f"j:        {j}")
    print(f"T_jp1:    {T_jp1:.10e}")
    print(f"T_j:      {T_j:.10e}")
    print(f"rel_diff: {rel_diff:.10e}")

    # Update variables for next iteration
    j += 1
    T_j = T_jp1


# We're done
print()
print("Done!")
print()
print(f"Numerical:  {T_j:.10e}")

ana = np.exp(x_max) - np.exp(x_min)
print(f"Analytical: {ana:.10e}")
print()


x_vals_plot = np.linspace(x_min, x_max, 101)
f_vals = f(x_vals_plot)

plt.plot(x_vals_plot, f_vals)
plt.xlim([x_min, x_max])
plt.ylim([0.0, 10.0])
plt.show()

