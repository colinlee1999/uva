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

ifstream fin("11472_input.txt");
#define cin fin

int main()
{
	int tttt;
	cin >> tttt;
	while (tttt--) {
		int N, M;
		cin >> N >> M;
		if (M == 0) {
			cout << 0 << endl;
			continue;
		}
		long long bit_status = 1 << N;
		//cout << 50 - tttt << endl;
		vector< vector < vector<long long> > > f(M, vector< vector<long long> >(N, vector<long long>(bit_status, 0)));
		//cout << 50 - tttt << endl;
		for (int k = 1; k < N; k++)
			f[0][k][1 << k] = 1;
		//cout << 50 - tttt << endl;

		for (int i = 1; i < M; i++)
			for (int s = 0; s < bit_status; s++)
				for (int k = 0; k < N; k++) {
					 for (int j = (k != 0 ? -1 : 1); j <= (k != (N - 1) ? 1 : -1); j += 2) {
						 if ( (s & (1 << (k + j))) && (s & (1 << k)) ) {
							 f[i][k][s] += f[i - 1][k + j][s];
							 f[i][k][s] += f[i - 1][k + j][s & (~(1 << k))];
							 f[i][k][s] %= MODULO;
						 }
					}
				}

		long long result = 0;
		for (int i = 0; i < M; i++)
			for (int k = 0; k < N; k++) {
				result += f[i][k][bit_status - 1];
				result %= MODULO;
			}

		cout << result << endl;
	}
}
