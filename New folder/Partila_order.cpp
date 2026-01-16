/*Survey three programming languages for how to implement custom sorting, typically based off a compare function / template of some kind.
  * design a compare function that bestows a partial order on the power set of a set with 6 elements
    * hint: operations for comparing sets
  * visualize the partial ordering as a Hasse diagram*/

// understanding the problem, - in this problem we basically have to define our own rule for deciding 
// when one thing or an element comes before another, Even when every thing is not comparable.
// we are going to assume that we do have a set U wiht 6 elements where U = {a,b,c,d,e,f}.
// The power set will contain all subset of U including the null set {}, which will be 64 elements in total.