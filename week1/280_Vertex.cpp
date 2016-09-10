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

ifstream fin("280_input.txt");
#define cin fin

int main()
{
	int n, m;
	cin >> n;
	while (n)
	{
		vector<vector<int>> f(n + 1, vector<int>(n + 1, UNREACHABLE));
		int start = 0;
		cin >> start;
		while (start)
		{
			int end;
			cin >> end;
			while (end)
			{
				f[start][end] = 1;
				cin >> end;
			}
			cin >> start;
		}

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);

		int num_test;
		cin >> num_test;
		for (int i = 0; i < num_test; i++)
		{
			int cur_test, total_unreachable = 0;
			cin >> cur_test;
			for (int i = 1; i <= n; i++)
				if (f[cur_test][i] == UNREACHABLE)
					total_unreachable++;
			cout << total_unreachable;
			for (int i = 1; i <= n; i++)
				if (f[cur_test][i] == UNREACHABLE)
					cout << ' ' << i;
			cout << endl;
		}
		cin >> n;
	}
}
