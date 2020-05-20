#include "../../number-theory/modular-arithmetic/mod-base.cpp"

// implements Pòlya Enumeration Theorem's formula
// n: number of positions in each permutation
// m: number of possible values for each position
// g: group of all invariant (change the represetation,
// but not the object) n-permutations in 0-based indexation
// return: number of equivalence classes (distinct objects)
MB polya (MB n, MB m, const vector<vi>& g) {
    MB sum = 0;
    vector<bool> mark(n);
    for (auto& p : g) {
        int cycles = 0;
        fill(mark.begin(), mark.end(), false);
        for (int i = 0; i < n; i++) {
            if (!mark[i]) {
                cycles++;
                int j = i;
                do {
                    mark[j] = true;
                    j = p[j];
                } while (j != i);
            }
        }
        sum += fastExp(m, cycles);
    }
    return sum/MB(g.size());
}