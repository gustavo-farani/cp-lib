// F: convex function in range (l, r)
template<int MAX = 80, class F>
double argmin (double l, double r, F get) {
    for (int i = 0; i < MAX; i++) {
        double d = (r - l)/3.0, m1 = l + d, m2 = r - d;
        if (get(m1) < get(m2)) r = m2;
        else l = m1;
    }
    return l;
}