import numpy as np

def drop_wave(x, y):
    """
    Drop-Wave function.
    Global minimum at (x, y) = (0, 0), where f(x, y) = -1.

    Parameters:
    x : float
        The x-coordinate.
    y : float
        The y-coordinate.

    Returns:
    float
        The value of the Drop-Wave function at (x, y).
    """
    r_squared = x**2 + y**2
    numerator = 1 + np.cos(12 * np.sqrt(r_squared))
    denominator = 0.5 * r_squared + 2
    return -numerator / denominator

DOMAIN_DW=[-5.12, 5.12]
