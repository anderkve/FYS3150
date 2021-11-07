from matplotlib import pyplot as plt
from scipy.stats import norm, uniform #, lognorm
import matplotlib.gridspec as gridspec
import numpy as np


# ---- Settings for example 1 ----

n_samples = 100 
plot_update_steps = 1
x_init = 12

# Define true distribution

mean1 = 15.0
sigma1 = 3.0
norm1 = norm(loc=mean1, scale=sigma1)

true_mean = mean1

def p(x):
  return norm1.pdf(x)


# ---- Settings for example 2 ----

# n_samples = 100 
# plot_update_steps = 1
# x_init = 35

# # Define true distribution

# mean1 = 15.0
# sigma1 = 3.0
# norm1 = norm(loc=mean1, scale=sigma1)

# true_mean = mean1

# def p(x):
#   return norm1.pdf(x)


# ---- Settings for example 3 ----

# n_samples = 5000
# plot_update_steps = 500
# x_init = 35

# # Define true distribution

# mean1 = 15.0
# sigma1 = 3.0
# norm1 = norm(loc=mean1, scale=sigma1)

# true_mean = mean1

# def p(x):
#   return norm1.pdf(x)


# ---- Settings for example 4 ----

# n_samples = 200
# plot_update_steps = 2
# x_init = 7  # 7.0

# # Define true distribution

# mean1 = 25.0  # 25.0
# sigma1 = 3.0
# norm1 = norm(loc=mean1, scale=sigma1)
# weight1 = 0.8

# mean2 = 8.0
# sigma2 = 1.0
# norm2 = norm(loc=mean2, scale=sigma2)
# weight2 = 1.0 - weight1

# true_mean = weight1 * mean1 + weight2 * mean2

# def p(x):
#   return weight1 * norm1.pdf(x) + weight2 * norm2.pdf(x)



# ---- Settings for example 5 ----

# n_samples = 20000 
# plot_update_steps = 2000
# x_init = 20

# # Define true distribution

# mean1 = 15.0
# sigma1 = 3.0
# norm1 = norm(loc=mean1, scale=sigma1)
# weight1 = 0.8

# mean2 = 8.0
# sigma2 = 1.0
# norm2 = norm(loc=mean2, scale=sigma2)
# weight2 = 1.0 - weight1

# true_mean = weight1 * mean1 + weight2 * mean2

# def p(x):
#   return weight1 * norm1.pdf(x) + weight2 * norm2.pdf(x)


# ---- Settings for example 6 ----

# n_samples = 200 
# plot_update_steps = 2
# x_init = 20

# # Define true distribution

# mean1 = 15.0
# sigma1 = 3.0
# norm1 = norm(loc=mean1, scale=sigma1)
# weight1 = 0.8

# mean2 = 8.0
# sigma2 = 1.0
# norm2 = norm(loc=mean2, scale=sigma2)
# weight2 = 1.0 - weight1

# true_mean = weight1 * mean1 + weight2 * mean2

# def p(x):
#   return weight1 * norm1.pdf(x) + weight2 * norm2.pdf(x)

# --------------------------- ----



# Define a derived quantity f(x)
def f(x):
  return (x-10.)*(x-18.) + -x*min((x-15),2.0)


# Define proposal functions
def generate_proposal(x_current):
  r = norm.rvs(0, 1.0)
  return x_current + r



# --------------------------------------------------


# Plot settings
x_plot_min = 0.0
x_plot_max = 50.0

y_plot_min = -0.05
y_plot_max = 0.3

n_bins = 100
bin_width = (x_plot_max - x_plot_min) / float(n_bins)
sample_weight = 1.0 / (n_samples * bin_width)

f_plot_min = -100 # 0.0  # f(x_plot_min)
f_plot_max = 300 # 100 # f(x_plot_max)
fy_plot_min = -0.005
fy_plot_max = 0.03

bin_width_f = (f_plot_max - f_plot_min) / float(n_bins)
sample_weight_f = 1.0 / (n_samples * bin_width_f)


# Evaluate true distribution
x_pts_pdf = np.linspace(x_plot_min, x_plot_max, 501)
y_pts_pdf = p(x_pts_pdf)


# Create figure
fig = plt.figure(figsize=(12.0, 12.0)) 
gs = gridspec.GridSpec(2, 1, height_ratios=[1,1], figure=fig)
ax1 = fig.add_subplot(gs[0])
ax2 = fig.add_subplot(gs[1])


#
# MCMC loop
#

x_samples = []

x_current = x_init
x_sum = 0.0
x_avg = 0.0

f_current = f(x_current)
f_sum = 0.0
f_avg = 0.0


hist, bin_edges = np.histogram([], bins=n_bins, range=(x_plot_min, x_plot_max))
hist = hist.astype(float)

hist_f, bin_edges_f = np.histogram([], bins=n_bins, range=(f_plot_min, f_plot_max))
hist_f = hist_f.astype(float)


for i in range(1,n_samples+1):

  # Print current results
  # print("samples: {:d},    x_current: {:.4f},    sample_avg: {:.4f},    sample_avg - true_mean: {:.4f}".format(i, x_current, x_avg, x_avg-true_mean))

  # Plot current state
  if (i % plot_update_steps == 0) or (i==1):

    plt.sca(ax1)
    plt.cla()
    plt.xlim([x_plot_min, x_plot_max])
    plt.ylim([y_plot_min, y_plot_max])

    plt.plot(x_pts_pdf, y_pts_pdf, color="black", label="true pdf", linewidth=2.0)

    # Histogram from scratch
    # plt.hist(x_samples, bins=n_bins, range=(x_plot_min,x_plot_max), density=True, alpha=1.0, color="orange")

    # Accumulated histogram
    plt.hist(bin_edges[:-1], bin_edges, weights=hist, alpha=0.8, color="orange")
    plt.hist(bin_edges[:-1], bin_edges, weights=hist, alpha=1.0, color="orange", histtype="step")

    plt.scatter(x_current, 0.0, s=50, c="red", edgecolor="0.1", zorder=5)

    plt.plot([true_mean, true_mean], [0.0, y_plot_max], linestyle="dashed", color="black", linewidth=1.5, label="true mean")
    plt.plot([x_avg, x_avg], [0.0, y_plot_max], linestyle="dashed", color="red", linewidth=1.5, label="sample avg")

    plt.title("samples: {:d},  sample_avg: {:.4f},  true_mean: {:.4f}".format(i, x_avg, true_mean))
    plt.xlabel("x")
    plt.ylabel("p(x), x sample count")

    plt.legend()


    plt.sca(ax2)
    plt.cla()
    plt.xlim([f_plot_min, f_plot_max])
    plt.ylim([fy_plot_min, fy_plot_max])
    plt.scatter(f_current, 0.0, s=50, c="blue", edgecolor="0.1", zorder=5)
    plt.plot([f_avg, f_avg], [0.0, y_plot_max], linestyle="dashed", color="blue", linewidth=1.5, label="sample avg")
    plt.hist(bin_edges_f[:-1], bin_edges_f, weights=hist_f, alpha=0.8, color="skyblue")
    plt.hist(bin_edges_f[:-1], bin_edges_f, weights=hist_f, alpha=1.0, color="skyblue", histtype="step")
    plt.xlabel("f(x)")
    plt.ylabel("f sample count")
    plt.legend()

    plt.pause(0.00001)


  # Propose new x
  x_proposal = generate_proposal(x_current)

  # Accept new x or keep current?
  accept_ratio = p(x_proposal) / p(x_current)  # Proposal prob not included as it is symmetric and cancels in ratio
  r = uniform.rvs() # sample number from uniform distribution between 0 and 1
  if r < accept_ratio:
    # Accept proposed point
    x_current = x_proposal

  # Save sample
  # x_samples.append(x_current)

  # Histogram sample
  hist_addition = np.histogram([x_current], bins=n_bins, range=(x_plot_min, x_plot_max), weights=[sample_weight])[0]
  hist += hist_addition

  # Update average
  x_sum += x_current
  x_avg = x_sum / i

  # Compute and histogram derived f sample
  f_current = f(x_current)
  f_sum += f_current
  f_avg = f_sum / i
  hist_f_addition = np.histogram([f_current], bins=n_bins, range=(f_plot_min, f_plot_max), weights=[sample_weight_f])[0]  
  hist_f += hist_f_addition

plt.show()

