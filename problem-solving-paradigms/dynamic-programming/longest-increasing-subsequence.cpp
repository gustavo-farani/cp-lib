#include <vector>
#include <algorithm>
using namespace std;

template <class T>
struct LIS {
    int n;
    vector<T> pivot, v;
    vi pred, pos, color;
    template <class I, class C>
    LIS (I first, I last, C comp) :
        v(first, last), n(last - first),
        pred(n), color(n)
    {
        for (int i = 0; i < n; i++) {
            int j = lower_bound(pivot.begin(), pivot.end(), v[i], comp) - pivot.begin();
            if (j == pivot.size()) {
                pivot.pb(v[i]);
                pos.pb(i);
            } else {
                pivot[j] = v[i];
                pos[j] = i;
            }
            color[i] = j;
            pred[i] = (j == 0 ? -1 : pos[j - 1]);
        }
    }
    /*
    Number of elements in a longest increasing subsequence (according to comp)
    */
    int size () { return pivot.size(); }
    /*
    An example of longest increasing subsequence (according to comp)
    */
    vector<T> sample () {
        vector<T> lis;
        for (int i = pos.back(); i != -1; i = pred[i]) {
            lis.pb(v[i]);
        }
        reverse(lis.begin(), lis.end());
        return lis;
    }
    /*
    Minimum cardinality partition of the original sequence
    into non-increasing subsequences (according to comp).
    It returns an array with colors associated to each position
    in the range [first, last).
    Ex:
    color[0] := color associated with element *first
    color[1] := color associeted with element *next(first)
    color[last - first - 1] := color associated with element *prev(last)
    */
    vi& partition () { return color; }
};