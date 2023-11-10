import numpy as np
import matplotlib.pyplot as plt
import sys
from scipy.integrate import quad


#
# Integrand function
#

def f(x):
    return 2.0 + np.sin(1.5 * np.pi * x**4) + x



#
# Main script
#

x_min = 0.0
x_max = 1.5
eps = 1e-2


counter = 0
# Keep track of evaluation points, for illustration
x_vals = [x_min, x_max]

# Recursive integration function
def recursive_integrate(x_min, x_max, eps):

    global x_vals
    global counter
    counter += 1

    print()
    print("counter:", counter)
    print(f"Integrate:   x_min: {x_min:.6e},  x_max: {x_max:.6e}")

    # Compute T1
    h = x_max - x_min
    T_1 = 0.5 * h * (f(x_min) + f(x_max))

    # Compute T2
    h = 0.5 * h
    x_mid = x_min + h
    T_2 = 0.5* T_1 + h * f(x_mid)

    # Relative difference
    rel_diff = np.abs((T_2 - T_1) / (T_1 + 0.001 * eps))

    # Some output
    print(f"T_1:      {T_1:.10e}")
    print(f"T_2:      {T_2:.10e}")
    print(f"rel_diff: {rel_diff:.10e}")

    # Store points, only for illustration
    x_vals.append(x_mid)

    # Should I stay or should I go?
    if rel_diff < eps:
        print("Done with this part.")
        return (4. / 3.) * T_2 - (1. / 3.) * T_1  # Simpson's rule
    else:
        print("Split this part.")
        return recursive_integrate(x_min, x_mid, eps) + recursive_integrate(x_mid, x_max, eps)



# 
# Output and plot
# 

result = recursive_integrate(x_min, x_max, eps)
print("Done!")

print()
print(f"Our result:  {result:.10e}")

scipy_result = quad(f, x_min, x_max)[0]
print(f"Scipy quad:  {scipy_result:.10e}")


# Illustrate which x points we've used by marking 
# them on a plot of the integrand function
x_vals = np.array(x_vals)
f_vals = f(x_vals)

z = np.argsort(x_vals)
x_vals = x_vals[z]
f_vals = f_vals[z]

x_vals_plot = np.linspace(x_min, x_max, 1001)
f_vals_plot = f(x_vals_plot)

plt.plot(x_vals_plot, f_vals_plot, '-')
plt.plot(x_vals, f_vals, '.')

plt.show()
