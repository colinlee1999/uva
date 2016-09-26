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
		vector<vector<int> > f(slen, vector<int>(slen, 0));

		for (int i = 1; i < slen; i++)
			for (int j = i - 1; j >= 0; j--)
			{
				f[j][i] = min(f[j + 1][i], f[j][i - 1]) + 1; // delete or add one more
				//f[j][i] = min(f[j][i], (i - j + 1) / 2); // change only half
				if (s[i] == s[j]) // if first and last are equal
					f[j][i] = min(f[j][i], f[j + 1][i - 1]);
				else // if first and last are not equal
					f[j][i] = min(f[j][i], f[j + 1][i - 1] + 1);
			}
		
		//for (int i = 0; i < slen; i++, cout << endl)
		//	for (int j = 0; j < slen; j++)
		//		cout << f[j][i] << ' ';

		case_count++;
		cout << "Case " << case_count << ": " << f[0][slen - 1] << endl;
	}
}
