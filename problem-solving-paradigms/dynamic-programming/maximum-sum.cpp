#include "../../boilerplate.cpp"

template<class T, class S>
T maximumSum (const S& s) {
    T global = numeric_limits<T>::min(), local = 0;
    for (T x : s) global = max(global, local = max(x, x + local));
    return global;
}