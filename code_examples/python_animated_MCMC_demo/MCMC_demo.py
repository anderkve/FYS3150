from matplotlib import pyplot as plt
from scipy.stats import norm, uniform #, lognorm
import matplotlib.gridspec as gridspec
from matplotlib.animation import FuncAnimation
import numpy as np


# ---- Settings for example 1 ----

# n_samples = 100
# plot_update_steps = 1
# x_init = 12

# # Define true distribution

# mean1 = 15.0
# sigma1 = 3.0
# norm1 = norm(loc=mean1, scale=sigma1)

# true_mean = mean1

# def p(x):
#   return norm1.pdf(x)


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

# n_samples = 2000
# plot_update_steps = 20
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
# plot_update_steps = 200
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

# NOTE: Change the line "accept_ratio = p(x_proposal) / p(x_current)" 
# towards the end of the script to "accept_ratio = 1.0"

n_samples = 200 
plot_update_steps = 2
x_init = 20

# Define true distribution

mean1 = 15.0
sigma1 = 3.0
norm1 = norm(loc=mean1, scale=sigma1)
weight1 = 0.8

mean2 = 8.0
sigma2 = 1.0
norm2 = norm(loc=mean2, scale=sigma2)
weight2 = 1.0 - weight1

true_mean = weight1 * mean1 + weight2 * mean2

def p(x):
  return weight1 * norm1.pdf(x) + weight2 * norm2.pdf(x)

# --------------------------- ----


#
# Define a derived quantity f(x)
#

def f(x):
  return (x-10.)*(x-18.) + -x*min((x-15),2.0)



#
# Do the MCMC 
#

# Define proposal functions
def generate_proposal(x_current):
  r = norm.rvs(0, 1.0)
  return x_current + r

x_samples = []
f_samples = []

x_current = x_init
x_sum = 0.0
x_avg = 0.0
x_avgs = []

f_current = f(x_current)
f_sum = 0.0
f_avg = 0.0
f_avgs = []

# Run MCMC loop
for i in range(1,n_samples+1):

  # Propose new x
  x_proposal = generate_proposal(x_current)

  # Accept new x or keep current?
  # accept_ratio = p(x_proposal) / p(x_current)  # Proposal prob not included as it is symmetric and cancels in ratio
  accept_ratio = 1.0  # To demonstrate why the acceptance rule is important...

  r = uniform.rvs() # sample number from uniform distribution between 0 and 1
  if r < accept_ratio:
    # Accept proposed point
    x_current = x_proposal

  # Save x sample
  x_samples.append(x_current)

  # Compute new x average and save average at this step
  x_sum += x_current
  x_avg = x_sum / i
  x_avgs.append(x_avg)

  # Compute f and save f sample
  f_current = f(x_current)
  f_samples.append(f_current)

  # Compute new f average and save average at this step
  f_sum += f_current
  f_avg = f_sum / i
  f_avgs.append(f_avg)



#
# Plot settings
#

x_plot_min = 0.0
x_plot_max = 50.0

y_plot_min = -0.05
y_plot_max = 0.3

n_bins = 100

hist_bins = np.linspace(x_plot_min, x_plot_max, n_bins+1)
bin_width = hist_bins[1] - hist_bins[0]
sample_weight = 1.0 / (n_samples * bin_width)


f_plot_min = -100
f_plot_max = 300
fy_plot_min = -0.005
fy_plot_max = 0.03

hist_bins_f = np.linspace(f_plot_min, f_plot_max, n_bins+1)
bin_width_f = hist_bins_f[1] - hist_bins_f[0]
sample_weight_f = 1.0 / (n_samples * bin_width_f)


#
# Evaluate true distribution
#

x_pts_pdf = np.linspace(x_plot_min, x_plot_max, 501)
y_pts_pdf = p(x_pts_pdf)



#
# Prepare figure with two panels 
#

fig = plt.figure(figsize=(12.0, 12.0)) 
gs = gridspec.GridSpec(2, 1, height_ratios=[1,1], figure=fig)
ax1 = fig.add_subplot(gs[0])
ax2 = fig.add_subplot(gs[1])

# Add some lines at y=0 in both plots
ax1.plot([x_plot_min, x_plot_max], [0.0, 0.0], linestyle="solid", color="0.8", linewidth=1.5)
ax2.plot([f_plot_min, f_plot_max], [0.0, 0.0], linestyle="solid", color="0.8", linewidth=1.5)


# True pdf p(x)
ax1.plot(x_pts_pdf, y_pts_pdf, color="black", label="true pdf", linewidth=2.0)

# Scatter marker, x
x_scat = ax1.scatter([], [], s=50, c="red", edgecolor="0.1", zorder=5)

# Histogram, x
_, _, x_bar_container = ax1.hist([], hist_bins, alpha=1.0, color="orange")

# True mean, x
ax1.plot([true_mean, true_mean], [0.0, y_plot_max], linestyle="dashed", color="black", linewidth=1.5, label="true mean")

# Sample average, x
x_avg_ln, = ax1.plot([], [], linestyle="dashed", color="red", linewidth=1.5, label="sample avg")

# Samples text, x
x_samples_text = ax1.text(x_plot_min + 0.02 * (x_plot_max - x_plot_min), 
                          y_plot_min + 0.96 * (y_plot_max - y_plot_min), 
                          "samples: {} \nsample average: {:.5e}".format(0,0), 
                          horizontalalignment="left",
                          verticalalignment="top")


ax1.set_xlim(x_plot_min, x_plot_max)
ax1.set_ylim(y_plot_min, y_plot_max)
ax1.legend()

# plt.title("samples: {:d},  sample_avg: {:.4f},  true_mean: {:.4f}".format(i, x_avg, true_mean))
ax1.set_xlabel("x")
ax1.set_ylabel("p(x), normalised sample count")


# Scatter marker, f
f_scat = ax2.scatter([], [], s=50, c="blue", edgecolor="0.1", zorder=5)

# Histogram, f
_, _, f_bar_container = ax2.hist([], hist_bins_f, alpha=1.0, color="skyblue")

# Sample average, f
f_avg_ln, = ax2.plot([], [], linestyle="dashed", color="blue", linewidth=1.5, label="sample avg")

# Samples text, f
f_samples_text = ax2.text(f_plot_min + 0.02 * (f_plot_max - f_plot_min), 
                          fy_plot_min + 0.96 * (fy_plot_max - fy_plot_min), 
                          "samples: {} \nsample average: {:.5e}".format(0,0), 
                          horizontalalignment="left",
                          verticalalignment="top")

ax2.set_xlim(f_plot_min, f_plot_max)
ax2.set_ylim(fy_plot_min, fy_plot_max)
ax2.legend()

ax2.set_xlabel("f(x)")
ax2.set_ylabel("normalised sample count")



#
# Make animation
#

def prepare_animation(x_bar_container, x_scat, x_avg_ln, x_samples_text,
                      f_bar_container, f_scat, f_avg_ln, f_samples_text):

  def animate(frame_index):

    # x histogram
    x_data = np.array(x_samples[:frame_index+1])
    nx, _ = np.histogram(x_data, hist_bins)

    for count, rect in zip(nx, x_bar_container.patches):
      rect.set_height(count * sample_weight)

    # x scatter
    current_x = x_samples[frame_index]    
    x_scat.set_offsets(np.c_[[current_x], [0.0]])

    # x avgerage
    x_avg_ln.set_data([x_avgs[frame_index], x_avgs[frame_index]], [0.0, y_plot_max])

    # x samples text
    x_samples_text.set_text("samples: {} \nsample average: {:.5e}".format(frame_index+1, x_avgs[frame_index])) 


    # f histogram
    f_data = np.array(f_samples[:frame_index+1])
    nf, _ = np.histogram(f_data, hist_bins_f)

    for count, rect in zip(nf, f_bar_container.patches):
      rect.set_height(count * sample_weight_f)

    # f scatter
    current_f = f_samples[frame_index]    
    f_scat.set_offsets(np.c_[[current_f], [0.0]])

    # f average
    f_avg_ln.set_data([f_avgs[frame_index], f_avgs[frame_index]], [0.0, fy_plot_max])

    # f samples text
    f_samples_text.set_text("samples: {} \nsample average: {:.5e}".format(frame_index+1, f_avgs[frame_index])) 


    return x_bar_container.patches, x_scat, x_avg_ln, x_samples_text, f_bar_container, f_scat, f_avg_ln, f_samples_text

  return animate


frame_indices = list(x-1 for x in range(0,n_samples,plot_update_steps))
frame_indices[0] = 0
frame_indices.append(n_samples-1)
ani = FuncAnimation(fig, 
                    prepare_animation(x_bar_container, x_scat, x_avg_ln, x_samples_text,
                                      f_bar_container, f_scat, f_avg_ln, f_samples_text), 
                    frames=frame_indices, blit=False, interval=1, repeat=False)

plt.show()

# # Save the animation
# anim.save('./animation.mp4', writer="ffmpeg", bitrate=-1, fps=30)
