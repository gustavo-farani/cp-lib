#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
    
#define pb push_back

const int bs = 320;     // sqrt(1e5)
    
struct Query {
    int l, r;    // closed interval: [l, r], 1-based indexation
    int id;      // priority number (entry time) of a query
    bool operator< (const Query &o) {
        int i = l/bs, j = o.l/bs;
        if (i != j) {
            return (i < j);
        } else if (i & 1) {    // zig-zag optmization
            return (r > o.r);  // odd bucket: right pointers in deacresing order
        } else {
            return (r < o.r);  // even bucket: right pointers in increasing order
        }
    }
};

struct Answer{};

struct DS {
    Answer state;    // the final answer after the range is adjusted
    DS ();
    void operator+= (int i);  // process the addition of array's ith position to the range
    void operator-= (int i);  // process the removal of array's ith position from the range
} ds;

struct Mo {
    int cnt;  // queries id's are defined automatically and safely
    vector<Query> qrs;
    Mo () : cnt(0) {}
    void push (int l, int r) {  // pushes a new query to the back of the queue
        qrs.pb(Query{l, r, cnt++});
    }
    queue<Answer> operator() () {
        vector<Answer> ans(qrs.size());
        sort(qrs.begin(), qrs.end());
        int l = 1, r = 0;             // following 1-based indexation
        for (Query q : qrs) {
            while (l > q.l) ds += --l;
            while (r < q.r) ds += ++r;
            while (l < q.l) ds -= l++;
            while (r > q.r) ds -= r--;
            ans[q.id] = ds.state;
        }
        queue<Answer> q; // a queue dismiss the use of counters and iterators
        for (Answer a : ans) q.push(a);
        return q;
    }
} mo;