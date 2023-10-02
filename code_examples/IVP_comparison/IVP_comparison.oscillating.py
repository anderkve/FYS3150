import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

# Colors
#66c2a5
#fc8d62
#8da0cb
#e78ac3
#a6d854




# 
# Second-order diff. eq.: d^2y/dt^2 = f(t,y)
#

w = 2. * np.pi

def f(t,y):
  # Diff eq: d^2y/dt^2 = -w^2 y(t)
  return -1.0 * w*w * y


#
# Analytical solution
#
def y_true(t):
  return np.sin(w * t)


#
# Forward Euler
#
def forward_euler(t_i, y_i, vy_i, dt):
  f_i = f(t_i, y_i)
  vy_ip1 = vy_i + dt * f_i
  y_ip1 = y_i + dt * vy_i
  return y_ip1, vy_ip1


# #
# # Euler-Cromer
# #
# def euler_cromer(t_i, y_i, vy_i, dt):
#   f_i = f(t_i, y_i)
#   vy_ip1 = vy_i + dt * f_i
#   y_ip1 = y_i + dt * vy_ip1
#   return y_ip1, vy_ip1



#
# Predictor-Corrector
#
def predictor_corrector(t_i, y_i, vy_i, dt):
  fv_i = f(t_i, y_i)
  t_ip1 = t_i + dt
  y_ip1_star = y_i + dt * vy_i
  f_ip1_star = f(t_ip1, y_ip1_star)
  vy_ip1 = vy_i + dt * 0.5 * (f_ip1_star + fv_i)
  y_ip1 = y_i + dt * 0.5 * (vy_ip1 + vy_i)
  return y_ip1, vy_ip1


#
# Leapfrog
#
first_LF = True
def leapfrog(t_i, y_i, vy_im05, dt):
  global first_LF

  f_i = f(t_i, y_i)

  if first_LF:
    vy_ip05 = vy_im05 + 0.5 * dt * f_i
    y_ip1 = y_i + dt * vy_ip05
    first_LF = False
  else:
    vy_ip05 = vy_im05 + dt * f_i
    y_ip1 = y_i + dt * vy_ip05

  return y_ip1, vy_ip05


#
# Runge-Kutta 4
#
def runge_kutta_4(t_i, y_i, vy_i, dt):

  k1_y = dt * vy_i
  k1_v = dt * f(t_i, y_i)

  k2_y = dt * (vy_i + 0.5 * k1_v)
  k2_v = dt * f(t_i + 0.5 * dt, y_i + 0.5 * k1_y)

  k3_y = dt * (vy_i + 0.5 * k2_v)
  k3_v = dt * f(t_i + 0.5 * dt, y_i + 0.5 * k2_y)

  k4_y = dt * (vy_i + 1.0 * k3_v)
  k4_v = dt * f(t_i + 1.0 * dt, y_i + k3_y)

  y_ip1 = y_i + (1./6.) * (k1_y + 2 * k2_y + 2 * k3_y + k4_y)
  vy_ip1 = vy_i + (1./6.) * (k1_v + 2 * k2_v + 2 * k3_v + k4_v)

  return y_ip1, vy_ip1



# 
# Relative error
# 
def rel_err(y_approx, y_true):
  if y_true == 0.0:
    return 0.0
  return np.abs((y_approx - y_true) / y_true)

# 
# Amplification factor
# 
def amp_factor(delta_i, delta_ip1):
  if delta_i == 0.0:
    return 0.0
  return np.abs(delta_ip1 / delta_i)


# -----------------------------------------------------

# Time settings

dt = 0.20

t_0 = 0.0

t_max = 15.0


# Create figre for plotting

# fig = plt.figure(figsize=(16,12))
# gs = gridspec.GridSpec(4, 1, height_ratios=[2,1,1,1], figure=fig)
fig = plt.figure(figsize=(16,8))
gs = gridspec.GridSpec(3, 1, height_ratios=[2,1,1], figure=fig)

ax1 = fig.add_subplot(gs[0])
plt.sca(ax1)
plt.plot([t_0, t_max], [0,0], '--', linewidth=1.0, color='0.0')
t_axis_true = np.linspace(t_0, t_max, 401)
y_vals_true = y_true(t_axis_true)
plt.plot(t_axis_true, y_vals_true, '-', linewidth=3.0, color='0.0', label="True")

plt.xlim([t_0, t_max])
# plt.ylim([-0.4, 1.2])
plt.ylim([-2.0, 2.0])
plt.xlabel("t")
plt.ylabel("y")
# plt.yscale("log")

ax2 = fig.add_subplot(gs[1], sharex=ax1)
plt.sca(ax2)
plt.xlim([t_0, t_max])
plt.xlabel("t")
plt.ylabel("relative error")
plt.yscale("log")
# plt.ylim([0.0, 1.0])
plt.ylim([1.0e-3, 1.0e2])

ax3 = fig.add_subplot(gs[2], sharex=ax1)
plt.sca(ax3)
plt.xlim([t_0, t_max])
plt.xlabel("t")
plt.ylabel("absolute error")
plt.yscale("log")
# plt.ylim([1.0e-3, 1.0e0])
# plt.ylim([0.0, 1.0])

# ax4 = fig.add_subplot(gs[3], sharex=ax1)
# plt.sca(ax4)
# plt.plot([t_0, t_max], [1,1], '--', linewidth=1.0, color='0.0')
# plt.xlim([t_0, t_max])
# plt.xlabel("t")
# plt.ylabel("amp. factor")
# plt.ylim([-1.0, 4.0])

plt.pause(0.5)



# Initial conditions
y_0 = 0.0
vy_0 = w

# Time loop
i = 0
t_i = t_0

y_i_FE = y_0
vy_i_FE = vy_0
y_ip1_FE = 0.0
vy_ip1_FE = 0.0

# y_i_EC = y_0
# vy_i_EC = vy_0
# y_ip1_EC = 0.0
# vy_ip1_EC = 0.0

y_i_PC = y_0
vy_i_PC = vy_0
y_ip1_PC = 0.0
vy_ip1_PC = 0.0

y_i_LF = y_0
vy_im05_LF = vy_0
y_ip1_LF = 0.0
vy_ip05_LF = 0.0

y_i_RK = y_0
vy_i_RK = vy_0
y_ip1_RK = 0.0
vy_ip1_RK = 0.0

y_i_true = y_true(t_i)
y_ip1_true = 0.0

rel_err_i_FE = rel_err(y_i_FE, y_i_true)
rel_err_ip1_FE = rel_err(y_ip1_FE, y_ip1_true)

# rel_err_i_EC = rel_err(y_i_EC, y_i_true)
# rel_err_ip1_EC = rel_err(y_ip1_EC, y_ip1_true)

rel_err_i_PC = rel_err(y_i_PC, y_i_true)
rel_err_ip1_PC = rel_err(y_ip1_PC, y_ip1_true)

rel_err_i_LF = rel_err(y_i_LF, y_i_true)
rel_err_ip1_LF = rel_err(y_ip1_LF, y_ip1_true)

rel_err_i_RK = rel_err(y_i_RK, y_i_true)
rel_err_ip1_RK = rel_err(y_ip1_RK, y_ip1_true)

while t_i < t_max:

  # # Print current step
  # print(t_i, y_i)

  # Compute next steps
  t_ip1 = t_i + dt

  # - Compute next step w/ true function
  y_ip1_true = y_true(t_ip1)

  # - Compute next step w/ Forward Euler
  y_ip1_FE, vy_ip1_FE = forward_euler(t_i, y_i_FE, vy_i_FE, dt)
  rel_err_ip1_FE = rel_err(y_ip1_FE, y_ip1_true)

  # # - Compute next step w/ Euler-Cromer
  # y_ip1_EC, vy_ip1_EC = euler_cromer(t_i, y_i_EC, vy_i_EC, dt)
  # rel_err_ip1_EC = rel_err(y_ip1_EC, y_ip1_true)

  # - Compute next step w/ Predictor-Corrector
  y_ip1_PC, vy_ip1_PC = predictor_corrector(t_i, y_i_PC, vy_i_PC, dt)
  rel_err_ip1_PC = rel_err(y_ip1_PC, y_ip1_true)

  # - Compute next step w/ Leapfrog
  y_ip1_LF, vy_ip05_LF = leapfrog(t_i, y_i_LF, vy_im05_LF, dt)
  rel_err_ip1_LF = rel_err(y_ip1_LF, y_ip1_true)

  # - Compute next step w/ Runge-Kutta 4
  y_ip1_RK, vy_ip1_RK = runge_kutta_4(t_i, y_i_RK, vy_i_RK, dt)
  rel_err_ip1_RK = rel_err(y_ip1_RK, y_ip1_true)


  # Plot functions
  plt.sca(ax1)

  # plt.plot([t_i, t_ip1], [y_i_FE, y_ip1_FE], '-', color='#66c2a5', linewidth=2.5, alpha=0.8)
  # plt.plot([t_i, t_ip1], [y_i_EC, y_ip1_EC], '-', color='#3d7463', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [y_i_PC, y_ip1_PC], '-', color='#fc8d62', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [y_i_LF, y_ip1_LF], '-', color='#a6d854', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [y_i_RK, y_ip1_RK], '-', color='#e78ac3', linewidth=2.5, alpha=0.8)

  plt.plot([t_i, t_ip1], [y_i_true, y_ip1_true], '.', color='0.5', markersize=14.0, mew=0.5, mec='0.1', alpha=1.0, label="True")

  # plt.plot([t_i, t_ip1], [y_i_FE, y_ip1_FE], '.', color='#66c2a5', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0, label="Forward Euler")
  # plt.plot([t_i, t_ip1], [y_i_EC, y_ip1_EC], '.', color='#3d7463', markersize=12.0, mew=0.5, mec='0.1', alpha=1.0, label="Euler-Cromer")
  plt.plot([t_i, t_ip1], [y_i_PC, y_ip1_PC], '.', color='#fc8d62', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0, label="Predictor-Corrector")
  plt.plot([t_i, t_ip1], [y_i_LF, y_ip1_LF], '.', color='#a6d854', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0, label="Leapfrog")
  plt.plot([t_i, t_ip1], [y_i_RK, y_ip1_RK], '.', color='#e78ac3', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0, label="Runge-Kutta 4")
  
  if i == 0:
    plt.legend()

  # Plot relative errors
  plt.sca(ax2)
  # plt.plot([t_i, t_ip1], [rel_err_i_FE, rel_err_ip1_FE], '-', color='#66c2a5', linewidth=2.5, alpha=0.8)
  # plt.plot([t_i, t_ip1], [rel_err_i_EC, rel_err_ip1_EC], '-', color='#3d7463', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [rel_err_i_PC, rel_err_ip1_PC], '-', color='#fc8d62', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [rel_err_i_LF, rel_err_ip1_LF], '-', color='#a6d854', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [rel_err_i_RK, rel_err_ip1_RK], '-', color='#e78ac3', linewidth=2.5, alpha=0.8)

  # plt.plot([t_i, t_ip1], [rel_err_i_FE, rel_err_ip1_FE], '.', color='#66c2a5', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  # plt.plot([t_i, t_ip1], [rel_err_i_EC, rel_err_ip1_EC], '.', color='#3d7463', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  plt.plot([t_i, t_ip1], [rel_err_i_PC, rel_err_ip1_PC], '.', color='#fc8d62', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  plt.plot([t_i, t_ip1], [rel_err_i_LF, rel_err_ip1_LF], '.', color='#a6d854', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  plt.plot([t_i, t_ip1], [rel_err_i_RK, rel_err_ip1_RK], '.', color='#e78ac3', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)

  # Plot absolute errors and amplification factors
  plt.sca(ax3)
  # plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_FE, y_ip1_true * rel_err_ip1_FE], '-', color='#66c2a5', linewidth=2.5, alpha=0.8)
  # plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_EC, y_ip1_true * rel_err_ip1_EC], '-', color='#3d7463', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_PC, y_ip1_true * rel_err_ip1_PC], '-', color='#fc8d62', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_LF, y_ip1_true * rel_err_ip1_LF], '-', color='#a6d854', linewidth=2.5, alpha=0.8)
  plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_RK, y_ip1_true * rel_err_ip1_RK], '-', color='#e78ac3', linewidth=2.5, alpha=0.8)

  # plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_FE, y_ip1_true * rel_err_ip1_FE], '.', color='#66c2a5', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  # plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_EC, y_ip1_true * rel_err_ip1_EC], '.', color='#3d7463', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_PC, y_ip1_true * rel_err_ip1_PC], '.', color='#fc8d62', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_LF, y_ip1_true * rel_err_ip1_LF], '.', color='#a6d854', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  plt.plot([t_i, t_ip1], [y_i_true * rel_err_i_RK, y_ip1_true * rel_err_ip1_RK], '.', color='#e78ac3', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)

  # plt.sca(ax4)
  # # af_FE = amp_factor(y_i_FE - y_i_true, y_ip1_FE - y_ip1_true)
  # # af_EC = amp_factor(y_i_EC - y_i_true, y_ip1_EC - y_ip1_true)
  # af_PC = amp_factor(y_i_PC - y_i_true, y_ip1_PC - y_ip1_true)
  # af_LF = amp_factor(y_i_LF - y_i_true, y_ip1_LF - y_ip1_true)
  # af_RK = amp_factor(y_i_RK - y_i_true, y_ip1_RK - y_ip1_true)

  # # plt.plot(t_ip1, af_FE, '.', color='#66c2a5', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  # # plt.plot(t_ip1, af_EC, '.', color='#3d7463', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  # plt.plot(t_ip1, af_PC, '.', color='#fc8d62', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  # plt.plot(t_ip1, af_LF, '.', color='#a6d854', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)
  # plt.plot(t_ip1, af_RK, '.', color='#e78ac3', markersize=9.0, mew=0.5, mec='0.1', alpha=1.0)


  plt.pause(0.001)


  # Update for next iteration
  y_i_true = y_ip1_true

  y_i_FE = y_ip1_FE
  vy_i_FE = vy_ip1_FE

  # y_i_EC = y_ip1_EC
  # vy_i_EC = vy_ip1_EC

  y_i_PC = y_ip1_PC
  vy_i_PC = vy_ip1_PC

  y_i_LF = y_ip1_LF
  vy_im05_LF = vy_ip05_LF

  y_i_RK = y_ip1_RK
  vy_i_RK = vy_ip1_RK

  t_i = t_ip1
  i += 1

  rel_err_i_FE = rel_err_ip1_FE
  # rel_err_i_EC = rel_err_ip1_EC
  rel_err_i_PC = rel_err_ip1_PC
  rel_err_i_LF = rel_err_ip1_LF
  rel_err_i_RK = rel_err_ip1_RK

plt.show()