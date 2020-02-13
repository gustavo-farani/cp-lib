#include "prefix-function.cpp"
#include <vector>
using namespace std;

typedef vector<int> vi;

template<class S>
int period (const S& s) {
    vi pi(prefixFunction(s));
    int n = s.size();
    int k = n - pi.back();
    return (n % k == 0 ? k : n);
}
