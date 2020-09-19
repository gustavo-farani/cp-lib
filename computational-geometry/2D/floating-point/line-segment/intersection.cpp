#include "../vector/comparison.cpp"

// tests if line-segment a-b onSegment point p
bool onSegment (PT a, PT b, PT p) {
    PT u = p - a, v = p - b;
    return sgn(cross(u, v)) == 0 && sgn(dot(u, v)) <= 0;
}

// tests if line segments a-b and c-d intersect
bool intersect (PT a, PT b, PT c, PT d) {
    return sgn(orient(c, d, a))*sgn(orient(c, d, b)) < 0
    && sgn(orient(a, b, c))*sgn(orient(a, b, d)) < 0
    || onSegment(c, d, a) || onSegment(c, d, b)
    || onSegment(a, b, c) || onSegment(a, b, d);
}

// computes intersection points between line segments a-b and c-d
vector<PT> intersection (PT a, PT b, PT c, PT d) {
    vector<PT> v;
    ld oa = orient(c, d, a), ob = orient(c, d, b),
    oc = orient(a, b, c), od = orient(a, b, d);
    if (sgn(oa)*sgn(ob) < 0 && sgn(oc)*sgn(od) < 0) {
        v.pb((a*ob - b*oa)/(ob - oa));
    } else {
        if (onSegment(c, d, a)) v.pb(a);
        if (onSegment(c, d, b)) v.pb(b);
        if (onSegment(a, b, c)) v.pb(c);
        if (onSegment(a, b, d)) v.pb(d);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    return v;
}