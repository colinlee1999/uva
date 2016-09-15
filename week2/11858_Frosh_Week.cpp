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

ifstream fin("11858_input.txt");
#define cin fin

long long merge(vector<int> & v, int left, int right)
{
	int mid = (right - left) / 2 + left;
	vector<int> f(right - left, 0);
	int lp, rp;
	lp = left;
	rp = mid;
	int count = 0;
	long long result = 0;
	while (lp < mid && rp < right)
	{
		if (v[lp] < v[rp])
			f[count++] = v[lp++];
		else
		{
			result += mid - lp;
			f[count++] = v[rp++];
		}
	}

	while (lp < mid)
		f[count++] = v[lp++];

	while (rp < right)
		f[count++] = v[rp++];

	count = 0;
	while (count < (int)f.size())
	{
		v[left + count] = f[count];
		count++;
	}

	return result;
}

long long get_inversion_num(vector<int> & v, int left, int right)
{
	if (right - left <= 1) return 0;
	int mid = (right - left) / 2 + left;
	long long result = get_inversion_num(v, left, mid);
	result += get_inversion_num(v, mid, right);
	result += merge(v, left, right);
	return result;
}

int main()
{
	int n;
	while (cin >> n)
	{
		vector<int> v(n, 0);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		cout << get_inversion_num(v, 0, v.size()) << endl;
	}
}