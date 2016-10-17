#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define eps (1e-9)
#define MODULO 1000000007

ifstream fin("11512_input.txt");
#define cin fin

vector<vector<long long> > mul(
	const vector<vector<long long> > & a, 
	const vector<vector<long long> > & b) {
	vector<vector<long long> > r(a);
	r[0][0] = r[0][1] = r[1][0] = r[1][1] = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				r[i][j] += a[i][k] * b[k][j];
	return r;
}

vector<vector<long long> > power(
	const vector<vector<long long> > & x,
	int n) {
	vector<vector<long long> > s(x);
	vector<vector<long long> > r(x);
	r[0][0] = r[1][1] = 1;
	r[0][1] = r[1][0] = 0;
	while (n > 0) {
		if (n & 1) {
			r = mul(r, s);
		}
		s = mul(s, s);
		n >>= 1;
	}
	return r;
}

int main()
{
	long long p, q, n;
	cin >> p >> q;
	while (cin >> n) {
		if (n == 0) {
			cout << 2 << endl;			
		}
		else {
			vector<vector<long long> > mat(2, vector<long long>(2, 0));
			mat[0][0] = 0;
			mat[0][1] = 1;
			mat[1][0] = -q;
			mat[1][1] = p;
			mat = power(mat, n - 1);
			long long S0 = 2;
			long long S1 = p;
			long long result = mat[1][0] * S0 + mat[1][1] * S1;
			cout << result << endl;
		}
		cin >> p >> q;
	}
}
