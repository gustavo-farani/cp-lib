#include "../vector/point.cpp"
#include "../vector/reflection.cpp"

PT Line::reflect (const PT& q) const {  // TO BE TESTED
    return p + reflect(q - p, d);
}