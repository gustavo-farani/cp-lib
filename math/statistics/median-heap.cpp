#include <set>
#include <vector>
#include <climits>
using namespace std;

struct MedianHeap {
    set<int> scr;  // scr is NOT a multiset, i.e., it doesn't admit repeated elements
    int median;    // when scr.size() is even, the median
    // is chosen as the leftmost element of the central pair
    void insert (int x) {
        if (scr.insert(x).second) {
            if (scr.size() > 1) {
                switch (scr.size() & 1) {  // new parity of scr.size()
                    case 0:
                        if (x < median) median = *prev(scr.lower_bound(median));
                        break;
                    case 1:
                        if (x > median) median = *scr.upper_bound(median);
                        break;
                }
            } else median = x;
        }
    }
};