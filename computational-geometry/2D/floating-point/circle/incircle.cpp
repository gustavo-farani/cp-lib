#include "circle.cpp"
#include "../line/bisector.cpp"
#include "../line/intersection.cpp"

// TO BE TESTED
Circle incircle (PT a, PT b, PT c) {
    Line r(a, b), s(b, c), t(c, a);
    PT p = intersection(extBisector(r, s), extBisector(s, t));
    return {p, t.dist(p)};
}