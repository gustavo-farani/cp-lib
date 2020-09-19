#include "../circle.cpp"
#include "../../vector/orthogonality.cpp"

// counts the number of intersection points between two circumferences
// NOTE: returns 3 for concentric circumferences with equal radius
int intersect (Circle a, Circle b) {
    PT u = b.c - a.c;
    ld d2 = dot(u, u);
    if (sgn(d2) == 0) {
        return sgn(a.r - b.r) == 0 ? 3 : 0;
    } else {
        ld pd = (d2 + a.r*a.r - b.r*b.r)/2.0L, h2 = a.r*a.r - pd*pd/d2;
        return 1 + sgn(h2);
    }
}

// computes the intersection points between two circumferences
// NOTE: for concentric circumferences, it is returned an empty
// vector of points, even if their radius are equal
vector<PT> intersection (Circle a, Circle b) {
    vector<PT> ans;
    PT u = b.c - a.c;
    ld d2 = dot(u, u);
    if (sgn(d2) != 0) {
        ld pd = (d2 + a.r*a.r - b.r*b.r)/2.0L, h2 = a.r*a.r - pd*pd/d2;
        int aux = sgn(h2);
        if (aux >= 0) {
            PT p = a.c + u*pd/d2;
            if (aux == 0) {
                ans.pb(p);
            } else {
                PT v = perp(u)*sqrt(h2/d2);
                ans.pb(p + v);
                ans.pb(p - v);
            }
        }
    }
    return ans;
}