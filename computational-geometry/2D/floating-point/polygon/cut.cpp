#include <vector>
#include "../vector/point.cpp"
#include "../line/vector-form.cpp"
using namespace std;

// whether points a and b are in separate half-planes w.r.t. this line
bool Line::oppose (const PT& a, const PT& b) const {
    return !contains(a) && !contains(b)
    && lt0((a - p ^ d)*(b - p ^ d));
}

// cuts the part of this convex (fails if concave)
// polygon situated in the counter-clock-wise
// half-plane w.r.t. the direction vector of line l
Polygon Polygon::cut (const Line& l) const {
    vector<PT> q;
    for (int i = 0; i < sides; i++) {
        if (ccw(l.d, p[i] - l.p)) q.pb(p[i]);
        if (l.oppose(p[i], p[i + 1])) {
            q.pb(l & Line(p[i], p[i + 1]));
        }
    }
    return Polygon(move(q));
}