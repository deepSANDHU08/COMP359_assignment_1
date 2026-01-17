/*Survey three programming languages for how to implement custom sorting, typically based off a compare function / template of some kind.
  * design a compare function that bestows a partial order on the power set of a set with 6 elements
    * hint: operations for comparing sets
  * visualize the partial ordering as a Hasse diagram*/

/* ******************************understanding the problem*************************** */
// We need to define our own rule for deciding when one thibng comes before another even when not everything is comparable.
// In this program, we are going to take a set U of 6 elements where U = {a,b,c,d,e,f}, and compare its subsets, using the power set of U.
// total number of subsets of set U is 2^6 = 64

#include<iostream>
#include<string>
#include<fstream>    // To read from and write to files in storage. 
#include<algorithm>  // required for standard algorithms 
#include<bitset>     // required for manipulating bits, assigns 1 if an element in a subset, asigns 0 if element is not there in a subset.
#include<vector>        //

using Subset = std::bitset<6>;
static const char U[6] = {'a','b','c','d','e','f'};

std::string subsetToString (const Subset& s){
    std::string out = "{";
    bool first = true;

    for (int i = 0; i < 6; i++){
        if(s.test(i)) {
            if(!first) out += ",";
            out += U[i];
            first = false;
        }
    }
    out += "}";
    return (out == "{}") ? "∅" : out;

}

/*------------- A is a subset B ?
if A contaons any element that B doesn't it not a subset. 
---------------------------------------------- */
bool isSubsetof(const Subset& A, const Subset& B){
     return (A & ~B).none();
}
/*The Partial order comparison returns one of 4 relationships.*/

enum class Relation {Less, Equal, Greater, Incomparable};

Relation comparePartial(const Subset& A, const Subset& B){
   if (A == B) return Relation::Equal;
   const bool A_in_B = isSubsetof (A,B);
   const bool B_in_A = isSubsetof(B, A);

    if (A_in_B && !B_in_A) return Relation::Less;     // A ⊂ B
    if (B_in_A && !A_in_B) return Relation::Greater;  // B ⊂ A

    return Relation::Incomparable; 

}
/* Temporary main to test this section */
int main() {
    Subset A, B;

    A.set(0); // {a}
    B.set(0);
    B.set(1); // {a,b}

    std::cout << "A = " << subsetToString(A) << "\n";
    std::cout << "B = " << subsetToString(B) << "\n";

    Relation r = comparePartial(A, B);

    if (r == Relation::Less)
        std::cout << "A is a subset of B\n";
    else if (r == Relation::Greater)
        std::cout << "B is a subset of A\n";
    else if (r == Relation::Equal)
        std::cout << "A equals B\n";
    else
        std::cout << "A and B are incomparable\n";

    return 0;
}