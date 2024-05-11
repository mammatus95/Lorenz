#!/usr/bin/python3
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D #für 3D Plots
from io import StringIO
import math

# ---------------------------------------------------------------------------------------------------------------------------

# logistic map
def logisticmap(x, r=2.8):
    return r*x*(1-x)

# henon_2D
def henon_2D(vec, alpha=1.4, beta=0.3):
    return np.array([vec[1] + 1 - alpha * vec[0]*vec[0], 
                     vec[0] * beta])

def fix_points(alpha, beta):
    solution = math.sqrt(alpha)/alpha
    return np.array([solution, solution*beta]), np.array([-solution, -solution*beta])

# henon_3D
def henon_3D(vec, alpha=1.4, beta=0.3):
    return np.array([-(alpha * vec[0]*vec[0]) + vec[2] + 1, 
                     -vec[0] * beta, 
                     beta*vec[0] + vec[1]])

# roessler
def roessler_x(y, z):
    return -y - z

def roessler_y(x, y, a=0.2):
    return x + a*y

def roessler_z(x, z, b=0.2, c=5.7):
    return b + z*(x-c)

# Peter de Jong
def jong(vec, a=1.641, b=1.902, c=0.316, d=1.525):
    return np.array([np.sin(a*vec[1]) - np.cos(b*vec[0]), 
                     np.sin(c*vec[0]) - np.cos(d*vec[1])])

# lorenz
def lorenz_func(x, y, z, sig=10, r=28, b=8/3):
    """
    Parameters:
    ----------
    x : velocity
    y : temperature
    z : thermal stratification
    sig : Prantl number
    r : Rayleigh number
    b : Aspekt number
    Returns:
    -------
    np.array([dx, dy, dz])
    """
    return np.array([sig*(-x + y), 
                     -y + x*(r - z), 
                     -b*z + x*y])

# conserved quantities
def conservation_func(x, y, z, r, sig, kind='vor'):
    """
    Parameters:
    ----------
    x : velocity
    y : temperature
    z : thermal stratification
    sig : Prantl number
    r : Rayleigh number
    kind : vor => Vorlesung
    Returns:
    -------
    np.array([H, C])
    """
    if kind=='vor':
        return np.array([0.5*y*y + 0.5*z*z - r*z, 0.5*x*x - sig*z])
    else: 
        return np.array([0.5*y*y + 0.5*z*z, 0.5*x*x])

# dy/dz dx/dz
def dydz_func(y, z, r):
    return (r-z)/y


def dxdz_func(x, sig):
    return x/sig

# fix points
def fix_func(sig, r, b):
    """
    Parameter:
    ----------
    sig : Prantl number
    r : Rayleigh number
    b : Aspekt number
    Returns:
    -------
    fix points as tuple(np.array, np.array)
    """
    Z=r-1
    if b*(r-1) >= 0.0:
        XY=np.sqrt(b*(r-1))
        return (np.array([XY, XY, r-1]), np.array([-XY, -XY, r-1]))
    else:
        return (np.array([0, 0, 0]), np.array([0, 0, 0]))


def rho_crit(sig, b):
    """
    Parameter:
    ----------
    sig : Prantl number
    b : Aspekt number
    Returns:
    -------
    critical Rayleigh number
    """
    return (sig*(sig+b+3))/(sig-b-1)

# ---------------------------------------------------------------------------------------------------------------------------
# wrapper with plots

def henon_2d_wrapper(x_0=0, y_0=0, a=1.4, b=0.3, plot=True, notebook=False):
    # Iterations
    n = 10000
    # time steps
    # delta_t = 0.01
    
    rlt=np.zeros(2*n, dtype=np.float128).reshape(n, 2)
    rlt[0, 0] = x_0
    rlt[0, 1] = y_0
    i=1
    while(i<n):
        rlt[i, :] = henon_2D(rlt[i-1, :], alpha=a, beta=b)
        i += 1

    if plot is True:
        plt.plot(rlt[:, 0], rlt[:, 1], 'r.')
        plt.title("Hénon map 2D")
        if notebook is True:
            plt.show()
        else:
            plt.savefig("./henon_2d.png")
        plt.close()


# roessler
def plot_roessler(X, Y, Z, a, b, c, n, dt, kind, factor=4, notebook=True):
    if kind == "euler" or kind == "Euler Einschritt":
        int_methode = "Euler"
    elif kind == "runge" or kind == "rk":
        int_methode = "Runge-Kutta"
    else:
        int_methode = "unclear"
    fig = plt.figure(figsize=(15*factor, 13*factor))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(X, Y, Z)
    ax.scatter(X[np.size(X)-1], Y[np.size(X)-1], Z[np.size(X)-1], s=200*factor, c='r', marker='o', lw=2.0*factor)#, depthshade=True)
    ax.scatter(X[0], Y[0], Z[0], s=200*factor, c='m', marker='x', lw=2.0*factor)
    plt.annotate("Rössler Attraktor", xy=(0.43, 0.95), xycoords='axes fraction', fontsize=18*factor)
    text1 = r"a : %.1f" % (a)
    text2 = f"b : {b:.1f}"
    text3 = f"c : {c:.1f}"
    plt.annotate(text1, xy=(0.01, 0.9), xycoords='axes fraction', fontsize=15*factor)
    plt.annotate(text2, xy=(0.01, 0.86), xycoords='axes fraction', fontsize=15*factor)
    plt.annotate(text3, xy=(0.01, 0.82), xycoords='axes fraction', fontsize=15*factor)
    plt.annotate(f"Integration: {int_methode}", xy=(0.01, 0.1), xycoords='axes fraction', fontsize=15*factor)
    plt.annotate(f"Count steps: {n}", xy=(0.01, 0.06), xycoords='axes fraction', fontsize=15*factor)
    plt.annotate(f"Timesteps: {dt}", xy=(0.01, 0.02), xycoords='axes fraction', fontsize=15*factor)
    plt.annotate("start point: magenta cross", xy=(0.71, 0.9), xycoords='axes fraction', fontsize=14*factor)
    plt.annotate("end point: red point", xy=(0.71, 0.87), xycoords='axes fraction', fontsize=14*factor)
    ax.set_xlabel('X(t)')
    ax.set_ylabel('Y(t)')
    ax.set_zlabel('Z(t)')
    ax.legend()
    if notebook is True:
        plt.show()
    else:
        plt.savefig(f"roessler_{int_methode}.png")
    plt.close()


def roessler(x_0=0, y_0=0, z_0=0, a=0.2, b=0.2, c=5.7, plot=True, notebook=False):
    # Iterations
    n = 10000
    # time steps
    delta_t = 0.01

    X = np.zeros(n, dtype=np.float128)
    Y = np.zeros(n, dtype=np.float128)
    Z = np.zeros(n, dtype=np.float128)

    X[0] = x_0
    Y[0] = y_0
    Z[0] = z_0

    i=1
    while(i<n):
        X[i] = X[i-1] + delta_t * roessler_x(Y[i-1], Z[i-1])
        Y[i] = Y[i-1] + delta_t * roessler_y(X[i-1], Y[i-1], a)
        Z[i] = Z[i-1] + delta_t * roessler_z(X[i-1], Z[i-1], b, c)
        i += 1

    if plot is True:
        plot_roessler(X, Y, Z, a, b, c, n, delta_t, "euler", factor=3, notebook=notebook)
    else:
        return X, Y, Z

# lorenz
def plot_lorenz(res_lk, sig, b, r, n, dt, kind, fac=3, notebook=False):
    dim = np.shape(res_lk)

    fig = plt.figure(figsize=(15*fac, 13*fac))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(res_lk[0, :], res_lk[1, :], res_lk[2, :])
    ax.scatter(res_lk[0, dim[1]-1], res_lk[1, dim[1]-1], res_lk[2, dim[1]-1], s=200*fac,
               c='r', marker='o', lw=2.0, label='start point')
    ax.scatter(res_lk[0, 0], res_lk[1, 0], res_lk[2, 0], s=200*fac, c='orange', marker='o', label='end point')

    # fix points
    fix_points = fix_func(sig, r, b)
    rhocrit = rho_crit(sig, b)

    ax.scatter(xs=fix_points[0][0], ys=fix_points[0][1], zs=fix_points[0][2], s=200*fac, c='m', marker='o', label='fix point')
    ax.scatter(xs=fix_points[1][0], ys=fix_points[1][1], zs=fix_points[1][2], s=200*fac, c='m', marker='o', label='fix point')

    plt.annotate("Lorenz Attractor", xy=(0.43, 0.96), xycoords='axes fraction', fontsize=15*fac)
    if kind == "euler":
        int_methode = "Euler"
    elif kind == "runge" or kind == "rk":
        int_methode = "Runge-Kutta"
    else:
        int_methode = "unclear"

    text = r"Prandtl number ($\sigma$) : %.1f" % (sig)
    plt.annotate(text, xy=(0.01, 0.9), xycoords='axes fraction', fontsize=15*fac)
    plt.annotate(f"Aspekt number (b): {b:.1f}", xy=(0.01, 0.87), xycoords='axes fraction', fontsize=15*fac)
    plt.annotate(f"Rayleigh number (r): {r:.1f}", xy=(0.01, 0.84), xycoords='axes fraction', fontsize=15*fac)
    text = r"$\rho$-Critical : %.4f" % (rhocrit)
    plt.annotate(text, xy=(0.01, 0.81), xycoords='axes fraction', fontsize=13*fac)
    if r > 1 and r < rhocrit:
        text = "linear stable"
    elif abs(r - rhocrit) < 0.01:
        text = "Hopfbifurkation"
    elif r > rhocrit:
        text = "instable"
    else:
        text = "unclear"
    plt.annotate(text, xy=(0.01, 0.78), xycoords='axes fraction', fontsize=12*fac)
    plt.annotate(f"Integration: {int_methode}", xy=(0.01, 0.09), xycoords='axes fraction', fontsize=13*fac)
    plt.annotate(f"Count steps: {n}", xy=(0.01, 0.06), xycoords='axes fraction', fontsize=13*fac)
    plt.annotate(f"Timesteps: {dt}", xy=(0.01, 0.03), xycoords='axes fraction', fontsize=13*fac)
    ax.set_xlim3d(-25, 25)
    ax.set_ylim3d(-30, 30)
    ax.set_zlim3d(0, 55)
    ax.set_xlabel('Velocity', fontsize=10*fac)
    ax.set_ylabel('Temperature', fontsize=10*fac)
    ax.set_zlabel('Instability', fontsize=10*fac)
    plt.tick_params(axis='both', which='major', labelsize=20)
    ax.legend(loc='best', fontsize=14*fac)
    if notebook is True:
        plt.show()
    else:
        plt.savefig(f"lorenz_{kind}.png")
    plt.close()
    plot_conservedquantities(res_lk[3, :], res_lk[4, :])
    plot_xyz(res_lk[0, :], res_lk[1, :], notebook=False)


# plot conserved quantities
def plot_conservedquantities(H, C, notebook=False):
    _, ax = plt.subplots(figsize=(14, 8))
    x = np.arange(0, np.size(H), 1)
    ax.plot(x, H, 'b-', label='H', lw=0.9)
    ax.plot(x, C, 'r-', label='C', lw=0.9)
    ax.set_xlabel("Time")
    ax.legend()
    plt.title("conserved quantities part")
    if notebook is True:
        plt.show()
    else:
        plt.savefig("lorenz_conserved_quantities.png")
    plt.close()


def plot_xyz(X, Y, notebook=False):
    _, ax = plt.subplots(figsize=(15, 13))
    ax.plot(X, Y, 'b-', lw=0.9)
    ax.set_xlim(-25, 25)
    ax.set_ylim(-30, 32)
    ax.set_xlabel('Geschwindigkeit')
    ax.set_ylabel('Temperatur')
    if notebook is True:
        plt.show()
    else:
        plt.savefig("lorenz_xyz.png")
    plt.close()


def lorenz_euler (x_0=10, y_0=0, z_0=0, sig=10, r=28, b=8/3, ttime=100.0, dt=0.01, plot=True, notebook=False):
    """
    Parameters:
    ------------------------------
    start values : x_0, y_0, z_0
    sig          : Prandtl number
    r            : Rayleigh number
    b            : Aspekt number
    ttime        : total time
    dt           : steps
    """
    # Iterations
    n = int(ttime/dt)
    res = np.zeros((5, n), dtype=np.float128)

    res[0, 0] = x_0
    res[1, 0] = y_0
    res[2, 0] = z_0
    res[3:5, 0] = conservation_func(x_0, y_0, z_0, r, sig, kind='vor')

    i = 1
    while(i<n):
        res[0:3, i] = res[0:3, i-1] + dt * lorenz_func(res[0, i-1], res[1, i-1], res[2, i-1], sig, r, b)
        res[3:5, i] = conservation_func(res[0, i], res[1, i], res[2, i], r, sig, kind='vor')
        i += 1
    if plot is True:
        plot_lorenz (res, sig, b, r, n, dt, "euler", notebook=notebook)


def lorenz_rk (x_0=10, y_0=0, z_0=0, sig=10, r=28, b=8/3, ttime=100.0, dt=0.01, plot=True, notebook=False):
    """
    Parameters:
    ------------------------------
    start values : x_0, y_0, z_0
    sig          : Prandtl number
    r            : Rayleigh number
    b            : Aspekt number
    ttime        : total time
    dt           : steps
    """
    # Iterations
    n = int(ttime/dt)
    res = np.zeros((5, n), dtype=np.float128)

    res[0, 0] = x_0
    res[1, 0] = y_0
    res[2, 0] = z_0
    res[3:5, 0] = conservation_func(x_0, y_0, z_0, r, sig, kind='vor')

    dt2  = (dt/2.0)
    dt_6 = (dt/6.0)
    i=1
    while(i<n):
        K1 = lorenz_func(res[0, i-1], res[1, i-1], res[2, i-1], sig, r, b)
        K2 = lorenz_func(res[0, i-1]+(dt2*K1[0]), res[1, i-1] + (dt2*K1[1]), res[2, i-1] + (dt2*K1[2]), sig, r, b)
        K3 = lorenz_func(res[0, i-1]+(dt2*K2[0]), res[1, i-1] + (dt2*K2[1]), res[2, i-1] + (dt2*K2[2]), sig, r, b)
        K4 = lorenz_func(res[0, i-1]+(dt*K3[0]), res[1, i-1] + (dt*K3[1]), res[2, i-1] + (dt*K3[2]), sig, r, b)
        res[0:3, i] = res[0:3, i-1] + dt_6 * (K1 + 2*K2 + 2*K3 + K4)
        res[3:5, i] = conservation_func(res[0, i], res[1, i], res[2, i], r, sig, kind='vor')
        i += 1
    if plot is True:
        plot_lorenz(res, sig, b, r, n, dt, "rk", notebook=notebook)

# ---------------------------------------------------------------------------------------------------------------------------


if __name__ == "__main__":
    # henon
    henon_2d_wrapper(plot=True)

    # roessler
    roessler(plot=True)

    lorenz_rk(plot=True)
