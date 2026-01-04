from math import *

# how many k values we try
K = 100

def fermat(n, B):
    """
        Generalized Fermat factorization: search for t^2 − k*n = s^2
    """
    for k in range(1, K + 1): 
        # starting value for t (must be above sqrt(k*n))
        t0 = isqrt(k * n)

        # try the next B values of t
        for t in range(t0 + 1, t0 + B + 1):

            # compute s² = t² − k*n
            s2 = t*t - k*n

            if s2 >= 0:
                # integer square root of s²
                s = isqrt(s2)

                # check if s² is a perfect square
                if s * s == s2:
                    return s, t, k

    return None


if __name__ == "__main__":
    n = int(input("n="))
    B = int(input("B="))

    result = fermat(n, B)

    if result is None:
        print("No factorization found.")
    else:
        s, t, k = result

        # print formula directly, without computing factors separately
        print(f"Factorization of n:")
        print(f"n = 1/{k} * ({t} - {s}) * ({t} + {s}) = {(t - s)//k} * {(t + s)//k}")
