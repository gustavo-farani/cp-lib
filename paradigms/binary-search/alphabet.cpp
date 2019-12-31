#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

template<typename T>
struct Alphabet { // Offline Position Query (useful for coordinate compression)
    vector<T> o;
    int sz;
    void add (T x) { o.pb(x); }
    void build () {
        sort(o.begin(), o.end());
        sz = unique(o.begin(), o.end()) - o.begin();
    }
    int rank (T x) {
        auto it = lower_bound(o.begin(), o.begin() + sz, x);
        int i = (it - o.begin());
        if (i == sz || x < o[i]) {
            return -1;
        } else {
            return i + 1;
        }
    }
};