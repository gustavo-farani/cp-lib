#include "polygon.cpp"
#include "../../../../problem-solving-paradigms/binary-search/monotonically-decreasing.cpp"
#include "../line/line-segment.cpp"

// localizes point q with relation to this polygon
// returns 0, if q lies outside the polygon
// returns 1, if q lies on the boundaries of the polygon (on some edge or vertex)
// returns 2, if q lies strictly inside the polygon
// complexity: O(lg(sides))
// polygon must be convex, with vertices listed counterclockwise
int Polygon::contains (const PT& q) {
    if (sides == 1) {
        return p[0] == q;
    } else if (sides == 2) {
        return LineSegment::contains(p[0], p[1], q);
    } else {
        PT u = q - p[0], v = p[1] - p[0], w = p[sides - 1] - p[0];
        if (gt0(v % u) && gt0(u % w)) {
            int i = search(1, sides - 2, [&] (int i) {
                return gt0((p[i] - p[0]) % u);
            });
            ld c = (p[i + 1] - p[i]) % (q - p[i]);
            if (eq0(c)) return 1;
            else if (c > 0) return eq0(u % v) || eq0(u % w) ? 1 : 2;
        }
        return 0;
    }
}