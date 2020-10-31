#include "../../../boilerplate.cpp"

template<class T>
T countUnion (int n, const function<T(int)>& countIntersection) {
    T ans = 0;
    for (int mask = 1; mask < 1 << n; mask++) {
        T aux = countIntersection(mask);
        if (__builtin_popcount(mask) & 1) {
            ans += aux;
        } else {
            ans -= aux;
        }
    }
    return ans;
}