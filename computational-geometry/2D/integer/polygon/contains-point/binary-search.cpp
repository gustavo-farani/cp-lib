#include "../../line-segment.cpp"
#include "../polygon.cpp"

// Crossing-Number or Cutting-Ray Test
// localizes point q with relation to this polygon
// returns 1, if q lies outside the polygon
// returns 0, if q lies on the boundaries of the polygon (over some edge or vertex)
// returns -1, if q lies strictly inside the polygon
// complexity: O(sides)
// polygon must be simple (non self-intersecting), but may be concave
int Polygon::contains (PT q) {
    bool cn = 0;
    auto half = [&] (PT a) { return a.y >= q.y; };
    auto crossesRay = [&] (PT a, PT b) {
        return (half(a) - half(b))*((q - a) % (b - a)) > 0;
    };
    for (int i = 0; i < sides; i++) {
        if (onSegment(p[i], p[next(i)], q)) return 0;
        cn ^= crossesRay(p[i], p[next(i)]);
    }
    return cn ? -1 : 1;
}