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
#define MODULO 1000007

ifstream fin("11957_input.txt");
#define cin fin

int main()
{
	int tttt;
	cin >> tttt;
	int case_count = 0;
	while (tttt--)
	{
		int N;
		cin >> N;
		vector<vector<char> > g(N, vector<char>(N, '.'));
		vector<vector<int> > f(N, vector<int>(N, 0));
		
		for (int i = 0; i < N; i++)
		{
			string s;
			cin >> s;
			for (int j = 0; j < N; j++)
				g[i][j] = s[j];
		}

		for (int i = N - 1; i >= 0; i--)
			for (int j = 0; j < N; j++)
			{
				if (g[i][j] == 'W')
				{
					f[i][j] = 1;
				}
				else if (g[i][j] == '.')
				{
					if (i < N - 1)
					{
						if (j > 0)
						{
							if (g[i + 1][j - 1] != 'B')
								f[i][j] += f[i + 1][j - 1];
							else if (i < N - 2 && j>1 && g[i + 2][j - 2] != 'B')
								f[i][j] += f[i + 2][j - 2];
						}
						if (j < N - 1)
						{
							if (g[i + 1][j + 1] != 'B')
								f[i][j] += f[i + 1][j + 1];
							else if (i < N - 2 && j < N - 2 && g[i + 2][j + 2] != 'B')
								f[i][j] += f[i + 2][j + 2];
						}
					}
				}
				f[i][j] %= MODULO;
			}

		int result = 0;
		for (int j = 0; j < N; j++)
		{
			result += f[0][j];
			result %= MODULO;
		}
			

		case_count++;
		cout << "Case " << case_count << ": " << result << endl;
	}
}