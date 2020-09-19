#include "../circle.cpp"
#include "../../line/line.cpp"
#include "../../vector/orthogonality.cpp"

// counts the number of intersection points between a line and a circumference
int intersect (Circle g, Line l) {
    ld aux = l.side(g.c);
    return 1 + sgn(g.r*g.r - aux*aux/dot(l.v, l.v));
}

// computes the intersection points between a line and a circumference
vector<PT> intersection (Circle g, Line l) {
    vector<PT> ans;
    PT p = l.proj(g.c), a = g.c - p;
    ld d2 = g.r*g.r - dot(a, a);
    int aux = sgn(d2);
    if (aux == 0) {
        ans.pb(p);
    } else if (aux == 1) {
        PT b = l.v/dot(l.v, l.v)*sqrt(d2);
        ans.pb(p - b);
        ans.pb(p + b);
    }
    return ans;
}