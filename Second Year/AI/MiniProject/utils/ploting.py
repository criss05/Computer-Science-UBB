import numpy as np
import matplotlib.pyplot as plt


def plot_function(func, x_lim, y_lim, title):
    x = np.linspace(*x_lim, num=100)
    y = np.linspace(*y_lim, num=100)
    X, Y = np.meshgrid(x, y)
    Z = func(X, Y)

    fig = plt.figure(figsize=(15,10))

    ax1 = fig.add_subplot(1,2,1)
    cp = ax1.contourf(X, Y, Z, levels=50, cmap='viridis')
    fig.colorbar(cp, ax=ax1)
    ax1.set_title(f'{title} - Contour')

    ax2 = fig.add_subplot(1,2,2, projection='3d')
    ax2.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none')
    ax2.set_title(f'{title} - Surface')

    plt.tight_layout()
    plt.show()
