import sys
from collections import defaultdict, deque

# ==========================================
# 1. Grammar Representation
# ==========================================
class GrammarContext:
    def __init__(self, filename):
        self.non_terminals = set()
        self.terminals = set()
        self.start_symbol = ""
        self.productions = defaultdict(list)
        self.production_id_map = {}
        self.production_by_id = {}
        self.prod_counter = 1
        
        self._load_grammar(filename)

    def _load_grammar(self, filename):
        try:
            with open(filename, 'r') as f:
                lines = f.readlines()
        except FileNotFoundError:
            print(f"Error: Grammar file '{filename}' not found.")
            sys.exit(1)

        is_reading_prods = False

        for line in lines:
            line = line.strip()
            if not line: continue

            if line.startswith("N ="):
                self.non_terminals = set(line.split("=", 1)[1].strip().split())
            elif line.startswith("E ="):
                self.terminals = set(line.split("=", 1)[1].strip().split())
            elif line.startswith("S ="):
                self.start_symbol = line.split("=", 1)[1].strip()
            elif line.startswith("P ="):
                is_reading_prods = True
            elif is_reading_prods and "->" in line:
                lhs, rhs_str = line.split("->")
                lhs = lhs.strip()
                rhs = rhs_str.strip().split()
                
                self.productions[lhs].append(rhs)
                self.production_id_map[(lhs, tuple(rhs))] = self.prod_counter
                self.production_by_id[self.prod_counter] = (lhs, rhs)
                self.prod_counter += 1

        for lhs, rhs_list in self.productions.items():
            for rhs in rhs_list:
                for symbol in rhs:
                    if symbol not in self.non_terminals and symbol != 'epsilon':
                        self.terminals.add(symbol)

# ==========================================
# 2. LL(1) Logic
# ==========================================
class LL1Analyzer:
    def __init__(self, grammar):
        self.g = grammar
        self.first = defaultdict(set)
        self.follow = defaultdict(set)
        self.parse_table = {}
        self.conflict_flag = False

        self._build_first()
        self._build_follow()
        self._build_parsing_table()

    def _get_seq_first(self, sequence):
        res = set()
        if not sequence:
            res.add('epsilon')
            return res

        first_sym = sequence[0]
        if first_sym == 'epsilon':
            res.add('epsilon')
        elif first_sym in self.g.terminals:
            res.add(first_sym)
        elif first_sym in self.g.non_terminals:
            res.update(self.first[first_sym])
            if 'epsilon' in self.first[first_sym]:
                remaining = self._get_seq_first(sequence[1:])
                res.update(remaining)
                if 'epsilon' not in remaining:
                    res.discard('epsilon')
        return res

    def _build_first(self):
        for nt in self.g.non_terminals:
            self.first[nt] = set()

        changed = True
        while changed:
            changed = False
            for lhs, rhs_list in self.g.productions.items():
                for rhs in rhs_list:
                    rhs_first = self._get_seq_first(rhs)
                    before_len = len(self.first[lhs])
                    self.first[lhs].update(rhs_first)
                    if len(self.first[lhs]) != before_len:
                        changed = True

    def _build_follow(self):
        for nt in self.g.non_terminals:
            self.follow[nt] = set()
        self.follow[self.g.start_symbol].add('$')

        changed = True
        while changed:
            changed = False
            for lhs, rhs_list in self.g.productions.items():
                for rhs in rhs_list:
                    for i, symbol in enumerate(rhs):
                        if symbol in self.g.non_terminals:
                            beta = rhs[i+1:]
                            beta_first = self._get_seq_first(beta)
                            start_len = len(self.follow[symbol])
                            self.follow[symbol].update(beta_first - {'epsilon'})
                            if not beta or 'epsilon' in beta_first:
                                self.follow[symbol].update(self.follow[lhs])
                            if len(self.follow[symbol]) != start_len:
                                changed = True

    def _build_parsing_table(self):
        for lhs, rhs_list in self.g.productions.items():
            for rhs in rhs_list:
                prod_id = self.g.production_id_map[(lhs, tuple(rhs))]
                first_of_rhs = self._get_seq_first(rhs)
                for term in first_of_rhs:
                    if term != 'epsilon':
                        self._insert_table(lhs, term, prod_id)
                if 'epsilon' in first_of_rhs:
                    for term in self.follow[lhs]:
                        self._insert_table(lhs, term, prod_id)

    def _insert_table(self, nt, t, prod_id):
        key = (nt, t)
        if key in self.parse_table:
            if self.parse_table[key] != prod_id:
                print(f"[CONFLICT] At ({nt}, {t}): Rules {self.parse_table[key]} and {prod_id}")
                self.conflict_flag = True
        else:
            self.parse_table[key] = prod_id

# ==========================================
# 3. Parsing & Tree
# ==========================================
class ParseNode:
    def __init__(self, symbol):
        self.symbol = symbol
        self.index = 0
        self.child_nodes = []
        self.parent = None

class SyntaxParser:
    def __init__(self, analyzer, sequence_file):
        self.ana = analyzer
        self.output_band = [] 
        self.sequence = self._load_sequence(sequence_file)

    def _load_sequence(self, filename):
        try:
            with open(filename, 'r') as f:
                # Read entire file and split by whitespace (works for both newlines and spaces)
                content = f.read()
                return content.split()
        except FileNotFoundError:
            print(f"Error: Sequence file '{filename}' not found.")
            return []

    def parse(self):
        input_stack = self.sequence + ['$']
        work_stack = [self.ana.g.start_symbol, '$']
        
        while True:
            top_input = input_stack[0]
            top_work = work_stack[0]

            if top_input == '$' and top_work == '$':
                return True

            if top_work == top_input:
                input_stack.pop(0)
                work_stack.pop(0)
            elif (top_work, top_input) in self.ana.parse_table:
                prod_id = self.ana.parse_table[(top_work, top_input)]
                self.output_band.append(prod_id)
                lhs, rhs = self.ana.g.production_by_id[prod_id]
                work_stack.pop(0)
                if rhs != ['epsilon']:
                    for sym in reversed(rhs):
                        work_stack.insert(0, sym)
            else:
                print(f"Syntax Error at token: '{top_input}'. Expected one of: {self._get_expected(top_work)}")
                return False

    def _get_expected(self, nt):
        return [t for (n, t) in self.ana.parse_table if n == nt]

class TreeFormatter:
    def __init__(self, grammar, production_ids):
        self.g = grammar
        self.prod_ids = production_ids
        self.root = None

    def build_tree(self):
        iterator = iter(self.prod_ids)
        self.root = self._recursive_build(self.g.start_symbol, iterator)
        self._assign_indexes_bfs()
        return self.root

    def _recursive_build(self, current_sym, iterator):
        node = ParseNode(current_sym)
        if current_sym in self.g.terminals or current_sym == 'epsilon':
            return node

        try:
            prod_id = next(iterator)
        except StopIteration:
            return node

        lhs, rhs = self.g.production_by_id[prod_id]
        if rhs == ['epsilon']:
            child = ParseNode('epsilon')
            child.parent = node
            node.child_nodes.append(child)
        else:
            for sym in rhs:
                child = self._recursive_build(sym, iterator)
                child.parent = node
                node.child_nodes.append(child)
        return node

    def _assign_indexes_bfs(self):
        q = deque([self.root])
        idx = 1
        while q:
            curr = q.popleft()
            curr.index = idx
            idx += 1
            for child in curr.child_nodes:
                q.append(child)

    def print_table(self):
        print(f"\n{'Index':<10} {'Symbol':<20} {'Father':<10} {'Sibling':<10}")
        print("-" * 55)
        q = deque([self.root])
        while q:
            curr = q.popleft()
            father_idx = curr.parent.index if curr.parent else 0
            sibling_idx = 0
            if curr.parent:
                siblings = curr.parent.child_nodes
                try:
                    my_pos = siblings.index(curr)
                    if my_pos + 1 < len(siblings):
                        sibling_idx = siblings[my_pos + 1].index
                except ValueError:
                    pass
            print(f"{curr.index:<10} {curr.symbol:<20} {father_idx:<10} {sibling_idx:<10}")
            for child in curr.child_nodes:
                q.append(child)

# ==========================================
# 4. Main Execution
# ==========================================
if __name__ == "__main__":
    
    # ---------------------------------------------------------
    # REQUIREMENT 1: Seminar Grammar + seq.txt -> Production String
    # ---------------------------------------------------------
    print("\n" + "="*60)
    print(" REQUIREMENT 1: SEMINAR GRAMMAR & SEQUENCE")
    print("="*60)
    
    # 1. Load Grammar
    g_sem = GrammarContext("seminar_grammar.txt")
    ll1_sem = LL1Analyzer(g_sem)
    
    if ll1_sem.conflict_flag:
        print("[FAIL] Seminar Grammar is not LL(1).")
    else:
        print("[OK] Seminar Grammar is LL(1). Parsing 'seq.txt'...")
        # 2. Parse File 'seq.txt'
        parser_sem = SyntaxParser(ll1_sem, "seq.txt")
        result_sem = parser_sem.parse()
        
        if result_sem:
            print("Sequence parsed successfully!")
            print(f"Output (Production String): {parser_sem.output_band}")
        else:
            print("Failed to parse seminar sequence.")


    # ---------------------------------------------------------
    # REQUIREMENT 2: DSL Grammar + pif.txt -> Parsing Tree Table
    # ---------------------------------------------------------
    print("\n" + "="*60)
    print(" REQUIREMENT 2: DSL GRAMMAR & PIF")
    print("="*60)

    # 1. Load Grammar
    g_dsl = GrammarContext("dsl_grammar.txt")
    ll1_dsl = LL1Analyzer(g_dsl)
    
    if ll1_dsl.conflict_flag:
        print("[FAIL] DSL Grammar is not LL(1). Fix conflicts.")
    else:
        print("[OK] DSL Grammar is LL(1). Parsing 'pif.txt'...")
        # 2. Parse File 'pif.txt'
        parser_dsl = SyntaxParser(ll1_dsl, "pif.txt")
        result_dsl = parser_dsl.parse()
        
        if result_dsl:
            print("PIF parsed successfully!")
            # 3. Build and Print Table
            print("\nParsing Tree (Father - Sibling Relation):")
            tree = TreeFormatter(g_dsl, parser_dsl.output_band)
            tree.build_tree()
            tree.print_table()
        else:
            print("Failed to parse PIF.")