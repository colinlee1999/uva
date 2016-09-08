#include <iostream>
#include <vector>
#include <fstream>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("input.txt");
// #define cin fin

int main()
{
	int n, m, tttt = 0;
	cin >> n >> m;
	while (!(n == 0 && m == 0))
	{
		tttt++;
		cout << "Network " << tttt << endl;
		vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));
		int start, end;
		for (int i = 0; i < m; i++)
		{
			cin >> start >> end;
			g[start][end] = 1;
		}
		// for (int i = 1; i <= n; i++, cout<<endl)
		// 	for (int j = 1; j <= n; j++)
		// 		cout << g[i][j] << ' ';
		vector<vector<int>> f(n + 1, vector<int>(n + 1, UNREACHABLE));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i == j)
					f[i][j] = 0;
				else if (g[i][j] != 0)
					f[i][j] = g[i][j];
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
		start = 1;
		end = 2;
		if (f[start][end] == UNREACHABLE || f[end][start] == UNREACHABLE)
			cout << "Impossible" << endl;
		else
		{
			vector<vector<int>> v(n + 1, vector<int>(n + 1, UNREACHABLE));
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (i == j)
						v[i][j] = 1;
					else
						v[i][j] = f[i][j] + f[j][i];
			for (int k = 1; k <= n; k++)
				for (int i = 1; i <= n; i++)
					for (int j = 1; j <= n; j++)
							v[i][j] = min(v[i][j], v[i][k] + v[k][j] - 1);
			for (int l = 1; l <= n; l++)
				for (int k = 1; k <= n; k++)
					for (int i = 1; i <= n; i++)
						for (int j = 1; j <= n; j++)
							v[i][j] = min(v[i][j], v[i][k] + f[k][l] + v[l][j] - 1);
			cout << "Minimum number of nodes = ";
			cout << v[start][end] << endl;
		}
		cin >> n >> m;
		if (!(n == 0 && m == 0)) cout << endl;
	}
}
