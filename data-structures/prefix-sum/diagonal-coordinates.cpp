#include "../../boilerplate.cpp"

struct DiagonalCoordinates {
    int n, m;
    DiagonalCoordinates (int n, int m) : n(n), m(m) {}
    ii dimensions () { return {n + m - 1, n + m - 1}; }
    // return: unique identifier for the main diagonal
    // where cell (i, j) is placed
    // defined precisely as the Manhattan distance from (0, m - 1),
    // the upper-right corner of the matrix, to cell (i, j)
    int row (int i, int j) { return i + m - j - 1; }
    // return: unique identifier for the secondary diagonal
    // where cell (i, j) is placed
    // defined precisely as the Manhattan distance from (0, 0),
    // the upper-left corner of the matrix, to cell (i, j)
    int column (int i, int j) { return i + j; }
};