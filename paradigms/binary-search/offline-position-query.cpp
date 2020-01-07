#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

template<typename T>
struct Universe {   // Offline Position Query
    vector<T> o;
    void push (const T &x) { o.pb(x); }
    void build () {
        sort(o.begin(), o.end());
        o.resize(unique(o.begin(), o.end()) - o.begin());
    }
    int find (const T &x) {   // 0-based
        auto it = lower_bound(o.begin(), o.end(), x);
        return (it == o.end() || x < *it ? -1 : it - o.begin());
    }
    T& operator[] (int i) { return o[i]; }  // 0-based
};