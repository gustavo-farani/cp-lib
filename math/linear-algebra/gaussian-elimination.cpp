#include "matrix.cpp"

// a: matrix with M rows and N columns
// transform a to the canonical form (a.k.a. reduced-row echelon form),
// applying elementary operations
// time complexity: O(M*N*N)
void canonical (MX& a) {
    // defined as: M - number of rows full of zeroes at the bottom
    int rank = 0;
    // pivot[i] := column where the pivot at line i is positioned
    // it holds: pivot[0] < pivot[1] < ... < pivot[rank - 1]
    vi pivot;
    for (int j = 0; j < a.n; j++) {
        int k = rank;
        while (k < a.m && sgn(a[k][j]) == 0) k++;
        // column j has no pivot
        if (k == a.m) continue;
        // scaling the pivot to 1
        a[k] /= a[k][j];
        // lift the pivot up
        swap(a[k], a[rank]);
        for (int i = 0; i < a.m; i++) {
            // zeroing every entry of column j, except for the pivot
            if (i == rank || sgn(a[i][j]) == 0) continue;
            ld t = a[i][j];
            a[rank] *= t;
            a[i] -= a[rank];
            a[rank] /= t;
        }
        pivot.pb(j);  // pivot of line i is positioned at column j
        rank++;
    }
}