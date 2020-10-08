#include "bridges.cpp"
#include "../../../../data-structures/disjoint-sets-union/disjoint-sets-count.cpp"

// partitioning the vertices of the graph according to equivalence relation:
// u R v iff no edge in the graph could be removed to disconnect u and v
// alternative: u R v iff u == v or there is a simple cycle covering u and v
DSU bridgeComponents (Graph& g) {
    bridges(g);
    DSU er(g.last);
    for (auto e : g.edges) {
        if (!e->bridge) er.merge(e->from, e->to);
    }
    return er;
}