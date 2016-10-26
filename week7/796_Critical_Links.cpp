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
#include <cstring>
#include <list>
using namespace std;

#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
// #define INF (1e300)
#define eps (1e-9)
#define MODULO 1000000007

// ifstream fin("796_input.txt");
// #define cin fin

typedef pair<int, int> II;
typedef vector<II> VII;

class Graph
{
  int V;
  list<int> * adj;
  void bridgeUtil(int u,
    vector<bool> & visited,
    vector<int> & disc,
    vector<int> & low,
    vector<int> & parent,
    int depth);

public:
  Graph(int V);
  void addEdge(int v, int w);
  void bridge();
  VII bridges;
};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
  bridges.resize(0);
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);
}

void Graph::bridgeUtil(int u,
  vector<bool> & visited,
  vector<int> & disc,
  vector<int> & low,
  vector<int> & parent,
  int depth) {
  
  static int time = 0;
  visited[u] = true;
  disc[u] = low[u] = ++time;
  for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
    int v = *i;
    if (!visited[v]) {
      parent[v] = u;
      bridgeUtil(v, visited, disc, low, parent, depth++);
      low[u] = min(low[u], low[v]);
      if (low[v] > disc[u]) {
        bridges.push_back(II(u, v));
      }
    } else if (v != parent[u]) {
      low[u] = min(low[u], disc[v]);
    }
  }
}

void Graph::bridge() {
  vector<bool> visited(V, false);
  vector<int> disc(V, 0);
  vector<int> low(V, 0);
  vector<int> parent(V, -1);

  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      bridgeUtil(i, visited, disc, low, parent, 0);
    }
  }
}

int main()
{
  int n;
  while (scanf("%d", &n) != -1) {
    Graph ag(n);
    for (int i = 0; i < n; i++) {
      int cur, num, next;
      scanf("%d (%d)", &cur, &num);
      for (int j = 0; j < num; j++) {
        scanf("%d", &next);
        ag.addEdge(cur, next);
        ag.addEdge(next, cur);
      }
    }
    ag.bridge();
    VII &bridges = ag.bridges;
    int num_dup = ((int)bridges.size());
    printf("%d critical link", num_dup);
    if (num_dup == 1) {
      printf("s\n");
    } else {
      printf("s\n");
    }
    for (int i = 0; i < bridges.size(); i++) {
      if (bridges[i].first > bridges[i].second) {
        int tmp = bridges[i].first;
        bridges[i].first = bridges[i].second;
        bridges[i].second = tmp;
      }
    }
    sort(bridges.begin(), bridges.end());
    for (int i = 0; i < bridges.size(); i++) {
      printf("%d - %d\n", bridges[i].first, bridges[i].second);
    }
    printf("\n");
    // scanf("%d", &n);
  }
}
