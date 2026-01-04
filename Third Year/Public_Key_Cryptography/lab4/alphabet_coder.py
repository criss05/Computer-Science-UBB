ALPHABET = " " + "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
ALPHABET_SIZE = 27

def char_to_int(char):
    """Maps a character to its integer value (0-26)."""
    char = char.upper()
    if char not in ALPHABET:
        raise ValueError(f"Invalid character '{char}'. Only blank and A-Z allowed.")
    return ALPHABET.index(char)

def int_to_char(integer):
    """Maps an integer value (0-26) back to a character."""
    if not 0 <= integer < ALPHABET_SIZE:
        raise ValueError(f"Invalid integer code: {integer}. Must be between 0 and 26.")
    return ALPHABET[integer]

def text_to_blocks(plaintext, block_size):
    """
    Converts plaintext into a list of integers (blocks) based on the block_size.
    Each block represents an integer M.
    """
    numeric_values = [char_to_int(char) for char in plaintext]
    blocks = []
    
    # Pad the text with ' ' (code 0) if length is not a multiple of block_size
    while len(numeric_values) % block_size != 0:
        numeric_values.append(0) 

    # Combine character codes into a single integer block
    for i in range(0, len(numeric_values), block_size):
        block_int = 0
        for j in range(block_size):
            block_int += numeric_values[i + j] * (ALPHABET_SIZE ** (block_size - 1 - j))
        blocks.append(block_int)
        
    return blocks

def blocks_to_text(blocks, block_size):
    """
    Converts a list of integer blocks back to plaintext.
    """
    plaintext = ""
    for block_int in blocks:
        temp_block = block_int
        codes = []
        for _ in range(block_size):
            code = temp_block % ALPHABET_SIZE
            codes.insert(0, code)
            temp_block //= ALPHABET_SIZE
            
        # Convert codes to characters and append to plaintext
        for code in codes:
            plaintext += int_to_char(code)
            
    return plaintext

def get_k_and_l(n):
    """
    Calculates both k (plaintext size) and l (ciphertext size).
    Condition: 27^k < n < 27^l
    """
    # Calculate k (max power of 27 strictly less than n)
    k = 0
    while (ALPHABET_SIZE ** (k + 1)) < n:
        k += 1
        
    # Calculate l (min power of 27 strictly greater than n)
    l = k
    while (ALPHABET_SIZE ** l) <= n:
        l += 1
        
    return k, l


# 3