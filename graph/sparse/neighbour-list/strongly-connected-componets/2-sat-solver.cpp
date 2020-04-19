#include "kosaraju.cpp"

struct SATSolver {
    int n;
    Graph g;
    SATSolver (int n) : n(n), g(n << 1, 0) {}
    int negation (int p) {
        if (p >= n) return p - n;
        else return p + n;
    }
    void implication (int p, int q) {
        g.addArc(p, q);
        g.addArc(negation(q), negation(p));
    }
    void disjunction (int p, int q) {
        implication(negation(p), q);
    }
    void exclusion (int p, int q) {
        implication(negation(p), q);
        implication(q, negation(p));
    }
    void biconditional (int p, int q) {
        implication(p, q);
        implication(q, p);
    }
    // returns a boolean evalutaion for the n variables
    // satisfying the expression specified
    // raises exception if unsatisfiable
    vector<bool> solve () {
        vi scc(stronglyConnectedComponents(g));
        vector<bool> v(n);
        for (int p = 0; p < n; p++) {
            int q = negation(p);
            if (scc[p] == scc[q]) throw -1;
            else if (scc[q] < scc[p]) v[p] = true;
        }
        return v;
    }
};