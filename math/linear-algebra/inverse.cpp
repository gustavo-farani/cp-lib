#include "mirror.cpp"

//FROM-FILE:math/linear-algebra/inverse.cpp
// a: square matrix of order N
// return: inverse matrix of a
// throws an exception, if a is singular
// time complexity: O(N^3)
MX inverse (MX& a) {
    MX b = identity(a.n);
    if (mirror(a, b).size() < a.n) {
        throw -1;  // has no inverse
    } else {
        return b;
    }
}