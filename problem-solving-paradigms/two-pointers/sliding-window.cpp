namespace TwoPointers {
    const bool B = 0;  // base indexation
    ll state;
    int l, r;
    void init () {
        l = B;
        r = B - 1;
        state = 0;
    }
    void add (int i, bool right) {}
    void remove (int i, bool right) {}
    ll query (int ql, int qr) {
        while (l > ql) add(--l, 0);
        while (r < qr) add(++r, 1);
        while (l < ql) remove(l++, 0);
        while (r > qr) remove(r--, 1);
        return state;
    }
};