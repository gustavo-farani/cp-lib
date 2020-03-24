#include "point.cpp"

bool operator< (const PT& a, const PT& b) {   // TO BE TESTED
    if (b.y > 0) {
        return !((a ^ b) <= 0 || a.y < 0);
    } else if (b.y < 0) {
        return ((a ^ b) > 0 || a.y >= 0);
    } else {
        ll c = a ^ b;
        return (c > 0 || c == 0 && a*b < 0);
    }
}       // counter-clock-wise sorting based on polar angle