#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("10793_input.txt");
#define cin fin

int main()
{
	int n, m, tttt = 0;
	cin >> tttt;
	int cases = 1;
	while (tttt--)
	{
		cout << "Map " << cases++ << ": ";
		int n, m;
		cin >> n >> m;
		vector<vector<int>> f(n + 1, vector<int>(n + 1,UNREACHABLE));
		for (int i = 0; i < m; i++)
		{
			int v1, v2, len;
			cin >> v1 >> v2 >> len;
			f[v1][v2] = min(f[v1][v2], len);
			f[v2][v1] = f[v1][v2];
		}
		for (int i = 1; i <= n; i++)
			f[i][i] = 0;

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);

		vector<int> max_per_row(n + 1, 0);
		bool reachable = true;
		for (int i = 1; i <= n && reachable; i++)
			for (int j = 1; j <= n && reachable; j++)
				if (f[i][j] != UNREACHABLE)
					max_per_row[i] = max(max_per_row[i], f[i][j]);
				else
					reachable = false;
		if (!reachable)
		{
			cout << -1 << endl;
			continue;
		}

		unordered_set<int> s;
		for (int i = 1; i <= n; i++)
			if (f[1][i] == f[2][i] && f[1][i] == f[3][i] && f[1][i] == f[4][i] && f[1][i] == f[5][i])
				s.insert(i);
		int min_length = UNREACHABLE;
		for (auto it : s)
		{
			if (max_per_row[it] < min_length)
				min_length = max_per_row[it];
		}
		if (min_length == UNREACHABLE)
			cout << -1 << endl;
		else
			cout << min_length << endl;
	}
}
