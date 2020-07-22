#include "../../../boilerplate.cpp"

const int BS = 320;      // bucket-size  (320 == sqrt(1e5))

struct Query {
    int l, r;    // closed interval: [l, r]; 1-based indexation;
    int id;      // priority number (entry time) of a query
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

template<class Answer>
struct Mo {
    vi v;                    // underlying array (we assume its value_type as int)
    int cnt;                 // queries id's are counted automatically and setted safely
    vector<Query> qrs;
    Answer state;            // the final answer after the range boundaries are adjusted
    Mo (int n) : v(n + 1), cnt(0) {}
    int& operator[] (int i) { return v[i]; }             // for reading input inside main
    void push (int l, int r) {             // pushes a new query to the back of the queue
        qrs.pb(Query{l, r, cnt++});
    }
    void add (int i);    // TODO process the addition of array's ith position to the range
    void remove (int i); // TODO process the removal of array's ith position from the range
    queue<Answer> solve () {
        vector<Answer> ans(qrs.size());
        sort(qrs.begin(), qrs.end());
        int l = 1, r = 0;             // following 1-based indexation
        for (Query q : qrs) {
            while (l > q.l) add(--l);
            while (r < q.r) add(++r);
            while (l < q.l) remove(l++);
            while (r > q.r) remove(r--);
            ans[q.id] = state;
        }
        queue<Answer> q; // a queue, rather than a vector, allows for successive retrievals independent from
        // interation: the retrievals may not necessarily happen all at the same time, in a single for loop
        for (Answer a : ans) q.push(a);
        return q;
    }
};