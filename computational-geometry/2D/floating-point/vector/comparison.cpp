#include "point.cpp"

bool operator< (PT p, PT q) {
    return sgn(p.x - q.x) == 0 ? p.y < q.y : p.x < q.x;
}
bool operator== (PT p, PT q) {
    return sgn(p.x - q.x) == 0 && sgn(p.y - q.y) == 0;
}