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
