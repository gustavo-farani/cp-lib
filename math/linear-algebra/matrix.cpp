#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

const int MOD = 1e9 + 7;

struct Matrix {
	int o;     // order (number of rows and columns) of the square matrix
	vector<vi> e;
	Matrix (int o, int k) : o(o), e(o, vi(o)) {
		for (int i = 0; i < o; i++) for (int j = 0; j < o; j++)
			e[i][j] = k*(i == j);    // initialized as kI := identity matrix scaled by k
	}
	Matrix operator* (const Matrix& a) {   // matrix-matrix multiplication
		Matrix p(o, 0);
		for (int i = 0; i < o; i++) for (int j = 0; j < o; j++)
			for (int k = 0; k < o; k++)
				p.e[i][j] = (p.e[i][j] + (ll) e[i][k]*a.e[k][j]) % MOD;
		return p;
	}
	vi operator* (const vi &v) {           // vector-matrix multiplication
		vi u(o);
		for (int i = 0; i < o; i++)
			for (int k = u[i] = 0; k < o; k++)
				u[i] = (u[i] + (ll) e[i][k]*v[k]) % MOD;
		return u;
	}
};