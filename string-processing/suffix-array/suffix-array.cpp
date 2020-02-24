#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define pb push_back
typedef vector<int> vi;

template<class S>
vi suffixArray (const S& s) {
    int n = s.size();
    vi suf(n), bucket(n), stable(n), cnt(n), temp(n);
    iota(suf.begin(), suf.end(), 0);
    sort(suf.begin(), suf.end(), [&](int i, int j) { return s[i] < s[j]; });
    bucket[suf[0]] = 0;
    int sz = 1;
    for (int i = 1; i < n; i++) {
        if (s[suf[i]] > s[suf[i - 1]]) sz++;
        bucket[suf[i]] = sz - 1; 
    }
    for (int l = 1; l < n && sz < n; l <<= 1) {
        for (int i = 0; i < n; i++) {
            if ((stable[i] = suf[i] - l) < 0) stable[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + sz, 0);
        for (int i = 0; i < n; i++) cnt[ bucket[ stable[i] ] ]++;
        for (int i = 1; i < sz; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            suf[ --cnt[ bucket[ stable[i] ] ] ] = stable[i];
        }
        temp[suf[0]] = 0;
        sz = 1;
        for (int i = 1; i < n; i++) {
            int cs, ps;
            if ((cs = suf[i] + l) >= n) cs -= n;
            if ((ps = suf[i - 1] + l) >= n) ps -= n;
            if (bucket[suf[i]] > bucket[suf[i - 1]]
            || bucket[suf[i]] == bucket[suf[i - 1]] && bucket[cs] > bucket[ps]) sz++;
            temp[suf[i]] = sz - 1;
        }
        bucket.swap(temp);
    }
    return suf;
}