#include "../number-theory/modular-arithmetic/mod-base.cpp"

const int ORDER = 3;

struct Matrix {
    int n;     // order (number of rows and columns) of the square matrix
    vector<vector<MB>> e;
    Matrix (int k, int n = ORDER) : n(n), e(n, vector<MB>(n)) {
        for (int i = 0; i < n; i++) e[i][i] = k;
    }   // initialized as kI := identity matrix scaled by k
    Matrix operator* (const Matrix& a) {   // matrix-matrix multiplication
        Matrix p(0, n);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) p.e[i][j] += e[i][k]*a.e[k][j];
        return p;
    }
    vector<MB> operator* (const vector<MB>& v) {  // vector-matrix multiplication
        vector<MB> u(n);
        for (int i = 0; i < n; i++) for (int k = 0; k < n; k++)
            u[i] += e[i][k]*v[k];
        return u;
    }
    MB& operator() (int i, int j) { return e[i][j]; }
};

/* How to initialize a matrix:
    Matrix m(0, 2);
    m.e[0] = {2, -1};
    m.e[1] = {1, 1};
*/