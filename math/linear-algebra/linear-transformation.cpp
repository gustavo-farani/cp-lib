#include "mirror.cpp"

MX transp (const MX& a) {
    MX t(a.n, a.m);
    for (int i = 0; i < a.m; i++) {
        for (int j = 0; j < a.n; j++) t[j][i] = a[i][j];
    }
    return t;
}

// row of x: argument vectors
// row of y: transformed vectors
// return: matrix of the acting linear transformation
MX linearTransformation (MX& x, MX& y) {
    mirror(x, y);
    return transp(y);
}