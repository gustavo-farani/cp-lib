#include "matrix.cpp"

// a: square matrix of order N
// return det(a), it may be zero
// time complexity: O(N^3)
ld determinant (MX& a) {
    int r = 0;
    ld det = 1.0L;
    for (int j = 0; j < a.n; j++) {
        int k = r;
        while (k < a.m && sgn(a[k][j]) == 0) k++;
        if (k == a.m) continue;
        ld t = a[k][j];
        a[k] /= t;
        det /= t;
        if (k != r) {
            swap(a[k], a[r]);
            det = -det;
        }
        for (int i = 0; i < a.m; i++) {
            if (i == r || sgn(a[i][j]) == 0) continue;
            t = a[i][j];
            a[r] *= t;
            a[i] -= a[r];
            a[r] /= t;
        }
        r++;
    }
    if (r < a.m) det = 0.0L;
    return det;
}