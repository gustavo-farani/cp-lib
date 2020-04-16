#include "point.cpp"

// reflects point p w.r.t. the line through the origin directed by v
PT reflect (const PT& p, const PT& v) {  // TO BE TESTED
    ld a = v.x*v.x - v.y*v.y, b = 2.0*v.x*v.y;
    return PT(PT(a, b)*p, PT(b, -a)*p)/(v*v);
}
/* OBS: Given the direction vector v = (x, y),
the matrix of the linear transformation that performs
reflection of 2D vectors w.r.t. to v is (in LaTeX):
    \frac{1}{x^2 + y^2} \begin{pmatrix} x^2 - y^2 & 2xy
    \\ 2xy & y^2 - x^2 \end{pmatrix}
*/