import java.util.*;

public class Main {
    
    // Let our base set be U = {1,2,3,4,5,6}, represented by bits 0->5
    // Then the power set P(U) is the set of all subsets of U

    // For this assignment, I will use subset inclusion for partial ordering, defined below
    // A ⊆ B ⟺ (A&B) = A
    static boolean isSubset(int a, int b) {
        return (a&b) == a;
    }

    // One of the tie-breakers for my compare function
    // Returns the cardinality (# of elements in the set)
    static int cardinality(int mask) {
        return Integer.bitCount(mask);
    }

    // Converts each subset's mask into a label
    static String setToString(int mask) {
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        boolean first = true;

        for (int i = 0; i < 6; i++) {
            if ((mask & (1 << i)) != 0) {   // bit i is set
                if (!first) {
                    sb.append(",");
                }
                
                sb.append(i + 1); // element numbers 1..6
                first = false;
            }
        }

        sb.append("}");
        return sb.toString();
    }

    // Assigns proper node names (S0 -> S63) for Graphviz
    static String nodeId(int mask) {
        return "S" + mask;
    }

    // Partial order comparator w/ tie-breaker for sorting
    // Partial order: A <= B ⟺ A ⊆ B
    // Java sorting requires total order, so I will break ties using (1) smaller cardinality then (2) numeric mask order
    static int compareFunc(int a, int b) {
        if(a==b) {
            return 0;
        }

        boolean aSubB = isSubset(a,b);
        boolean bSubA = isSubset(b,a);

        if(aSubB && !bSubA) {
            return -1; // a ⊂ b
        }
        
        if(bSubA && !aSubB) {
            return 1; // b ⊂ a
        }

        // Tie-break
        int cardA = cardinality(a);
        int cardB = cardinality(b);

        if(cardA != cardB) {
            return Integer.compare(cardA,cardB);
        }

        return Integer.compare(a,b);
    }

    // Edges of the Hasse diagram
    // A ≺ B ⟺ A ⊂ B and |B| = |A| + 1
    static List<int[]> hasseEdges() {
        List<int[]> edges = new ArrayList<>();

        for(int a=0; a<64; a++) {
            for(int b=0; b<64; b++) {
                if(a==b) continue;
                if(cardinality(b) == cardinality(a) + 1 && isSubset(a,b)) {
                    edges.add(new int[]{a,b});
                }
            }
        }
        return edges;
    }

    // Hasse diagram visualization
    static String toDot(List<int[]> edges) {
        StringBuilder sb = new StringBuilder();
        sb.append("digraph Hasse {\n");
        sb.append("  rankdir=BT;\n"); // bottom to top

        // Nodes
        for(int m=0; m<64; m++) {
            sb.append("  ").append(nodeId(m)).append(" [label=\"").append(setToString(m)).append("\"];\n");
        }

        // Levels
        for(int k=0; k<=6; k++) {
            sb.append("  {rank=same; ");
            for(int m=0; m<64; m++) {
                if(cardinality(m) == k) {
                    sb.append(nodeId(m)).append("; ");
                }
            }
            sb.append("}\n");
        }

        // Edges
        for(int[] e : edges) {
            sb.append("  ").append(nodeId(e[0])).append(" -> ").append(nodeId(e[1])).append(";\n");
        }

        // Put it all together
        sb.append("}\n");
        return sb.toString();
    }

    public static void main(String[] args) {
        // Step 1: generate all possible subsets for a 6-element set
        List<Integer> subsets = new ArrayList<>();
        for(int mask = 0; mask<64; mask++) {
            subsets.add(mask);
        }

        // Step 2: Sort them using our comparator function
        subsets.sort(Main::compareFunc);

        System.out.println("Sorted subsets: ");
        for(int m : subsets) {
            System.out.printf("%-10s  size=%d  mask=%d%n", setToString(m), cardinality(m), m);
        }

        // Step 3: Build the Hasse diagram
        List<int[]> edges = hasseEdges();

        // Step 4: Output DOT file text for Graphviz
        String dot = toDot(edges);
        System.out.println("\n--- Graphviz DOT for Hasse diagram ---");
        System.out.println(dot);
    }
}