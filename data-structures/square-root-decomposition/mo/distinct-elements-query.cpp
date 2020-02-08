#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
    
#define pb push_back

const int bs = 320;     // sqrt(1e5)
    
struct Query {
    int l, r, id;
    bool operator< (const Query &o) {
        int i = (l - 1)/bs, j = (o.l - 1)/bs;
        if (i != j) {
            return (i < j);
        } else if (i & 1) {
            return (r > o.r);
        } else {
            return (r < o.r);
        }
    }
};

typedef int Answer;

int freq[300000 + 1], arr[300000 + 1];

struct DS {
    Answer state;    // := number of distinct elements in range
    DS () : state(0) {}
    void operator+= (int i) {
        if (freq[arr[i]]++ == 0) state++;
    }
    void operator-= (int i) {
        if (--freq[arr[i]] == 0) state--;
    }
} ds;

struct Mo {
    int cnt;
    vector<Query> qrs;
    Mo () : cnt(0) {}
    void push (int l, int r) {   // [l, r] closed interval 1-based indexation
        qrs.pb(Query{l, r, cnt++});
    }   // NOTE: empty interval such as (i, i - 1) is safely accepted
    queue<Answer> operator() () {
        vector<Answer> ans(qrs.size());
        sort(qrs.begin(), qrs.end());
        int l = 1, r = 0;
        for (Query q : qrs) {
            while (l > q.l) ds += --l;
            while (r < q.r) ds += ++r;
            while (l < q.l) ds -= l++;
            while (r > q.r) ds -= r--;
            ans[q.id] = ds.state;
        }
        queue<Answer> q;
        for (Answer a : ans) q.push(a);
        return q;
    }
} mo;