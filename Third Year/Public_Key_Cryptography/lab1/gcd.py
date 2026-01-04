import time


# euclidean algorithm based on divisions
def euclidean(a, b):
    """
        Compute GCD using division and modulo repeatedly
    """
    if b==0:
        return a
    return euclidean(b, a % b)


# brute force
def brute_force(a, b):
    """
        Compute GCD by checking all possible divisors
    """
    if a == 0: return b
    if b == 0: return a
    for i in range(min(a, b), 0, -1):
        if a % i == 0 and b % i == 0:
            return i


# stein's algorithm (binary gcd)
def stein(a, b):
    """
        Compute GCD using Stein's algorithm:
        1. Remove common factors of 2.
        2. Divide even numbers by 2 until odd.
        3. Subtract smaller from larger until one is 0.
        4. Multiply remaining number by removed 2s.
    """
    # if one of the numbers are 0, return the other one
    if a == 0: return b
    if b == 0: return a

    shift = 0 # count common factors of 2

    # remove all factors of 2 from a and b
    while (a | b) & 1 == 0: # a and b are even
        a >>= 1 # divide a by 2
        b >>= 1 # divide b by 2
        shift += 1

    # make a odd, if not already
    while a & 1 == 0:
        a >>= 1

    # reduce b until it becomes 0
    while b != 0:
        # make sure b is odd each time
        while b & 1 == 0:
            b >>= 1 

        if a > b:
            a, b = b, a # swap the elements

        b -= a # substract smaller from larger (both are odd numbers)

    # multiply by the common factors of 2 to get final GCD
    return a << shift # a* 2^shift


inputs = [
    (48, 18), (123456, 789012), (101, 103),
    (2**20, 2**15), (99999, 11111), (1, 1),
    (270, 192), (987654321, 123456789), (17, 31), (0, 45)
]

print(f"{'Input':>21} | {'Euclidean (s)':>15} | {'Brute-force (s)':>17} | {'Stein (s)':>12} | {'GCD Euclid':>10} | {'GCD Brute':>10} | {'GCD Stein':>10}")
print("-"*110)

# Test and print each result
for a, b in inputs:
    start = time.perf_counter()
    res1 = euclidean(a, b)
    t_euclid = time.perf_counter() - start

    start = time.perf_counter()
    res2 = brute_force(a, b)
    t_brute = time.perf_counter() - start

    start = time.perf_counter()
    res3 = stein(a, b)
    t_stein = time.perf_counter() - start

    print(f"({a},{b})".rjust(21), "|",
          f"{t_euclid:.8f}".rjust(15), "|",
          f"{t_brute:.8f}".rjust(17), "|",
          f"{t_stein:.8f}".rjust(12), "|",
          f"{res1}".rjust(10), "|",
          f"{res2}".rjust(10), "|",
          f"{res3}".rjust(10))