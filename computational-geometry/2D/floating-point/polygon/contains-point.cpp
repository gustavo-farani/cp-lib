#include "polygon.cpp"
#include "../../../../problem-solving-paradigms/binary-search/monotonically-decreasing.cpp"
#include "../line-segment/intersection.cpp"

// localizes point q with relation to this polygon
// returns 1, if q lies outside
// returns 0, if q lies on the boundaries (over an edge or vertex)
// returns -1, if q lies strictly inside
// complexity: O(lg(sides))
// polygon must be convex, with vertices listed counterclockwise
/* includes PT::operator== */
int Polygon::contains (PT q) {
    if (sides == 1) {
        return !(p[0] == q);
    } else if (sides == 2) {
        return !onSegment(p[0], p[1], q);
    } else {
        int l = sgn(orient(p[0], p[sides - 1], q));
        int r = sgn(orient(p[0], p[1], q));
        if (l <= 0 && r >= 0) {
            int i = search(1, sides - 2, [&] (int i) {
                return sgn(orient(p[0], p[i], q)) >= 0;
            });
            int e = sgn(orient(p[i], p[next(i)], q));
            if (e == 0) return 0;
            else if (e > 0) return l == 0 || r == 0 ? 0 : -1;
        }
        return 1;
    }
}

// Crossing-Number Method or Cutting-Ray Test
// localizes point q with relation to this polygon
// returns 1, if p lies outside
// returns 0, if p lies on the boundary (over an edge or vertex)
// returns -1, if q lies strictly inside
// complexity: O(sides)
// polygon must be simple (no self-intersecting), but may be concave
int Polygon::contains (PT q) {
    bool cn = 0;
    auto half = [&] (PT a) { return a.y >= q.y; };
    auto crossesRay = [&] (PT a, PT b) {
        return (half(a) - half(b))*sgn(orient(a, q, b)) > 0;
    };
    for (int i = 0; i < sides; i++) {
        if (onSegment(p[i], p[next(i)], q)) return 0;
        cn ^= crossesRay(p[i], p[next(i)]);
    }
    return cn ? -1 : 1;
}