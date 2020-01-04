#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

template<typename T>
struct Universe {   // Offline Position Query
    vector<T> o;
    int sz;
    void push (T x) { o.pb(x); }
    int build () {   // returns number of distinct elements
        sort(o.begin(), o.end());
        return sz = unique(o.begin(), o.end()) - o.begin();
    }
    int rank (T x) {   // 1-based
        auto it = lower_bound(o.begin(), o.begin() + sz, x);
        int i = (it - o.begin());
        return (i == sz || x < o[i] ? -1 : i + 1);
    }
    T operator[] (int i) { return o[i - 1]; }  // 1-based
};