#include "../../boilerplate.cpp"

template<class T>
struct MaxStack {
    vector<T> s;
    void push (const T& x) { s.pb(s.empty() ? x : max(x, s.back())); }
    void pop () { s.pop_back(); }
    T query () { return s.empty() ? numeric_limits<T>::min() : s.back(); }
};