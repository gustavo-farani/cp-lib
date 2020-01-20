#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> Vector;

const int O = 3;
ll m;

struct Matrix {
	vector< Vector > e;
	Matrix (int k) : e(O, Vector(O, 0)) {
		for (int i = 0; i < O; i++) for (int j = 0; j < O; j++)
			e[i][j] = k*(i == j);
	}
	Matrix operator* (Matrix a) {
		Matrix p (0);
		for (int i = 0; i < O; i++) for (int j = 0; j < O; j++)
			for (int k = 0; k < O; k++) 
				p.e[i][j] = (p.e[i][j] + e[i][k] * a.e[k][j]) % m;
		return p;
	}
	void operator= (const Matrix &a) {
		for (int i = 0; i < O; i++) for (int j = 0; j < O; j++)
			e[i][j] = a.e[i][j];
	}
	Vector operator* (const Vector &v) {
		Vector u (O, 0);
		for (int i = 0; i < O; i++)
			for (int k = u[i] = 0; k < O; k++)
				u[i] = (u[i] + e[i][k] * v[k]) % m;
		return u;
	}
};