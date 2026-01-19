# Hasse diagram for P(U) where U = {a,b,c,d,e,f}
# We represent each subset using a 6-bit number (0..63).
# Bit i = 1 means U[i] is in the subset.

U = ["a", "b", "c", "d", "e", "f"]

def subset_to_string(mask):
    # Convert a bitmask into something like {a,c,e} or ∅
    result = []
    for i in range(6):
        if mask & (1 << i):
            result.append(U[i])

    if len(result) == 0:
        return "∅"
    return "{" + ",".join(result) + "}"

def is_subset(A, B):
    # A is a subset of B if A has no element that B doesn't have
    # same idea as: (A & ~B) == 0
    return (A & (~B)) == 0

def generate_power_set():
    subsets = []
    for mask in range(64):   # 2^6 = 64
        subsets.append(mask)
    return subsets

def make_hasse_edges(subsets):
    # Cover relation: A -> B if B is A plus exactly one new element
    edges = []

    for A in subsets:
        for i in range(6):
            if (A & (1 << i)) == 0:     # element i is not in A
                B = A | (1 << i)        # add element i
                edges.append((A, B))

    return edges

# -------------------- test run --------------------
subsets = generate_power_set()
edges = make_hasse_edges(subsets)

print("Total subsets:", len(subsets))   # should be 64
print("Total edges:", len(edges))       # should be 192

print("\nFirst 10 subsets:")
for m in subsets[:10]:
    print(m, "=", subset_to_string(m))

print("\nFirst 10 edges:")
for (A, B) in edges[:10]:
    print(subset_to_string(A), "->", subset_to_string(B))

def write_dot(subsets, edges, filename):
    # Write a Graphviz DOT file for the Hasse diagram
    out = open(filename, "w", encoding="utf-8")

    out.write("digraph hasse {\n")
    out.write("  rankdir=BT;\n")
    out.write("  node [shape=box, fontsize=10];\n\n")

    # Nodes
    for s in subsets:
        out.write('  S' + str(s) + ' [label="' + subset_to_string(s) + '"];\n')
    out.write("\n")

    # Levels (rank by subset size)
    for k in range(7):  # sizes 0..6
        out.write("  { rank=same; ")
        for s in subsets:
            if bin(s).count("1") == k:
                out.write("S" + str(s) + "; ")
        out.write("}\n")
    out.write("\n")

    # Hasse edges (cover relations)
    for (A, B) in edges:
        out.write("  S" + str(A) + " -> S" + str(B) + ";\n")

    out.write("}\n")
    out.close()

if __name__ == "__main__":

    subsets = generate_power_set()
    edges = make_hasse_edges(subsets)

    print("Total subsets:", len(subsets))   # should be 64
    print("Total edges:", len(edges))       # should be 192

    write_dot(subsets, edges, "hasse_b6.dot")
    print("Hasse diagram written to hasse_b6.dot")

