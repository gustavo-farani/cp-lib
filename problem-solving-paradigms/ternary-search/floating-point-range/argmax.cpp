// F: concave function in range (l, r)
template<int MAX = 80, class F>
double argmax (double l, double r, F get) {
    for (int i = 0; i < MAX; i++) {
        double d = (r - l)/3.0, m1 = l + d, m2 = r - d;
        if (get(m1) < get(m2)) l = m1;
        else r = m2;
    }
    return l;
}