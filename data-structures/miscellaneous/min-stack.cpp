#include "../../boilerplate.cpp"

template<class T>
struct MinStack {
    vector<T> s;
    void push (const T& x) { s.pb(s.empty() ? x : min(x, s.back())); }
    void pop () { s.pop_back(); }
    T min () { return s.empty() ? numeric_limits<T>::max() : s.back(); }
};