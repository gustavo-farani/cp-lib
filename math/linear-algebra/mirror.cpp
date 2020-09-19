#include "matrix.cpp"

// a: matrix with M rows and N columns
// transform a to the reduced-row echelon form,
// applying the same elementary operations to b
// return: columns of pivots of lines [0, rank)
// time complexity: O(M*N*N)
template<class T>
vi mirror (MX& a, T& b) {
    vi p;
    int r = 0;
    for (int j = 0; j < a.n; j++) {
        int k = r;
        while (k < a.m && sgn(a[k][j]) == 0) k++;
        if (k == a.m) continue;
        ld t = a[k][j];
        a[k] /= t;
        b[k] /= t;
        swap(a[k], a[r]);
        swap(b[k], b[r]);
        for (int i = 0; i < a.m; i++) {
            if (i == r || sgn(a[i][j]) == 0) continue;
            t = a[i][j];
            a[r] *= t;
            b[r] *= t;
            a[i] -= a[r];
            b[i] -= b[r];
            a[r] /= t;
            b[r] /= t;
        }
        p.pb(j);
        r++;
    }
    return p;
}