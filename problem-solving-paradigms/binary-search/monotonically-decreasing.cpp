template<class F>
int search (int l, int r, F test) { // 111[1]00
    r++;
    while (r - l > 1) {
        int m = l + r >> 1;
        if (test(m)) l = m;
        else r = m;
    }
    return test(l) ? l : l - 1;
}