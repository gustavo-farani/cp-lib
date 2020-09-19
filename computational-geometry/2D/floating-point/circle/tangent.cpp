#include "circle.cpp"
#include "../vector/orthogonality.cpp"

// computes the points of tangency of this circle
// with the lines passing through p
// assumes p is out of the region covered by this circle
pair<PT, PT> Circle::pointsOfTangency (PT p) {
    PT d = p - c;
    ld d2 = dot(d, d), h2 = d2 - r*r;
    PT u = (d*r - perp(d)*sqrt(h2))/d2;
    PT v = (d*r + perp(d)*sqrt(h2))/d2;
    return {c + u*r, c + v*r};
}

// computes the points of tangency of this circle
// with the inner lines that are tangent to the other circle too
// assumes the circle regions do not overlap
pair<PT, PT> Circle::innerPointsOfTangency (Circle o) {
    PT d = o.c - c;
    ld dr = r + o.r, d2 = dot(d, d), h2 = d2 - dr*dr;
    PT u = (d*dr - perp(d)*sqrt(h2))/d2;
    PT v = (d*dr + perp(d)*sqrt(h2))/d2;
    return {c + u*r, c + v*r};
}

// computes the points of tangency of this circle
// with the outer lines that are tangent to the other circle too
// assumes the circle regions do not overlap
pair<PT, PT> Circle::outerPointsOfTangency (Circle o) {
    PT d = o.c - c;
    ld dr = r - o.r, d2 = dot(d, d), h2 = d2 - dr*dr;
    PT u = (d*dr - perp(d)*sqrt(h2))/d2;
    PT v = (d*dr + perp(d)*sqrt(h2))/d2;
    return {c + u*r, c + v*r};
}