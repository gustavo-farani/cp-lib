#include "point.cpp"
#include "../../../problem-solving-paradigms/binary-search/monotonically-decreasing.cpp"
#include "line-segment.cpp"

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (vector<PT>&& v) : sides(v.size()), p(v) {}
    int next (int i) { return i == sides - 1 ? 0 : i + 1; }

    ll shoelace () {
        ll sum = 0;
        for (int i = 0; i < sides; i++) sum += p[i] % p[next(i)];
        return sum;
    }
    bool cw () { return shoelace() < 0; }
    bool ccw () { return shoelace() > 0; }

    // Pick's Theorem
    // computes the number of points with integer coordinates in this polygon
    // polygon must not be self-intersecting
    // boolean parameter border: whether the points lying on the boundary
    // (on edges or vertices) should be counted or not
    ll latticePoints (bool border) {
        ll b = 0;
        for (int i = 0; i < sides; i++) {
            PT v = p[next(i)] - p[i];
            b += abs(gcd(v.x, v.y));  // C++ 17 only
        }
        return ((abs(shoelace()) - b + 2) >> 1) + border*b;
    }

    // localizes point q with relation to this polygon
    // returns 0, if q lies outside the polygon
    // returns 1, if q lies on the boundaries of the polygon (on some edge or vertex)
    // returns 2, if q lies strictly inside the polygon
    // complexity: O(lg(sides))
    // polygon must be convex, with at least 3 vertices, listed counterclockwise
    int contains (PT q) {
        PT u = q - p[0], v = p[1] - p[0], w = p[sides - 1] - p[0];
        if (v % u >= 0 && u % w >= 0) {
            int i = search(1, sides - 2, [&] (int i) {
                return (p[i] - p[0]) % u >= 0;
            });
            ll c = (p[i + 1] - p[i]) % (q - p[i]);
            if (c == 0) return 1;
            else if (c > 0) return u % v == 0 || u % w == 0 ? 1 : 2;
        }
        return 0;
    }

    // Crossing-Number or Cutting-Ray Test
    // localizes point q with relation to this polygon
    // returns 1, if q lies outside the polygon
    // returns 0, if q lies on the boundaries of the polygon (over some edge or vertex)
    // returns -1, if q lies strictly inside the polygon
    // complexity: O(sides)
    // polygon must be simple (non self-intersecting), but may be concave
    int crossingNumber (PT q) {
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
};
