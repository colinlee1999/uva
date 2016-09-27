#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define eps (1e-9)
using namespace std;

ifstream fin("12238_input.txt");
#define cin fin

struct q_ele
{
	q_ele(int next, int qid)
	{
		this->next = next;
		this->qid = qid;
	}

	int next;
	int qid;
};

typedef unordered_map<int, set<pair<int, long long> > > graph;
typedef vector<vector<q_ele> > query;

int father(int x, vector<int> & unionfind)
{
	vector<int> path;
	while (x != unionfind[x])
	{
		path.push_back(x);
		x = unionfind[x];
	}
	for (auto it : path)
		unionfind[it] = x;
	return x;
}

int merge(int x, int y, vector<int> & unionfind)
{
	y = father(y, unionfind);
	x = father(x, unionfind);
	unionfind[y] = x;
}

void tarjan(
	int cur,
	long long d,
	graph & g,
	query & q,
	vector<bool>& visited,
	vector<long long>& depth,
	vector<int>& unionfind,
	vector<long long> & result)
{
	depth[cur] = d;
	for (auto it : g[cur])
	{
		tarjan(it.first, d + it.second,
			g, q, visited, depth, unionfind, result);
		merge(cur, it.first, unionfind);
	}
	visited[cur] = true;
	for (auto it : q[cur])
	{
		if (visited[it.next])
		{
			long long temp = depth[cur] + depth[it.next] - depth[father(it.next, unionfind)] * 2;
			//cout << temp << "=" << depth[cur] << "+" << depth[it.next] << "-" << depth[father(it.next, unionfind)] << "*2" << endl;
			result[it.qid] = temp;
		}
		else
			q[it.next].push_back(q_ele(cur, it.qid));
	}
}

int main()
{
	int N;
	cin >> N;
	while (N != 0)
	{
		graph g;
		for (int i = 1; i < N; i++)
		{
			int A, L;
			cin >> A >> L;
			if (g.count(A) == 0)
				g[A] = set<pair<int, long long>>();
			g[A].insert(pair<int, long long>(i, L));
		}
		
		query q(N, vector<q_ele>());

		int Q;
		cin >> Q;
		for (int i = 0; i < Q; i++)
		{
			int S, T;
			cin >> S >> T;
			q[S].push_back(q_ele(T, i));
		}

		vector<bool> visited(N, false);
		vector<long long> depth(N, 0);
		vector<int> unionfind(N, 0);
		for (int i = 0; i < N; i++)
			unionfind[i] = i;

		vector<long long> result(Q, 0);
		tarjan(0, 0,
			g, q, visited, depth, unionfind, result);

		cout << result[0];
		for (int i = 1; i < Q; i++)
			cout << ' ' << result[i];
		cout << endl;

		cin >> N;
	}
}
