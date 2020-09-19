#include <bits/stdc++.h>
using namespace std;

// maximum capacity of BS*BS
template<class T, int BS = 320>
struct JumpQueue {
    int sz;
    vector<list<T>> bk;
    JumpQueue () : bk(BS), sz(0) {}
    // number of elements in the queue
    int size () { return sz; }
    // inserts x right before i-th (0-based) element of the queue
    // insert(0, x) : pushes to the front
    // insert(size(), x) : pushes to the back
    // complexity: O(BS)
    void insert (int i, const T& x) {
        if (sz == BS*BS) throw 'C';  // exceeded maximum capacity
        if (i < 0 || i > sz) throw 'I';  // index out of queue bounds
        for (auto it = bk.begin(); it != bk.end(); it++) {
            if (i <= it->size()) {
                it->insert(next(it->begin(), i), x);
                for (auto jt = it; jt->size() > BS; jt++) {
                    next(jt)->push_front(jt->back());
                    jt->pop_back();
                }
                break;
            } else {
                i -= BS;
            }
        }
        sz++;
    }
    // element at i-th position (0-based)
    // complexity: O(BS)
    T operator[] (int i) {
        if (i < 0 || i >= sz) throw 'I';  // index out of queue bounds
        for (auto& it : bk) {
            if (i < it.size()) return *next(it.begin(), i);
            else i -= BS;
        }
    }
    // removes element at i-th position (0-based) and returns it
    // pop(size() - 1) : removes element in the back
    // pop(0) : removes element in the front
    // complexity: O(BS + size()/BS)
    T pop (int i) {
        if (i < 0 || i >= sz) throw 'I';  // index out of queue bounds
        for (auto it = bk.begin(); it != bk.end(); it++) {
            if (i < it->size()) {
                auto kt = next(it->begin(), i);
                T x = *kt;
                it->erase(kt);
                for (auto jt = it; next(jt) != bk.end()
                && !next(jt)->empty(); jt++) {
                    jt->push_back(next(jt)->front());
                    next(jt)->pop_front();
                }
                sz--;
                return x;
            } else {
                i -= it->size();
            }
        }
    }
    /* Iterating it from the front to the back:
    JumpQueue<int> v;
    for (auto& b : v.bk) {
        if (b.empty()) break;
        for (int x : b) {
            cout << x << '\n';
        }
    }
    */
};