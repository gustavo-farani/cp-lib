#include "vector-form.cpp"
#include "../vector/reflection.cpp"

PT reflect (const PT& q, const Line& l) {  // TO BE TESTED
    return l.p + reflect(q - l.p, l.d);
}