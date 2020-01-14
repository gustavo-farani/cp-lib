#include <tuple>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

pll eea (ll a, ll b) {
	ll r[] = {a, b};
	ll q[] = {-1, -1};
	ll m[] = {1, 0};
	ll n[] = {0, 1};
	bool cur = 1, prev = 0;
	while (r[prev]) {
		q[cur] = r[cur]/r[prev];
		r[cur] = r[cur] - q[cur]*r[prev];
		m[cur] = m[cur] - q[cur]*m[prev];
		n[cur] = n[cur] - q[cur]*n[prev];
		cur = !cur;
		prev = !prev;
	}
    return {m[cur], n[cur]};
}