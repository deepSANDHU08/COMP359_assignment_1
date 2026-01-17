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
/* Temporary main to test this section 
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
} */
/* -----------------------------
   Sorting needs a total order.
   We'll respect subset order when possible, otherwise tie-break:
     1) smaller size first
     2) smaller bit-pattern value
   ----------------------------- */
bool totalOrderLess(const Subset& A, const Subset& B) {
    if (A == B) return false;

    Relation r = comparePartial(A, B);
    if (r == Relation::Less) return true;
    if (r == Relation::Greater) return false;

    // Incomparable: decide using tie-break rules
    if (A.count() != B.count()) return A.count() < B.count();
    return A.to_ulong() < B.to_ulong();
}
/* -----------------------------
   Generate all subsets of U.
   We loop over all 6-bit patterns (0..63) and convert each to a bitset.
   ----------------------------- */

std::vector<Subset> generatePowerSet(){
    std::vector<Subset> subsets;
    subsets.reserve(64);

    for(int x=0; x < 64; ++x){
        Subset s;
        for(int i=0; i < 6; ++i){
            if(x & (1<<i)) s.set(i);
        }
        subsets.push_back(s);
    }
    return subsets;
}
/* Test output up to here 
int main() {
    auto subsets = generatePowerSet();

    std::cout << "Total subsets: " << subsets.size() << "\n\n";
    std::cout << "First 10 subsets (unsorted):\n";
    for (int i = 0; i < 10; i++) {
        std::cout << i << ": " << subsetToString(subsets[i])
                  << "  size=" << subsets[i].count() << "\n";
    }

    // Optional: show sorted first 10
    std::sort(subsets.begin(), subsets.end(), totalOrderLess);
    std::cout << "\nFirst 10 subsets (sorted):\n";
    for (int i = 0; i < 10; i++) {
        std::cout << i << ": " << subsetToString(subsets[i])
                  << "  size=" << subsets[i].count() << "\n";
    }

    return 0; 
}*/

/*-------------------------------
for Graphviz nodes, upto 63 
we do need to convert a subset bitset back to 0 to 63 id.
*/
int idof(const Subset& s){
    int id = 0;
    for (int i = 0; i <6; ++i){
        if (s.test(i)) id |= (1<<i);
    }
     return id;
}
/*--------------------------------------
Hasse edge (cover relations):
A -> B if B = A plus exactly one new element
-----------------------------------*/
std::vector<std::pair<int,int>> makeHasseEdges(const std::vector<Subset>& subs){
    std::vector<std::pair<int,int>> Edges;

    for(int a = 0; a < (int)subs.size(); ++a){
        const Subset& A = subs[a];

        for (int i = 0; i < 6; ++i){
            if(!A.test(i)){
                Subset B = A;
                B.set(i);
                Edges.push_back({a, idof(B)});
            }
        }
    }
    return Edges;
}
/*--------------------
Write Graphviz DOT file:
nodes groupped by level (subset size)
edges are hasse cover relations
---------------------------*/
void writeDot(const std::vector<Subset>& subs,
               const std::vector<std::pair<int,int>>& edges,
               const std::string& result){

        std::ofstream out(result);

        out<< "digraph hasse{\n";
        out<< " rankdir=BT;\n";
        out<< " node[shape=box, fontsize=10];\n\n";

         // Nodes
    for (int i = 0; i < (int)subs.size(); ++i) {
        out << "  S" << i << " [label=\"" << pretty(subs[i]) << "\"];\n";
    }
    out << "\n";

    // Levels (rank by subset size)
    for (int k = 0; k <= 6; ++k) {
        out << "  { rank=same; ";
        for (int i = 0; i < (int)subs.size(); ++i) {
            if ((int)subs[i].count() == k) out << "S" << i << "; ";
        }
        out << "}\n";
    }
    out << "\n";

    // Edges
    for (auto [a,b] : edges) {
        out << "  S" << a << " -> S" << b << ";\n";
    }

    out << "}\n";
        
               } 