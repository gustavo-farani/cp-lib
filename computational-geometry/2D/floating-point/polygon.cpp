#include "line.cpp"  // oppose, inter -> cut
#include "../../../problem-solving-paradigms/binary-search/monotonically-decreasing.cpp" // -> contains 
#include "line-segment.cpp"  // onSegment -> contains

double area (PT a, PT b, PT c) { return abs(cross(b - a, c - a))/2.0; }

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (const vector<PT>& v) : p(v), sides(v.size()) {}
    int next (int i) { return i == sides - 1 ? 0 : i + 1; }


    // returns 0, if polygon is not simple, or concave
    // returns 1, if polygon is convex, with vertices
    // listed counterclockwise
    // returns -1, if polygon is convex, with vertices
    // listed clockwise
    int isConvex () {
        bool pos = false, neg = false;
        for (int i = 0; i < sides; i++) {
            int j = next(i), k = next(j);
            int s = sgn(orient(p[i], p[j], p[k]));
            neg |= s < 0;
            pos |= s > 0;
        }
        return !(pos && neg) ? pos - neg : 0;
    }


    double shoelace () {
        double sum = 0;
        for (int i = 0; i < sides; i++) sum += cross(p[i], p[next(i)]);
        return sum;
    }
    double area () { return abs(shoelace())/2.0; }
    bool ccw () { return sgn(shoelace()) > 0; }
    bool cw () { return sgn(shoelace()) < 0; }


    // cuts the part of this convex (fails if concave) polygon
    // situated in the counterclockwise half-plane
    // with relation to the directed line l
    Polygon cut (Line l) {
        vector<PT> c;
        for (int i = 0; i < sides; i++) {
            if (sgn(l.side(p[i])) >= 0) c.pb(p[i]);
            if (l.opposes(p[i], p[next(i)])) {
                c.pb(inter(l, Line(p[i], p[next(i)])));
            }
        }
        return c;
    }

    
    // localizes point q with relation to this polygon
    // returns 1, if q lies outside
    // returns 0, if q lies on the boundaries (over an edge or vertex)
    // returns -1, if q lies strictly inside
    // complexity: O(lg(sides))
    // polygon must be convex, with vertices listed counterclockwise
    /* includes PT::operator== */
    int contains (PT q) {
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
    int crossingNumber (PT q) {
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
};