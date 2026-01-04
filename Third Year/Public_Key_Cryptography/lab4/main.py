from rsa_core import generate_rsa_keys, rsa_encrypt, rsa_decrypt
from alphabet_coder import text_to_blocks, blocks_to_text

KEY_BITS = 128

def main():
    PLAINTEXT = input("Enter the plaintext: ")

    # Generate Key Pair
    public_key, private_key = generate_rsa_keys(KEY_BITS)
    
    # Extract common parameters
    n = public_key['n']
    e = public_key['e']
    d = private_key['d']
    
    # We now retrieve both k (plaintext block) and l (ciphertext block)
    k = public_key['k']
    l = public_key['l']
    
    print(f"Modulus (n): {n}")
    print(f"Public Exponent (e): {e}")
    print(f"Private Exponent (d): {d}")
    print(f"Plaintext Block Size (k):  {k}")
    print(f"Ciphertext Block Size (l): {l}\n")
    
    print("## Encryption")
    print(f"Original Plaintext: '{PLAINTEXT}'")
    
    try:
        # Plaintext Validation and Conversion
        # We use 'k' to pack the plaintext into numbers M where M < n
        plaintext_blocks = text_to_blocks(PLAINTEXT, k)
    except ValueError as e:
        print(f"Plaintext Validation Failed: {e}")
        return

    print(f"Numeric Blocks (M): {plaintext_blocks}")

    # Encryption
    # C = M^e mod n
    ciphertext_blocks = rsa_encrypt(public_key, plaintext_blocks)
    print(f"Numeric Cipher (C): {ciphertext_blocks}")
    
    # We use 'l' to unpack the cipher integers into text
    # This ensures every C (which is < n) fits into l characters.
    ciphertext_string = blocks_to_text(ciphertext_blocks, l)
    print(f"Ciphertext String:  '{ciphertext_string}'")

    print("## Decryption")
    print(f"Received String:    '{ciphertext_string}'")
    
    # Convert Ciphertext String back to Numeric Blocks
    # We use 'l' because that's how it was packed
    try:
        received_ciphertext_blocks = text_to_blocks(ciphertext_string, l)
    except ValueError as e:
        print(f"Ciphertext Reading Failed: {e}")
        return
        
    print(f"Numeric Cipher (C): {received_ciphertext_blocks}")

    # Decryption
    # M = C^d mod n
    try:
        decrypted_blocks = rsa_decrypt(private_key, received_ciphertext_blocks)
    except ValueError as e:
        print(f"Ciphertext Validation Failed: {e}")
        return
        
    print(f"Decrypted Blocks (M): {decrypted_blocks}")

    # Convert numeric blocks back to text
    # We use 'k' because that's how the original message was packed
    decrypted_text = blocks_to_text(decrypted_blocks, k)
    
    # Remove any trailing padding spaces for clean comparison
    decrypted_text_clean = decrypted_text.rstrip(' ')
    
    # Final comparison
    print(f"Decrypted Plaintext: '{decrypted_text_clean}'")

    if decrypted_text_clean.upper() == PLAINTEXT.upper():
        print("\nSUCCESS: Decrypted text matches original plaintext.")
    else:
        print("\nFAILURE: Decrypted text does NOT match original plaintext.")

if __name__ == "__main__":
    main()