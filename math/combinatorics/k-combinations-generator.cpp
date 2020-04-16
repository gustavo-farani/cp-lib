#include <vector>
using namespace std;

#define pb push_back
typedef vector<int> vi;

template<class T>
struct Combinator {
    vector<T> v, a;
    vector<vector<T>> s;
    Combinator (vi&& v) : v(v) {}   // v : SORTED vector MOVED
    vector<vi>& operator() (int k) {  // 0 <= m <= a.size()
        s.clear();
        build(0, k);
        return s;
    }
    void build (int i, int r) {
        if (r == 0) s.pb(a);
        else {
            for (int j = i; j + r <= v.size(); j++) {
                a.pb(v[j]);
                build(j + 1, r - 1);
                a.pop_back();
            }
        }
    }
};