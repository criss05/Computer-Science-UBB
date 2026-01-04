from math_utils import generate_large_prime, gcd, mod_inverse
from alphabet_coder import get_k_and_l

PUBLIC_EXPONENT = 65537 

def generate_rsa_keys(bits=512):
    """
    Generates a public key (n, e) and a private key (n, d).
    """
    # Choose two distinct large primes p and q
    p = generate_large_prime(bits)
    q = generate_large_prime(bits)
    while p == q:
        q = generate_large_prime(bits)
        
    # Calculate n
    n = p * q
    
    # Calculate function phi(n)
    phi_n = (p - 1) * (q - 1)
    
    # Set the public exponent e
    e = PUBLIC_EXPONENT

    if gcd(e, phi_n) != 1:
        # If the standard e is not coprime, throw error
        raise Exception("Failed to find a suitable public exponent e.")

    # Calculate the private exponent d (modular inverse of e mod phi_n)
    d = mod_inverse(e, phi_n)
    
    # Determine the block sizes k and l
    # k is used for plaintext (M < n)
    # l is used for ciphertext strings (C < 27^l)
    k, l = get_k_and_l(n)

    public_key = {'n': n, 'e': e, 'block_size': k, 'k': k, 'l': l}
    private_key = {'n': n, 'd': d, 'block_size': k, 'k': k, 'l': l}
    
    return public_key, private_key

def rsa_encrypt(public_key, plaintext_blocks):
    """
    Encrypts the integer blocks using the public key (n, e).
    C = M^e mod n
    """
    n = public_key['n']
    e = public_key['e']
    
    ciphertext_blocks = []
    for M in plaintext_blocks:
        # C = M^e mod n. Use pow() for efficient modular exponentiation.
        C = pow(M, e, n)
        ciphertext_blocks.append(C)
        
    return ciphertext_blocks

def rsa_decrypt(private_key, ciphertext_blocks):
    """
    Decrypts the integer blocks using the private key (n, d).
    M = C^d mod n
    """
    n = private_key['n']
    d = private_key['d']
    
    # Ciphertext validation: check if C < n.
    for C in ciphertext_blocks:
        if C >= n:
            raise ValueError("Ciphertext validation failed: received block C is >= n.")
            
    decrypted_blocks = []
    for C in ciphertext_blocks:
        # M = C^d mod n. Use pow() for efficient modular exponentiation.
        M = pow(C, d, n)
        decrypted_blocks.append(M)
        
    return decrypted_blocks