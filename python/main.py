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

U = ["a","b","c","d","e","f"]

def levels(U):
    L = []
    for k in range(len(U) + 1): # this will store
        level_k = []
        for comb in combinations(U, k): # for the structure of L
            level_k.append(frozenset(comb))
        L.append(level_k)   # <-- moved outside inner loop
    return L

L = levels(U)

print(len(L))       # should be 6
print(len(L[3]))    # should be 10

def hasse_edges(L):
    edges=[]
    for k in range(len(L)-1):  # from level 0 to level l - 1 
        for A in L[k]:
            for B in L[k+1]:
                if A.issubset(B):
                    edges.append((A,B))
    return edges

E = hasse_edges(L)

print("Number of edges:", len(E))

print("First 10:")
for i in range(10):
    print(E[i][0]), "--->", E[i][1]