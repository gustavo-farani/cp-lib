#include "mirror.cpp"

// finds one valid solution, even when there are infinite ones
// if the system is inconsistent, throws an exception
VR anySolution (MX& a, VR& b) {
    vi p = mirror(a, b);
    int r = p.size();
    for (int i = r; i < a.m; i++) {
        if (sgn(b[i]) != 0) {
            throw 0;  // no solution
        }
    }
    VR ans(a.n);
    for (int i = 0; i < r; i++) ans[p[i]] = b[i];
    return ans;
}

VR allSolutions (MX& a, VR& b) {
    vi p = mirror(a, b);
    int r = p.size();
    for (int i = r; i < a.m; i++) {
        if (sgn(b[i]) != 0) {
            throw 0;  // no solution
        }
    }
    VR v(a.n);
    for (int i = 0; i < r; i++) v[p[i]] = b[i];
    if (r == a.n) {  // unique solution
        return v;  
    } else {  // infinite solutions
        MX t(a.n, a.n - r);
        int z = 0;
        vi f;
        for (int j = a.n; j--;) {
            if (!p.empty() && p.back() == j) {
                p.pop_back();
                for (int k = 0; k < z; k++) {
                    t[j][k] = -a[p.size()][f[k]];
                }
            } else {
                t[j][z++] = 1;
                f.pb(j);
            }
        }
        // all solutions will have the form t*u + v,
        // u an arbitrary vector with a.n - r entries
        throw make_pair(t, v);
    }
}