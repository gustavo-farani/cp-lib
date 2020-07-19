#include "cut.cpp"
#include "../line-segment/distance.cpp"
#include "../line/bissector.cpp"
#include "../line/move.cpp"

// largest circle contained inside a CONVEX polygon
// complexity: O(N^3)
Circle Polygon::largestCircle () {
    Circle ans;
    for (int i = 0; i < sides; i++) {
        Polygon pol = *this;
        Line my = Line(p[i], p[next(i)]);
        for (int j = 0; j < sides; j++) {
            if (i == j) continue;
            Line your = Line(p[j], p[next(j)]);
            if (sgn(cross(my.v, your.v)) == 0) {
                Line l = my;
                l.translate((your.proj(p[i]) - p[i])/2.0);
                if (sgn(l.side(p[i])) < 0 || sgn(l.side(p[next(i)])) < 0) {
                    l.reverse();
                }
                pol = pol.cut(l);
            } else {
                Line l = intBisector(my, your);
                if (sgn(l.side(p[i])) < 0 || sgn(l.side(p[next(i)])) < 0) {
                    l.reverse();
                }
                pol = pol.cut(l);
                l = extBisector(my, your);
                if (sgn(l.side(p[i])) < 0 || sgn(l.side(p[next(i)])) < 0) {
                    l.reverse();
                }
                pol = pol.cut(l);
            }
        }
        for (int j = 0; j < pol.sides; j++) {
            double aux = dist(p[i], p[next(i)], pol.p[j]);
            if (aux > ans.r) {
                ans.r = aux;
                ans.c = pol.p[j];
            }
        }
    }
    return ans;
}