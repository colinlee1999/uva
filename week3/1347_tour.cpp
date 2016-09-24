#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#include <cmath>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
using namespace std;

ifstream fin("1347_input.txt");
#define cin fin

struct point
{
	point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int x, y;
};

double get_dist(point a, point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main()
{
	int n;
	while (cin >> n)
	{
		vector<point> v(n, point(0, 0));
		for (int i = 0; i < n; i++)
			cin >> v[i].x >> v[i].y;
		vector<vector<double> > f(n, vector<double>(n, INF));
		vector<vector<double> > dist(n, vector<double>(n, 0));
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				dist[j][i] = dist[i][j] = get_dist(v[i], v[j]);

		for (int i = 0; i < n; i++)
			f[n - 1][i] = dist[n - 1][i];
		for (int i = n - 2; i >= 0; i--)
			for (int j = i; j >= 0; j--)
			{
				f[i][j] = min(f[i + 1][j] + dist[i + 1][i], f[i + 1][i] + dist[i + 1][j]);
			}

		printf("%.2f\n", f[0][0]);
	}
}
