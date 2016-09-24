#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
using namespace std;

ifstream fin("10616_input.txt");
#define cin fin

int main()
{
	int N, Q;
	cin >> N >> Q;
	int set_count = 0;
	while (!(N == 0 && Q == 0))
	{
		set_count++;
		cout << "SET " << set_count << ":" << endl;
		vector<long long> a(N + 1, 0);
		for (int i = 1; i <= N; i++)
			cin >> a[i];
		int query_count = 0;
		while (Q--)
		{
			query_count++;
			int D, M;
			cin >> D >> M;
			vector<vector<vector<long long> > > f(N + 1, vector<vector<long long> >(M + 1, vector<long long>(D, 0)));
			for (int i = 0; i <= N; i++)
					f[i][0][0] = 1;
			long long help = (long long)INT_MAX * D;
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= M && j <= i; j++)
					for (int k = 0; k < D; k++)
					{
						f[i][j][k] = f[i - 1][j - 1][(k - a[i] + help) % D];
						if (i - 1 >= j)
							f[i][j][k] += f[i - 1][j][k];
					}
			cout << "QUERY " << query_count << ": " << f[N][M][0] << endl;
		}

		cin >> N >> Q;
	}
}
