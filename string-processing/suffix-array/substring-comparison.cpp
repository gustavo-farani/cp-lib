#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

struct SubstringComparison {
    vector<vi> bucket;
    template<class S>
    SubstringComparison (const S& s) : bucket(1) {
        int n = s.size();
        vi suf(n), stable(n), cnt(n), temp(n);
        iota(suf.begin(), suf.end(), 0);
        sort(suf.begin(), suf.end(), [&](int i, int j) { return s[i] < s[j]; });
        bucket[0][suf[0]] = 0;
        int sz = 1;
        for (int i = 1; i < n; i++) {
            if (s[suf[i]] > s[suf[i - 1]]) sz++;
            bucket[0][suf[i]] = sz - 1; 
        }
        for (int k = 0, l = 1; l < n; k++, l <<= 1) {
            for (int i = 0; i < n; i++) {
                if ((stable[i] = suf[i] - l) < 0) stable[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + sz, 0);
            for (int i = 0; i < n; i++) cnt[ bucket[k][ stable[i] ] ]++;
            for (int i = 1; i < sz; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) {
                suf[ --cnt[ bucket[k][ stable[i] ] ] ] = stable[i];
            }
            bucket.pb(vi(n));
            bucket[k + 1][suf[0]] = 0;
            sz = 1;
            for (int i = 1; i < n; i++) {
                int cs, ps;
                if ((cs = suf[i] + l) >= n) cs -= n;
                if ((ps = suf[i - 1] + l) >= n) ps -= n;
                if (bucket[k][suf[i]] > bucket[k][suf[i - 1]]
                || bucket[k][suf[i]] == bucket[k][suf[i - 1]]
                && bucket[k][cs] > bucket[k][ps]) sz++;
                bucket[k + 1][suf[i]] = sz - 1;
            }
        }
    }
    int operator() (int i, int a, int j, int b) {
        int m = min(a, b);
        int ans = 0;
        for (int k = 0, l = 1; ans == 0 && l <= m; k++, l <<= 1) {
            if (m & l) {
                ans = bucket[k][i] - bucket[k][j];
                i += l;
                j += l;
            }
        }
        if (ans == 0) ans = a - b;
        return ans;
    }
};