#include "polygon.cpp"

ld shoelace (const Polygon& p) {
    ld sum = 0;
    for (int i = 0; i < p.sides; i++) sum += p[i] ^ p[i + 1];
    return sum;
}

// works either for concave or convex polygons
ld area (const Polygon& p) { return abs(shoelace(p))/2.0; }