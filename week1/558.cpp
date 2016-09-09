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

ifstream fin("558_input.txt");
#define cin fin

typedef vector<int> ele;

int main()
{
	int n, m, tttt = 0;
	cin >> tttt;
	int cases = 1;
	while (tttt--)
	{
		int n, m;
		cin >> n >> m;
		vector<ele> edges;
		for (int i = 0; i < m; i++)
		{
			int v1, v2, len;
			cin >> v1 >> v2 >> len;
			edges.push_back(ele(3, 0));
			edges[i][0] = v1;
			edges[i][1] = v2;
			edges[i][2] = len;
		}

		vector<int> dist(n, UNREACHABLE);
		dist[0] = 0;

		for (int i = 1; i < n; i++)
			for (auto it : edges)
			{
				int s = it[0];
				int t = it[1];
				int len = it[2];
				if (dist[s] + len < dist[t])
					dist[t] = dist[s] + len;
			}

		bool possible = false;
		for (auto it : edges)
		{
			int s = it[0];
			int t = it[1];
			int len = it[2];
			if (dist[s] + len < dist[t])
			{
				possible = true;
				break;
			}
		}
		if (possible)
			cout << "possible" << endl;
		else
			cout << "not possible" << endl;
	}
}
