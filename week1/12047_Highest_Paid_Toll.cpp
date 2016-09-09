#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("12047_input.txt");
// #define cin fin

typedef vector<int> ele;

struct
{
	bool operator()(const ele & first, const ele & second)
	{
		return first[0] < second[0];
	}
} my_comp_0;

void spfa(int n, int m, int s, int t, vector<int> & index, vector<ele> & edges, vector<int> & total_toll)
{
	vector<bool> inq(n + 1, false);
	total_toll.resize(n + 1);
	fill(total_toll.begin(), total_toll.end(), UNREACHABLE);
	queue<int> q;
	q.push(s);
	inq[s] = true;
	total_toll[s] = 0;
	while (!q.empty())
	{
		int cur_node = q.front();
		for (int i = index[cur_node]; i < m; i++)
		{
			if (edges[i][0] != cur_node) break;
			int out_node = edges[i][1];
			int toll = edges[i][2];
			if (total_toll[cur_node] + toll <= total_toll[out_node])
			{
				total_toll[out_node] = total_toll[cur_node] + toll;
				if (!inq[out_node])
				{
					q.push(out_node);
					inq[out_node] = true;
				}
			}
		}
		q.pop();
		inq[cur_node] = false;
	}
}

void get_index(int n, int m, vector<ele> & edges, vector<int> & index)
{
	index.resize(n + 1);
	fill(index.begin(), index.end(), m);
	for (int i = 0; i < m; i++)
	{
		if (index[edges[i][0]] == m)
			index[edges[i][0]] = i;
	}
}

void read_edges(int m, vector<ele> & edges)
{
	int v1, v2, toll;
	edges.clear();
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2 >> toll;
		edges.push_back(ele(3,0));
		edges[i][0] = v1;
		edges[i][1] = v2;
		edges[i][2] = toll;
	}
}

void reverse_edges(vector<ele> & edges)
{
	for (auto it = edges.begin(); it != edges.end(); it++)
		swap((*it)[0], (*it)[1]);
}

int main()
{
	int n, m, tttt = 0;
	cin >> tttt;
	while (tttt--)
	{
		int n, m, s, t, p;
		cin >> n >> m >> s >> t >> p;
		
		vector<ele> edges;
		read_edges(m, edges);
		sort(edges.begin(), edges.end(), my_comp_0);

		vector<int> index;
		get_index(n, m, edges, index);
		
		vector<int> forward_total_toll;
		spfa(n, m, s, t, index, edges, forward_total_toll);
		if (forward_total_toll[t] > p)
		{
			cout << "-1" << endl;
		}
		else
		{
			// cout << "================" << endl;
			vector<int> backward_total_toll;
			reverse_edges(edges);
			sort(edges.begin(), edges.end(), my_comp_0);
			get_index(n, m, edges, index);
			// for (auto it : index)
			// 	cout << it << endl;
			spfa(n, m, t, s, index, edges, backward_total_toll);

			int result = 0;

			// cout << forward_total_toll[t] << endl;
			// cout << backward_total_toll[s] << endl;

			int v1, v2, toll;
			for (auto it : edges)
			{
				v1 = it[1];
				v2 = it[0];
				toll = it[2];
				if (forward_total_toll[v1] + toll + backward_total_toll[v2] <= p)
					result = max(result, toll);
			}
			cout << result << endl;
		}
	}
}
