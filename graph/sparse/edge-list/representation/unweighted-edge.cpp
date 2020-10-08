struct Edge {      // Unweighted Edge
    int from, to;
    Edge (int u, int v) : from(u), to(v) {}
    int other (int u) { return u ^ from ^ to; }
};