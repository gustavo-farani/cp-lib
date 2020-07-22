#include "../../boilerplate.cpp"

template<typename T>
struct CoordinateCompression {
    vector<T> o;
    void push (const T& x) { o.pb(x); }
    int build () {
        sort(o.begin(), o.end());
        o.erase(unique(o.begin(), o.end()), o.end());
        return o.size();
    }
    int operator() (const T &x) {   // 0-based
        auto it = lower_bound(o.begin(), o.end(), x);
        return it == o.end() || x < *it ? -1 : it - o.begin();
    }
    T& operator[] (int i) { return o[i]; }  // 0-based
};