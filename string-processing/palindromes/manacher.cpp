#include <vector>
#include <array>
using namespace std;

typedef vector<int> vi;

template<class S>
array<vi, 2> manacher (const S& s) {
	int n = s.size();
	array<vi, 2> d({vi(n), vi(n)});
	for (int z = 0; z < 2; z++) {
        int gl = 0, gr = 0;
        for (int i = 0; i < n; i++) {
            d[z][i] = i > gr ? z : min(gr - i + 1, d[z][gl + gr - i + !z]);
            int tl = i - d[z][i] + z, tr = i + d[z][i] - 1;
            while (tl > 0 && tr + 1 < n && s[tl - 1] == s[tr + 1]) {
                d[z][i]++;
                tl--;
                tr++;
            }
            if (tr > gr) {
                gl = tl;
                gr = tr;
            }
        }
	}
	return d;
}