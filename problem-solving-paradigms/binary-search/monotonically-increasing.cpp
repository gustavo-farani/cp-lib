template<class F>
int search (int l, int r, F test) { // 000[1]11
    while (l < r) {
        int m = l + r >> 1;
        if (test(m)) r = m;
        else l = m + 1;
    }
    return test(l) ? l : l + 1;
}