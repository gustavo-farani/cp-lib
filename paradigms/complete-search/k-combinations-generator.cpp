#include <vector>
using namespace std;

typedef vector<int> vi;

struct Combinator {
    vi v, a;
    vector<vi> s;
    int k;
    Combinator (const vi &v) : v(v) {}   // v : SORTED vector
    vector<vi> operator() (int k) {  // 0 <= m <= a.size()
        s.clear();
        build(0, k);
        return s;
    }
    void build (int i, int r) {
        if (r == 0) {
            s.push_back(a);
        } else {
            for (int j = i; j + r <= v.size(); j++) {
                a.push_back(v[j]);
                build(j + 1, r - 1);
                a.pop_back();
            }
        }
    }
};