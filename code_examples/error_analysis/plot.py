import numpy as np
import matplotlib.pyplot as plt

#
# Read data into numpy arrays
#

h, d2u_approx, d2u_exact = np.loadtxt("output.txt", usecols=(0,1,2), unpack=True)

# Compute numpy arrays with the absolute error, relative error and log10(relative error)
abs_err = np.absolute(d2u_approx - d2u_exact)
rel_err = np.absolute(abs_err / d2u_exact)
log10_rel_err = np.log10(rel_err)

# Array with log10(h)
log10_h = np.log10(h)



#
# Make plots
#

# Common title string
exact_result = d2u_exact[0]
common_title_string = "for approximation of\n u''(x=2) = 4*exp(2*2) = {:.8e}".format(exact_result)

# Figure size (inches)
figwidth = 5.5
figheight = figwidth / 1.33333

# Plot absolute error
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("log10(h)")
plt.savefig("abs_err.pdf")

# Plot relative error
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, rel_err, '.', c="black", markersize=10)
plt.title("Relative error " + common_title_string, fontsize=10)
plt.ylabel("relative error")
plt.xlabel("log10(h)")
plt.savefig("rel_err.pdf")

# Plot log10(relative error)
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, log10_rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, log10_rel_err, '.', c="black", markersize=10)
plt.title("Log10(relative error) " + common_title_string, fontsize=10)
plt.ylabel("log10(relative error)")
plt.xlabel("log10(h)")
plt.savefig("log10_rel_err.pdf")

# Alternative way of making log-log plot for relative error
plt.figure(figsize=(figwidth, figheight))
plt.plot(h, rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(h, rel_err, '.', c="black", markersize=10)
plt.title("Relative error " + common_title_string, fontsize=10)
plt.ylabel("relative error")
plt.xlabel("h")
plt.xscale("log")
plt.yscale("log")
plt.savefig("log10_rel_err_v2.pdf")

