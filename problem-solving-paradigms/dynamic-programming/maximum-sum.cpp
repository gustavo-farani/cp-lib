#include "../../template.cpp"

template<class T, class I>
T maximumSum (I first, I last) {
    T global = numeric_limits<T>::min(), local = 0;
    for (I it = first; it != last; it++) {
        local = max(*it, *it + local);
        global = max(global, local);
    }
    return global;
}