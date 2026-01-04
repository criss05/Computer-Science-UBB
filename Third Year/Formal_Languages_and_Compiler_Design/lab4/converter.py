import re
import string
import sys

default_macros = {
    "@letter": list(string.ascii_letters),
    "@digit": list(string.digits),
    "@nonzero": list("123456789"),
}

def expand_symbol(symbol, macros):
    symbol = symbol.strip()

    if symbol == "(space)":
        return [" "]

    if symbol in macros:
        return macros[symbol]

    if re.fullmatch(r"[A-Za-z0-9_+\-.,!?':\"@#$^&<>\\/]", symbol):
        return [symbol]

    if re.fullmatch(r"[A-Za-z0-9_]-[A-Za-z0-9_]", symbol):
        start, end = symbol.split("-")
        return [chr(c) for c in range(ord(start), ord(end) + 1)]

    return [symbol]

def parse_grammar(file_path):
    grammar = {}
    macros = default_macros.copy()

    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue

            if line.startswith("@"):
                parts = re.split(r"\s*=\s*", line)
                if len(parts) == 2:
                    name, value = parts
                    symbols = [s.strip() for s in re.split(r",|\|", value) if s.strip()]
                    expanded = []
                    for s in symbols:
                        expanded.extend(expand_symbol(s, macros))
                    macros[name.strip()] = expanded
                continue

            if "->" in line:
                left, right = line.split("->")
                left = left.strip()
                productions = [r.strip() for r in right.split("|")]
                grammar.setdefault(left, []).extend(productions)

    return grammar, macros

def grammar_to_fa(grammar, macros):
    transitions = {}
    final_states = set()
    alphabet = set()

    for left, productions in grammar.items():
        for prod in productions:
            parts = re.findall(r'\(space\)|"[^"]*"|[^\s]+', prod)

            if len(parts) == 1:
                symbol = parts[0]
                for s in expand_symbol(symbol, macros):
                    transitions.setdefault(left, {}).setdefault(s, []).append("F")
                    alphabet.add(s)
                    final_states.add("F")

            elif len(parts) == 2:
                symbol, next_state = parts
                for s in expand_symbol(symbol, macros):
                    transitions.setdefault(left, {}).setdefault(s, []).append(next_state)
                    alphabet.add(s)

            else:
                raise ValueError(f"Unexpected production format: {prod}")

    states = set(transitions.keys())
    for trans in transitions.values():
        for next_states in trans.values():
            states.update(next_states)

    start_state = next(iter(grammar.keys())) if grammar else None

    return transitions, states, alphabet, start_state, final_states

def write_fa(file_path, transitions, states, alphabet, start_state, final_states):
    with open(file_path, "w", encoding="utf-8") as f:
        f.write("Finite Automata\n")

        f.write(f"Q: {', '.join(sorted(states))}\n")
        f.write(f"E: {', '.join(sorted(alphabet))}\n")
        f.write(f"q0: {start_state}\n")
        f.write(f"qf: {', '.join(sorted(final_states))}\n\n")

        f.write("d:\n")
        for state, trans in transitions.items():
            for symbol, next_states in trans.items():
                for ns in next_states:
                    f.write(f"d({state}, '{symbol}') -> {ns}\n")

def main(input_file, output_file):
    grammar, macros = parse_grammar(input_file)
    transitions, states, alphabet, start_state, finals = grammar_to_fa(grammar, macros)
    write_fa(output_file, transitions, states, alphabet, start_state, finals)
    print(f"FA successfully generated and saved to {output_file}")

if __name__ == "__main__":
    if len(sys.argv) >= 3:
        main(sys.argv[1], sys.argv[2])
    else:
        print("Error: Script should be called 'python converter.py input.txt output.txt'")
