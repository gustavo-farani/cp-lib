#include <vector>
using namespace std;

#define pb push_back
typedef long long ll;

vector<ll> find (ll n) {
    vector<ll> d;
    ll i;
    for (i = 1; i*i < n; i++) {
        if (n % i == 0) {
            d.pb(i);
            d.pb(n/i);
        }
    }
    if (i*i == n) d.pb(i);
    return d;
}