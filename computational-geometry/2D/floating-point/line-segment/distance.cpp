#include "../line/sort.cpp"
#include "../vector/comparison.cpp"

// distance to line segment a-b from point p
ld dist (PT a, PT b, PT p) {
    if (!(a == b)) {
        Line l(a, b);
        LineSort compProj{l};
        if (compProj(a, p) && compProj(p, b)) return l.dist(p);
    }
    return min(abs(p - a), abs(p - b));
}

// distance between line segments a-b and c-d
ld dist (PT a, PT b, PT c, PT d) {
    if (sgn(orient(c, d, a))*sgn(orient(c, d, b)) < 0
    && sgn(orient(a, b, c))*sgn(orient(a, b, d)) < 0) {
        return 0;
    } else {
        return min({dist(c, d, a), dist(c, d, b),
        dist(a, b, c), dist(a, b, d)});
    }
}