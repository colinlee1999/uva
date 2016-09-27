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
#define eps (1e-9)
using namespace std;

ifstream fin("11284_input.txt");
//#define cin fin

struct dvd_info
{
	dvd_info(int id_store, long long gain)
	{
		this->id_store = id_store;
		this->gain = gain;
	}

	int id_store;
	long long gain;
};

int main()
{
	int tttt;
	scanf("%d", &tttt);
	while (tttt--)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		vector<vector<long long> > dist(n + 1, vector<long long>(n + 1, INT_MAX));
		for (int i = 0; i < m; i++)
		{
			int s, t;
			long long d1, d2;
			scanf("%d %d %lld.%lld", &s, &t, &d1, &d2);
			// cout << "debug:\t" << d1 << d2 << endl;
			dist[s][t] = dist[t][s] = d1 * 100 + d2;
		}
		
		for (int i = 0; i <= n; i++)
			dist[i][i] = 0;

		for (int k = 0; k <= n; k++)
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		int p;
		scanf("%d", &p);
		vector<dvd_info> dvd(p, dvd_info(0, 0));
		for (int i = 0; i < p; i++)
		{
			long long d1, d2;
			scanf("%d %lld.%lld", &dvd[i].id_store, &d1, &d2);
			dvd[i].gain = d1 * 100 + d2;
		}

		vector<vector<long long> > f(p, vector<long long>((1 << (p)), INT_MIN));

		for (int i = 0; i < p; i++)
			f[i][1 << i] = - dist[dvd[i].id_store][0] + dvd[i].gain;

		vector< pair<int, int> > o;
		for (int i = 0; i < (1 << (p)); i++) {
			o.push_back(make_pair(__builtin_popcount(i), i));
		}
		sort(o.begin(), o.end());
		
		for (int j = 3; j < (1 << (p)); j++)
			for (int i = 0; i < p; i++) // to position i
			{
				int to = 1 << i;
				for (int k = 0; k < p; k++) // from position k
					if (i != k && f[k][j & (~to)] != INT_MIN)
					{
						int from = 1 << k;
						if ((to & j) && (from & j)) // j contains to and from
						{
							f[i][j] = max(f[i][j], f[k][j & (~to)] + dvd[i].gain - dist[dvd[k].id_store][dvd[i].id_store]);
							//f[i][j] = max(f[i][j], f[k][j] + dvd[i].gain - dist[dvd[k].id_store][dvd[i].id_store]);
						}
					}
			}

		long long result = 0;
		for (int j = 0; j < (1 << (p)); j++)
			for (int i = 0; i < p; i++)
				if (f[i][j] != INT_MIN)
					result = max(result, f[i][j] - dist[dvd[i].id_store][0]);

		if (result <= 0)
			printf("Don't leave the house\n");
		else
			printf("Daniel can save $%lld.%02lld\n", result / 100, result % 100);
	}
}
