#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

template <class T>
struct LIS {
    vector<T> pivot;
    vi pred, pos, color;
    template <class I, class C>
    LIS (I first, I last, C comp) : pred(last - first), color(last - first) {
        for (I it = first; it != last; it++) {
            int i = it - first;
            int j = lower_bound(pivot.begin(), pivot.end(), *it, comp) - pivot.begin();
            if (j == pivot.size()) {
                pivot.pb(*it);
                pos.pb(i);
            } else {
                pivot[j] = *it;
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
    Returns the INDICES of some longest increasing subsequence (according to comp)
    */
    vi restore () {
        vector<T> lis;
        for (int i = pos.back(); i != -1; i = pred[i]) lis.pb(i);
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