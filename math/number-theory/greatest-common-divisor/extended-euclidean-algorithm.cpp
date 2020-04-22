#include "../../../template.cpp"

ll extendedEuclidean (ll a, ll b, ll &x, ll &y) {
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
	x = m[cur];
	y = n[cur];
    return r[cur];
}