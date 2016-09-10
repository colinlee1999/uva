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

ifstream fin("11631_input.txt");
#define cin fin

typedef vector<int> ele;

struct
{
	bool operator()(const ele & a, const ele & b)
	{
		return a[2] < b[2];
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
	cin >> m >> n;
	while (m && n)
	{
		vector<ele> edges;
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			edges.push_back(ele(3, 0));
			for (int j = 0; j <= 2; j++)
				cin >> edges[i][j];
			sum += edges[i][2];
		}
		sort(edges.begin(), edges.end(), my_comp_0);
		vector<int> union_find_set(m, 0);
		for (int i = 0; i < m; i++)
			union_find_set[i] = i;
		
		int mst = 0;
		for (auto it : edges)
		{
			int fa1, fa2;
			fa1 = get_father(it[0], union_find_set);
			fa2 = get_father(it[1], union_find_set);
			if (fa2 != fa1)
			{
				mst += it[2];
				union_find_set[fa2] = fa1;
			}
		}
		cout << sum - mst << endl;
		cin >> m >> n;
	}
}
