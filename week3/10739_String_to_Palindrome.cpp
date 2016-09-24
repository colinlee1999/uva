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

ifstream fin("10739_input.txt");
#define cin fin

int main()
{
	int N;
	cin >> N;
	int case_count = 0;
	while (N--)
	{
		string s;
		cin >> s;
		int slen = s.length();
		vector<vector<int> > f(slen + 1, vector<int>(slen + 1, 0));
		for (int i = 1; i <= slen; i++)
			f[i][0] = f[0][i] = i;

		for (int i = 1; i <= slen; i++)
			for (int j = 1; j <= slen; j++)
			{
				f[i][j] = min(f[i - 1][j], f[i][j - 1]) + 1;
				if (s[i - 1] == s[slen - j])
					f[i][j] = min(f[i][j], f[i - 1][j - 1]);
			}

		case_count++;
		cout << "Case " << case_count << ": " << f[slen][slen] << endl;
	}
}
