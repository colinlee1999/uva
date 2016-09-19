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

ifstream fin("1577_input.txt");
#define cin fin

bool check(int range, int n, int k, const vector<int> & v)
{
	int pairs = 0;
	for (int i = 1; pairs < n && i < v.size(); i++)
	{
		if (v[i] - v[i - 1] <= range)
		{
			pairs++;
			i++;
		}
		else
		{
			if (pairs * 2 * k < i)
				return false;
		}
	}
	return true;
}

int main()
{
	int n, k;
	while (cin >> n >> k)
	{
		vector<int> v(2 * n * k, 0);
		for (int i = 0; i < v.size(); i++)
			cin >> v[i];
		sort(v.begin(), v.end());
		int left = -1;
		int right = v.back() - v.front();
		while (left + 1 < right)
		{
			int mid = left + (right - left) / 2;
			if (check(mid, n, k, v)) right = mid;
			else left = mid;
		}
		int result = right;
		cout << result << endl;
	}
}
