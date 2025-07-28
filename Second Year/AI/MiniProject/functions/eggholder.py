import numpy as np

def eggholder(x, y):
    """
    Eggholder function.
    Global minimum at (512, 404.2319), where f(x, y) ≈ -959.6407.

    Parameters:
    x : float
        The x-coordinate.
    y : float
        The y-coordinate.

    Returns:
    float
        The value of the Eggholder function at (x, y).
    """
    term1 = -(y + 47) * np.sin(np.sqrt(abs(x / 2 + (y + 47))))
    term2 = -x * np.sin(np.sqrt(abs(x - (y + 47))))
    return term1 + term2

DOMAIN_EG=[-512, 512]
