#include <vector>
#include "../vector/point.cpp"
using namespace std;

#define pb push_back

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (vector<PT>&& v) : sides(v.size()), p(v) {
        p.pb(p.front());  // facilitates iteration
    }  // v is moved, instead of copied, for efficiency
};