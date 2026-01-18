U = {"a","b","c","d","e","f"}

A = {"a","c"}
B = {"a","c","e"}

def lessEqual(A,B):
    return A.Issubset(B)

def strictLess(A,B):
    # means A is a subset of B
    return A.Issubset(B) and A != B

def incomprable(A,B):
    return (not A.Issubset(B)) and (not B.Issubset(A))

print(lessEqual({"a"},{"a","b"}))  #true
print(strictLess({"a","b"},{"a",}))  #false 
print(incomprable({"a"},{"c"}))   # true (incomprable)
print(incomprable({"a"},{"a","c"})) #false 
