#include "../../boilerplate.cpp"

template<class T>
struct Matrix {
    int n;     // order (number of rows and columns) of square matrix
    vector<vector<T>> a;
    // initializes this matrix as kI := identity matrix scaled by k
    Matrix (int n, int k) : n(n), a(n, vector<T>(n)) {
        for (int i = 0; i < n; i++) a[i][i] = k;
    }
    // matrix-matrix multiplication
    Matrix operator* (const Matrix& o) {
        Matrix p(n, 0);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) p.a[i][j] += a[i][k]*o.a[k][j];
        return p;
    }
    // matrix-vector multiplication
    vector<T> operator* (const vector<T>& v) {
        vector<T> u(n);
        for (int i = 0; i < n; i++) for (int k = 0; k < n; k++)
            u[i] += a[i][k]*v[k];
        return u;
    }
    // exponentiates this matrix to the power of e
    // complexity: O((n^3) lg e)
    // n: order of this matrix
    // e: exponent
    Matrix to (ll e) {
        Matrix p(n, 1), b = *this;
        while (e > 0) {
            if (e & 1) p = p * b;
            b = b * b;
            e >>= 1;
        }
        return p;
    }
    T& operator() (int i, int j) { return a[i][j]; }  // manually inputing
};