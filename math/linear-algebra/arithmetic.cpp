#include "matrix.cpp"

// a: matrix with M rows and N columns
// x: vector with N entries
// return a*x
// time complexity: O(M*N)
VR operator* (const MX& a, const VR& x) {
    VR y(a.m);
    for (int i = 0; i < a.m; i++) {
        for (int j = 0; j < a.n; j++) y[i] += a[i][j]*x[j];
    }
    return y;
}

// a: matrix with M rows and N columns
// b: matrix with N rows and O columns
// return a*b
// time complexity: O(M*N*O)
MX operator* (const MX& a, const MX& b) {
    MX c(a.m, b.n);
    for (int i = 0; i < a.m; i++) {
        for (int j = 0; j < b.n; j++) {
            for (int k = 0; k < a.n; k++) {
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    return c;
}

MX operator* (const MX& a, ld k) {
    MX b(a.m, a.n);
    for (int i = 0; i < a.m; i++) {
        for (int j = 0; j < a.n; j++) b[i][j] = k*a[i][j];
    }
    return b;
}

// a: matrix with M rows and N columns
// b: matrix with M rows and N columns
// return a + b
// time complexity: O(M*N)
MX operator+ (const MX& a, const MX& b) {
    MX c(a.m, a.n);
    for (int i = 0; i < c.m; i++) {
        for (int j = 0; j < c.n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}