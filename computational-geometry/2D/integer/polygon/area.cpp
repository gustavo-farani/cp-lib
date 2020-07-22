#include "polygon.cpp"

ll Polygon::shoelace () {
    ll sum = 0;
    for (int i = 0; i < sides; i++) sum += p[i] % p[next(i)];
    return sum;
}
bool Polygon::cw () { return shoelace() < 0; }
bool Polygon::ccw () { return shoelace() > 0; }