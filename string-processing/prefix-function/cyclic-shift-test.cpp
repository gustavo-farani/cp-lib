#include "knuth-morris-pratt.cpp"
using namespace std;

template<class S>
bool isCyclicShift (const S& s, const S& t) {
    bool match = false;
    int n = s.size();
    if (n == t.size()) {
        S cat(t);
        cat.insert(cat.end(), t.begin(), t.end());
        vector<bool> end(patternMatching(s, cat));
        for (int i = n; i < cat.size() && !match; i++) {
            match |= end[i];
        }
    }
    return match;
}

#include <iostream>

int main () {
    int n;
    cin >> n;
    vi u(n);
    for (int i = 0; i < n; i++) cin >> u[i];
    vi v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    if (isCyclicShift(u, v)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}