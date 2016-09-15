#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("10020_input.txt");
#define cin fin

typedef pair<int, int> ele;

struct
{
	bool operator()(const ele & a, const ele & b)
	{
		return a.first < b.first;
	}
} my_comp_0;

int main()
{
	int tttt;
	cin >> tttt;

	while (tttt--)
	{
		int m;
		cin >> m;
		vector<ele> pairs;
		int l, r;
		cin >> l >> r;
		while (!(l == 0 && r == 0))
		{
			pairs.push_back(ele(l, r));
			cin >> l >> r;
		}
		sort(pairs.begin(), pairs.end(), my_comp_0);

		vector<int> f(m + 1, 0);
		vector<ele> pairs_in_use(1, ele(0, 0));
		int cur_right = 1;

		for (auto it : pairs)
		{
			int last = it.first > 0 ? f[it.first] : 0;
			if (it.first < cur_right && it.second >= cur_right)
			{
				while (cur_right <= m && cur_right <= it.second)
				{
					f[cur_right++] = last + 1;
					pairs_in_use.push_back(it);
				}
			}
			if (cur_right > m) break;
		}

		if (f.back() == 0)
			cout << 0 << endl;
		else
		{
			cout << f.back() << endl;
			int last = f.back() + 1;
			stack<ele> s;
			for (int i = m; i >= 1; i--)
			{
				if (f[i] != last)
				{
					last = f[i];
					s.push(pairs_in_use[i]);
				}
			}
			while (!s.empty())
			{
				ele t = s.top();
				s.pop();
				cout << t.first << ' ' << t.second << endl;
			}
		}
	}
}
