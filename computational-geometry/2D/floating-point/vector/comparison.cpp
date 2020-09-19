#include "point.cpp"

bool operator< (PT p, PT q) {
    int sx = sgn(p.x - q.x);
    return sx == 0 ? sgn(p.y - q.y) < 0 : sx < 0;
}
bool operator== (PT p, PT q) {
    return sgn(p.x - q.x) == 0 && sgn(p.y - q.y) == 0;
}