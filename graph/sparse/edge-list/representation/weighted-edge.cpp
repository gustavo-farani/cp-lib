struct Edge {      // Weighted Edge
    int from, to, weight;
    Edge (int u, int v, int w) : from(u), to(v), weight(w) {}
    bool operator< (const Edge& o) const {
        return weight < o.weight;
    }
    int other (int u) { return u ^ from ^ to; }
};