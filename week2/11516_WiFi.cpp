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

ifstream fin("11516_input.txt");
#define cin fin

bool check(int range, int n, const vector<int> & v)
{
	int used = 1;
	int last = 0;
	for (int i = 1; i < v.size(); i++)
	{
		if (v[i] - v[last]>range)
		{
			last = i;
			used++;
		}
	}
	return used <= n;
}

int main()
{
	int tttt;
	cin >> tttt;
	while (tttt--)
	{
		int n, m;
		cin >> n >> m;
		vector<int> v(m, 0);
		for (int i = 0; i < m; i++)
			cin >> v[i];
		if (n >= m)
			cout << "0.0" << endl;
		else
		{
			sort(v.begin(), v.end());
			int left = -1;
			int right = v.back() - v.front();
			while (left + 1 < right)
			{
				int mid = left + (right - left) / 2;
				if (check(mid, n, v)) right = mid;
				else left = mid;
			}
			double result = (double)right / 2.0;
			printf("%.1f\n", result);
		}
	}
}
