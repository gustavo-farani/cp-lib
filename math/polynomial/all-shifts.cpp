#include "polynomial-multiplication.cpp"

// l, r: boolean vectors
// d[k] = number of pairs i < j such that
//  l[i] && r[j] && j - i == k
vi allShifts (const vector<bool>& l, const vector<bool>& r) {
    vi a(l.rbegin(), l.rend()), b(r.begin(), r.end());
    auto c = multiply(a, b);
    vi cnt(c.begin() + l.size() - 1, c.end());
    return cnt;
}

// sample applications:
// https://open.kattis.com/problems/kinversions
// https://codeforces.com/contest/1398/problem/G