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

ifstream fin("11284_input.txt");
#define cin fin

struct dvd_info
{
	dvd_info(int id_store, double gain)
	{
		this->id_store = id_store;
		this->gain = gain;
	}

	int id_store;
	double gain;
};

int main()
{
	int tttt;
	cin >> tttt;
	while (tttt--)
	{
		int n, m;
		cin >> n >> m;
		vector<vector<double> > dist(n + 1, vector<double>(n + 1, INF));
		for (int i = 0; i < m; i++)
		{
			int s, t;
			double d;
			cin >> s >> t >> d;
			dist[s][t] = dist[t][s] = d;
		}
		
		for (int i = 0; i <= n; i++)
			dist[i][i] = 0;

		for (int k = 0; k <= n; k++)
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		int p;
		cin >> p;
		vector<dvd_info> dvd(p + 1, dvd_info(0, 0));
		for (int i = 1; i <= p; i++)
			cin >> dvd[i].id_store >> dvd[i].gain;

		vector<vector<double> > f(p + 1, vector<double>((1 << (p + 1)), -INF));
		
		f[0][1] = 0;

		for (int j = 3; j < (1 << (p + 1)); j++)
			for (int i = 1; i <= p; i++)
				for (int k = 0; k <= p; k++)
					if (i != k)
					{
						int to = 1 << i;
						int from = 1 << k;
						if ((to & j) && (from & j))
						{
							f[i][j] = max(f[i][j], f[k][j & (~to)] + dvd[i].gain - dist[dvd[k].id_store][dvd[i].id_store]);
							//f[i][j] = max(f[i][j], f[k][j] + dvd[i].gain - dist[dvd[k].id_store][dvd[i].id_store]);
						}
					}

		double result = -INF;
		for (int j = 1; j < (1 << (p + 1)); j++)
			for (int i = 1; i <= p; i++)
				result = max(result, f[i][j] - dist[dvd[i].id_store][0]);

		if (result <= 0)
			cout << "Don't leave the house" << endl;
		else
			printf("Daniel can save $%.2f\n", result);
	}
}
