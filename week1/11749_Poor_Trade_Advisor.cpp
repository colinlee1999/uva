#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("11749_input.txt");
#define cin fin

typedef vector<int> ele;

struct
{
	bool operator()(const ele & a, const ele & b)
	{
		return a[2] > b[2];
	}
} my_comp_0;

int get_father(int p, vector<int> & union_find_set)
{
	int p_backup = p;
	while (union_find_set[p] != p)
		p = union_find_set[p];
	union_find_set[p_backup] = p;
	return p;
}

int main()
{
	int n, m;
	cin >> n >> m;
	while (n && m)
	{
		vector<ele> edges;
		int largest_ppa = INT_MIN;
		for (int i = 0; i < m; i++)
		{
			edges.push_back(ele(3, 0));
			for (int j = 0; j <= 2; j++)
				cin >> edges[i][j];
			largest_ppa = max(largest_ppa, edges[i][2]);
		}
		sort(edges.begin(), edges.end(), my_comp_0);
		vector<int> union_find_set(n + 1, 0);
		for (auto it : edges)
		{
			if (it[2] != largest_ppa) break;
			union_find_set[it[0]] = it[0];
			union_find_set[it[1]] = it[1];
		}
		for (auto it : edges)
		{
			if (it[2] != largest_ppa) break;
			int fa1 = get_father(it[0], union_find_set);
			int fa2 = get_father(it[1], union_find_set);
			if (fa1 != fa2)
				union_find_set[fa2] = fa1;
		}
		
		unordered_map<int, int> statistics;
		for (int i = 1; i <= n; i++)
		{
			int fa = get_father(i, union_find_set);
			if (fa==0) continue;
			if (statistics.count(fa) == 0)
				statistics[fa] = 1;
			else
				statistics[fa]++;
		}

		int result = 0;
		for (auto it : statistics)
			result = max(result, it.second);

		cout << result << endl;
		cin >> n >> m;
	}
}
