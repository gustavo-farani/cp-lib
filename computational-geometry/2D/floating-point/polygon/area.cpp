#include <cmath>
#include "polygon.cpp"

// works either for concave or convex polygons
ld Polygon::area () const {
    ld sum = 0;
    for (int i = 0; i < sides; i++) sum += p[i] ^ p[i + 1];
    return abs(sum)/2.0;
}