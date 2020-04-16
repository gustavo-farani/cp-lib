template<class T>
T get (int i);  // TODO

template<class T>
int search (int l, int r) {
    if (r - l < 3) {
        int m = l;
        T x = get(m);
        for (int i = l + 1; i <= r; i++) {
            T y = get(i);
            if (x < y) {
                x = y;
                m = i;
            }
        }
        return m;
    } else {
        int m1 = l + (r - l)/3;
        int m2 = r - (r - l)/3;
        if (get(m1) < get(m2)) {
            return search(m1, r);
        } else if (get(m2) < get(m1)) {
            return search(l, m2);
        } else {
            return search(m1, m2);
        }
    }
}