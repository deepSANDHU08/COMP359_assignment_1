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
#include<fstream>    // To read from and wreite to files in storage. 
#include<algorithm>  // required for standard algorithms 
#include<bitset>     // required for manipulating bits, assigns 1 if an element in a subset, asigns 0 if element is not there in a subset.
#include<vector>

using Set = std::bitset<6>;
static const char elements[6] = {'a','b','c','d','e','f'};