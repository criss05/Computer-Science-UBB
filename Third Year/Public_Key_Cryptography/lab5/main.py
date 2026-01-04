import secrets
import hashlib
import sys

# --- Helper Functions ---

def mod_inverse(a, m):
    """
    Computes the modular multiplicative inverse of a modulo m
    using Python's built-in pow(a, -1, m) for Python 3.8+.
    """
    return pow(a, -1, m)

def hash_function(u1, u2, e):
    """
    A cryptographic hash function H(u1, u2, e) -> Integer.
    Uses SHA-256.
    """
    data = f"{u1}{u2}{e}".encode('utf-8')
    digest = hashlib.sha256(data).hexdigest()
    return int(digest, 16)

class CramerShoup:
    def __init__(self):
        # We use a fixed large Safe Prime (p = 2q + 1) for the lab to ensure performance.
        # This is a 1024-bit safe prime from RFC 3526 (Group 2).
        self.p = int(
            "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD1"
            "29024E088A67CC74020BBEA63B139B22514A08798E3404DD"
            "EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245"
            "E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
            "EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3D"
            "C2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F"
            "83655D23DCA3AD961C62F356208552BB9ED529077096966D"
            "670C354E4ABC9804F1746C08CA18217C32905E462E36CE3B"
            "E39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9"
            "DE2BCBF6955817183995497CEA956AE515D2261898FA0510"
            "15728E5A8AACAA68FFFFFFFFFFFFFFFF", 16
        )
        # Order of the group (approximately p-1 for Zp*)
        self.q = (self.p - 1) // 2 
        
        # Alphabet definition: Space + A-Z
        self.alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        # Mapping: ' '->1, 'A'->2, ..., 'Z'->27 (Avoid 0 for multiplicative group)
        self.char_to_int = {char: i + 1 for i, char in enumerate(self.alphabet)}
        self.int_to_char = {i + 1: char for i, char in enumerate(self.alphabet)}

        self.public_key = None
        self.private_key = None

    def generate_keys(self):
        """
        Generates Public and Private keys.
        """
        print("[*] Generating Keys...")
        
        # 1. Generators
        # We pick random elements in [2, p-2]
        g1 = 1 + secrets.randbelow(self.p - 2)
        g2 = 1 + secrets.randbelow(self.p - 2)
        
        # 2. Private Key Components (x1, x2, y1, y2, z)
        # Random scalars in [0, q-1] (conceptually) or just [0, p-2] for Zp implementation
        x1 = secrets.randbelow(self.p - 1)
        x2 = secrets.randbelow(self.p - 1)
        y1 = secrets.randbelow(self.p - 1)
        y2 = secrets.randbelow(self.p - 1)
        z  = secrets.randbelow(self.p - 1)
        
        # 3. Public Key Components (c, d, h)
        # c = g1^x1 * g2^x2
        c = (pow(g1, x1, self.p) * pow(g2, x2, self.p)) % self.p
        
        # d = g1^y1 * g2^y2
        d = (pow(g1, y1, self.p) * pow(g2, y2, self.p)) % self.p
        
        # h = g1^z
        h = pow(g1, z, self.p)
        
        self.public_key = (g1, g2, c, d, h)
        self.private_key = (x1, x2, y1, y2, z)
        
        print("[+] Keys Generated.")
        print(f"    Public Key (h): {h}...") # Print snippet only
        
    def validate_plaintext(self, plaintext):
        """
        (iii) Plaintext Validation: Checks if characters are in the alphabet.
        """
        for char in plaintext:
            if char not in self.alphabet:
                raise ValueError(f"Invalid character '{char}' in plaintext. Only A-Z and Space allowed.")
        return True

    def encrypt(self, plaintext):
        """
        Encrypts a string plaintext using the Public Key.
        Returns a list of tuples (u1, u2, e, v) per character.
        """
        if not self.public_key:
            raise Exception("Keys not generated yet.")
        
        self.validate_plaintext(plaintext)
        
        g1, g2, c, d, h = self.public_key
        ciphertexts = []
        
        print(f"[*] Encrypting message: '{plaintext}'")
        
        for char in plaintext:
            m = self.char_to_int[char] # Convert char to integer message
            
            # Select random r
            r = secrets.randbelow(self.p - 1)
            
            # Compute u1, u2
            u1 = pow(g1, r, self.p)
            u2 = pow(g2, r, self.p)
            
            # Compute e = h^r * m
            e = (pow(h, r, self.p) * m) % self.p
            
            # Compute alpha = H(u1, u2, e)
            alpha = hash_function(u1, u2, e)
            
            # Compute v = c^r * d^(r*alpha)
            # v = (g1^x1 g2^x2)^r * (g1^y1 g2^y2)^(r*alpha)
            # This is equal to: u1^(x1 + y1*alpha) * u2^(x2 + y2*alpha)
            # But during encryption we use the public components c and d:
            term1 = pow(c, r, self.p)
            term2 = pow(d, r * alpha, self.p) # Note: exponent might be large, python handles it
            v = (term1 * term2) % self.p
            
            ciphertexts.append((u1, u2, e, v))
            
        return ciphertexts

    def decrypt(self, ciphertexts):
        """
        Decrypts a list of ciphertexts using the Private Key.
        (iv) Includes Ciphertext Validation.
        """
        if not self.private_key:
            raise Exception("Private key missing.")
            
        x1, x2, y1, y2, z = self.private_key
        decrypted_message = ""
        
        print("[*] Decrypting...")
        
        for i, ct in enumerate(ciphertexts):
            u1, u2, e, v = ct
            
            # 1. Compute alpha
            alpha = hash_function(u1, u2, e)
            
            # 2. VALIDATION CHECK (The core of Cramer-Shoup)
            # Verify if u1^(x1 + y1*alpha) * u2^(x2 + y2*alpha) == v
            
            exponent_1 = x1 + (y1 * alpha)
            exponent_2 = x2 + (y2 * alpha)
            
            check_val = (pow(u1, exponent_1, self.p) * pow(u2, exponent_2, self.p)) % self.p
            
            if check_val != v:
                print(f"[!] Validation Failed for character at index {i}!")
                return None # Reject entire message if one block is tampered
                
            # 3. Decryption
            # m = e / u1^z
            u1_z = pow(u1, z, self.p)
            u1_z_inv = mod_inverse(u1_z, self.p)
            m = (e * u1_z_inv) % self.p
            
            # Convert int back to char
            if m in self.int_to_char:
                decrypted_message += self.int_to_char[m]
            else:
                decrypted_message += "?" # Should not happen if m was valid
                
        return decrypted_message

# --- Main Execution Block ---
if __name__ == "__main__":
    # Initialize System
    cs = CramerShoup()
    
    # 1. Generate Keys
    cs.generate_keys()
    
    # 2. Define a Plaintext
    # Allowed: A-Z and Space
    msg = "PUBLIC KEY CRYPTOGRAPHY"
    
    # 3. Encrypt
    try:
        encrypted_data = cs.encrypt(msg)
        print(f"[+] Encryption successful. First block: {encrypted_data[0]}")
    except ValueError as e:
        print(f"[!] Error: {e}")
        sys.exit(1)

    # 4. Decrypt
    decrypted_msg = cs.decrypt(encrypted_data)
    
    if decrypted_msg:
        print(f"[+] Decrypted Message: '{decrypted_msg}'")
    else:
        print("[!] Decryption failed due to invalid ciphertext.")

    # --- Demonstration of Validation (Tampering) ---
    print("\n--- Tampering Test ---")
    # Let's modify the verification tag 'v' of the first character
    u1, u2, e, v = encrypted_data[0]
    tampered_v = (v + 1) % cs.p
    encrypted_data[0] = (u1, u2, e, tampered_v)
    
    print("[*] Tampered with the first ciphertext block.")
    result = cs.decrypt(encrypted_data)
    if result is None:
        print("[+] Validation worked! The system rejected the tampered ciphertext.")
