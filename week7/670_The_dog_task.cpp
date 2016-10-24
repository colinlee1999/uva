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
using namespace std;

#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
// #define INF (1e300)
#define eps (1e-9)
#define MODULO 1000000007

ifstream fin("670_input.txt");
#define cin fin

// BEGIN
// This code performs maximum (cardinality) bipartite matching.
// Does not support weighted edges.
//
// Running time: O(|E| |V|) -- often much faster in practice
//
//   INPUT: adj_list[i][j] = edge between row node i and column node adj_list[i][j]
//          mr[i] = vector of size #rows, initialized to -1
//          mc[j] = vector of size #columns, initialized to -1
//          
//   OUTPUT: mr[i] = assignment for row node i, -1 if unassigned
//           mc[j] = assignment for column node j, -1 if unassigned
//           function returns number of matches made

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;
typedef pair<int, int> P;
typedef vector<P> VP;

bool FindMatch(int i, const VVI &adj_list, VI &mr, VI &mc, VB &seen) {
  for (int j = 0; j < adj_list[i].size(); j++) {
    int item = adj_list[i][j];
    if (!seen[item]) {
      seen[item] = true;
      if (mc[item] < 0 || FindMatch(mc[item], adj_list, mr, mc, seen)) {
        mr[i] = item;
        mc[item] = i;
        return true;
      }
    }
  }
  return false;
}

// mr should be a vector of size number of row items, initialized to -1
// mc should be a vector of size number of column items, initialized to -1
int BipartiteMatching(const VVI &adj_list, VI &mr, VI &mc) {
  int ct = 0;
  for (int i = 0; i < adj_list.size(); i++) {
    VB seen(mc.size(), false);
    if (FindMatch(i, adj_list, mr, mc, seen)) ct++;
  }
  return ct;
}
// END

double get_len(P &a, P &b) {
  int d1 = (a.first - b.first);
  int d2 = (a.second - b.second);
  return sqrt(d1 * d1 + d2 * d2);
}

int main()
{
  int tttt;
  cin >> tttt;
  int N, M;
  while (tttt--) {
    cin >> N >> M;
    VVI adj_list(N + M, VI());
    VP route(N, P(0, 0));
    VP dots(M, P(0, 0));
    for (int i = 0; i < N; i++) {
      cin >> route[i].first >> route[i].second;
    }
    for (int i = 0; i < M; i++) {
      cin >> dots[i].first >> dots[i].second;
    }
    for (int i = 0; i < N - 1; i++) {
      double base_len = get_len(route[i], route[i + 1]);
      for (int j = 0; j < M; j++) {
        double len1 = get_len(route[i], dots[j]);
        double len2 = get_len(dots[j], route[i + 1]);
        if (len1 + len2 < 2 * base_len + eps) {
          adj_list[i].push_back(N + j);
          adj_list[N + j].push_back(i);
        }
      }
    }

    // for (int i = 0; i < N + M; i++, cout << endl) {
    //   printf("node %d:", i);
    //   for (int j = 0; j < adj_list[i].size(); j++) {
    //     printf(" %d", adj_list[i][j]);
    //   }
    // }

    VI mr(N + M, -1);
    VI mc(N + M, -1);
    int result = BipartiteMatching(adj_list, mr, mc);

    // for (int i = 0; i < N + M; i++)
    //   printf("mr[%d]: %d\n", i, mr[i]);

    // for (int i = 0; i < N + M; i++)
    //   printf("mc[%d]: %d\n", i, mc[i]);

    cout << result / 2 + route.size() << endl;
    int cx, cy;
    cx = route[0].first;
    cy = route[0].second;
    cout << cx << ' ' << cy;
    int i = 0;
    do {
      if (mr[i] != -1) {
        int j = mr[i] - N;
        cout << ' ' << dots[j].first << ' ' << dots[j].second;
      }
      i++;
      cx = route[i].first;
      cy = route[i].second;
      cout << ' ' << cx << ' ' << cy;
    } while (i != N - 1);
    cout << endl;

    if (tttt != 0)
      cout << endl;
  }
}
