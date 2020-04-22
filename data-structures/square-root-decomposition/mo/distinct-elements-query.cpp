#include "../../../template.cpp"

const int BS = 320;

struct Query {
    int l, r;
    int id;
    bool operator< (const Query &o) {
        int i = (l - 1)/BS, j = (o.l - 1)/BS;
        if (i != j) {
            return (i < j);
        } else if (i & 1) {
            return (r > o.r);
        } else {
            return (r < o.r);
        }
    }
};

struct DistinctElements {
    vi v;
    int cnt;
    vector<Query> qrs;
    int state;
    vi freq;
    DistinctElements (int n) :
        v(n + 1), cnt(0), state(0),
        freq(1e6 + 1, 0)
    {}
    int& operator[] (int i) { return v[i]; }
    void push (int l, int r) {
        qrs.pb(Query{l, r, cnt++});
    }
    void add (int i) {
        if (freq[v[i]]++ == 0) state++;
    }
    void remove (int i) {
        if (--freq[v[i]] == 0) state--;
    }
    queue<int> solve () {
        vi ans(qrs.size());
        sort(qrs.begin(), qrs.end());
        int l = 1, r = 0;
        for (Query q : qrs) {
            while (l > q.l) add(--l);
            while (r < q.r) add(++r);
            while (l < q.l) remove(l++);
            while (r > q.r) remove(r--);
            ans[q.id] = state;
        }
        queue<int> q;
        for (int a : ans) q.push(a);
        return q;
    }
};