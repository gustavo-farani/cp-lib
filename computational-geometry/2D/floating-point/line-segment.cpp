#include "point.cpp"

bool onSegment (PT a, PT b, PT p) {
    return sgn(orient(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

bool segmentsIntersect (PT a, PT b, PT c, PT d) {
    return sgn(orient(c, d, a))*sgn(orient(c, d, b)) < 0
    && sgn(orient(a, b, c))*sgn(orient(a, b, d)) < 0
    || onSegment(c, d, a) || onSegment(c, d, b)
    || onSegment(a, b, c) || onSegment(a, b, d);
}

/* includes PT::operator*, operator/, operator<, operator== */
vector<PT> segmentsIntersection (PT a, PT b, PT c, PT d) {
    vector<PT> v;
    double oa = orient(c, d, a), ob = orient(c, d, b),
    oc = orient(a, b, c), od = orient(a, b, d);
    if (sgn(oa)*sgn(ob) < 0 && sgn(oc)*sgn(od) < 0) {
        v.pb((a*ob - b*oa)/(ob - oa));
    } else {
        if (onSegment(c, d, a)) v.pb(a);
        if (onSegment(c, d, b)) v.pb(b);
        if (onSegment(a, b, c)) v.pb(c);
        if (onSegment(a, b, d)) v.pb(d);
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
    }
    return v;
}

#include "line.cpp"  // + Line::dist, LineSort

/* includes PT::operator== */
double segPointDist (PT a, PT b, PT p) {
    if (!(a == b)) {
        Line l(a, b);
        LineSort compProj{l};
        if (compProj(a, p) && compProj(p, b)) return l.dist(p);
    }
    return min(abs(p - a), abs(p - b));
}

double segmentsDistance (PT a, PT b, PT c, PT d) {
    if (sgn(orient(c, d, a))*sgn(orient(c, d, b)) < 0
    && sgn(orient(a, b, c))*sgn(orient(a, b, d)) < 0) {
        return 0;
    } else {
        return min({segPointDist(c, d, a), segPointDist(c, d, b),
        segPointDist(a, b, c), segPointDist(a, b, d)});
    }
}