#include "../two-pointers/sliding-window.cpp"
#include "../../boilerplate.cpp"

const int BS = 320;      // bucket-size  (320 == sqrt(1e5))

struct Query {
    int l, r;    // closed interval: [l, r]; 1-based indexation;
    int id;      // priority number (entry time) of a query
    Query (int l, int r) : l(l), r(r) {}
    bool operator< (const Query &o) {
        int i = (l - 1)/BS, j = (o.l - 1)/BS;
        if (i != j) {
            return (i < j);
        } else if (i & 1) {    // zig-zag optmization
            return (r > o.r);  // odd-indexed bucket: right pointers in deacresing order
        } else {
            return (r < o.r);  // even-indexed bucket: right pointers in increasing order
        }
    }
};

template<class T>
deque<T> mo (vector<Query>& q) {
    int m = q.size();
    for (int i = 0; i < q.size(); i++) q[i].id = i;
    sort(q.begin(), q.end());
    deque<T> ans(m);
    TwoPointers::init();
    for (Query& qry : q) {
        ans[qry.id] = TwoPointers::query(qry.l, qry.r);
    }
    return ans;
}