def gcd(a, b):
    """
        Compute GCD using division and modulo repeatedly
    """
    if b==0:
        return a
    return gcd(b, a % b)


def generators_of_Zn(n):
    """
        Finds all generators of the cyclic group (Zn, +).
    """
    if n < 2:
        raise ValueError("n must be a natural number greater or equal to 2.")
    
    generators = []
    
    # for each element from 0 to n-1 check if they are coprime with n
    for g in range(n):
        # if the element is coprime with n, then it is a generator 
        # this condition is true because if n and g have a divisor>1, 
        # then some numbers will be skiped when checking the formula x=kg 
        # because the product will be a multiple of the divisor.
        # ex: for gcd(n, g)=2, all odd numbers will be skiped.
        if gcd(g, n) == 1:
            generators.append(g)
    return generators


if __name__ == "__main__":
    n = int(input("Enter n (>=2): "))
    gens = generators_of_Zn(n)
    print(f"Generators of (Z{n}, +): {gens}")