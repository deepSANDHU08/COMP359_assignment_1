# U = {"a","b","c","d","e","f"}

# A = {"a","c"}
# B = {"a","c","e"}

# def lessEqual(A,B):
    # return A.issubset(B)

# def strictLess(A,B):
    # means A is a subset of B
    # return A.issubset(B) and A != B

# def incomprable(A,B):
    # return (not A.issubset(B)) and (not B.issubset(A))

# print(lessEqual({"a"},{"a","b"}))  #true
# print(strictLess({"a","b"},{"a",}))  #false 
# print(incomprable({"a"},{"c"}))   # true (incomprable)
# print(incomprable({"a"},{"a","c"})) #false '''

from itertools import combinations
import matplotlib.pyplot as plt

# Universe
U = ["a", "b", "c", "d", "e", "f"]

# Step 1: Build levels (power set grouped by size)
def levels(U):
    L = []
    for k in range(len(U) + 1):
        level_k = []
        for comb in combinations(U, k):
            level_k.append(frozenset(comb))
        L.append(level_k)
    return L

L = levels(U)

# Step 2: Build Hasse edges (cover relations)
def hasse_edges(L):
    edges = []
    for k in range(len(L) - 1):
        for A in L[k]:
            for B in L[k + 1]:
                if A.issubset(B):
                    edges.append((A, B))
    return edges

E = hasse_edges(L)
print("Number of edges:", len(E))  # should be 192 for |U|=6

# Step 3: Assign node positions (centered per level)
def node_position(L):
    pos = {}
    for k, level in enumerate(L):
        for i, S in enumerate(level):
            x = i - (len(level) - 1) / 2   # center each level
            y = k
            pos[S] = (x, y)
    return pos

pos = node_position(L)

# Step 4: Draw Hasse diagram
plt.figure(figsize=(10, 6))

# Draw edges
for (A, B) in E:
    x1, y1 = pos[A]
    x2, y2 = pos[B]
    plt.plot([x1, x2], [y1, y2], linewidth=1)

# Draw nodes
xs = []
ys = []
for (x, y) in pos.values():
    xs.append(x)
    ys.append(y)

plt.scatter(xs, ys, s=40)

plt.yticks(range(len(L)))
plt.xlabel(" ")
plt.ylabel("Subset size (level)")
plt.title("Hasse Diagram of P(U) under ⊆")

plt.show()









