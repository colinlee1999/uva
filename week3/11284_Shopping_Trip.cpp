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
#define UNREACHABLE (INT_MAX>>1)
#define INF (1e300)
#define eps (1e-9)
using namespace std;

// #define VD vector<double>
// #define VVD vector<VD>
#define VI vector<int>
#define VVI vector<VI>

#define pos(i) (1 << i)
#define unmark(s, to) (s & (~to))

int main()
{
	int tttt;
	scanf("%d", &tttt);
	int N, M, P;
	while (tttt--) {
		scanf("%d %d", &N, &M);
		// VVD graph(N + 1, VD(N + 1, INF));
		VVI graph(N + 1, VI(N + 1, UNREACHABLE));
		for (int i = 0; i < M; i++) {
			int a, b;
			int c, d;
			scanf("%d %d %d.%d", &a, &b, &c, &d);
			graph[a][b] = graph[b][a] = min(graph[a][b], c * 100 + d);
		}
		// floyd
		for (int i = 0; i <= N; i++) {
			graph[i][i] = 0;
		}
		for (int k = 0; k <= N; k++)
			for (int i = 0; i <= N; i++)
				for (int j = 0; j <= N; j++)
					graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);

		// for (int i = 0; i <= N; i++, printf("\n"))
		// 	for (int j = 0; j <= N; j++) {
		// 		printf("%.2f ", graph[i][j]);
		// 	}

		scanf("%d", &P);
		VI value(N + 1, 0);
		for (int i = 0; i < P; i++) {
			int a;
			int c, d;
			scanf("%d %d.%d", &a, &c, &d);
			value[a] += 100 * c + d;
		}
		VI node;
		for (int i = 0; i <= N; i++)
			if (value[i] > 0) {
				node.push_back(i);
			}
		P = node.size();
		
		// for (int i = 0; i <= N; i++) {
		// 	printf("value %d: %.2f\n", i, value[i]);
		// }

		// for (auto it : node) {
		// 	printf("%d ", it);
		// }
		// printf("\n");

		int status_max = 1 << P;
		VVI f(P, VI(status_max, INT_MIN));
		for (int i = 0; i < P; i++) {
			f[i][pos(i)] = -graph[0][node[i]] + value[node[i]];
		}

		for (int s = 3; s < status_max; s++)
			for (int i = 0; i < P; i++)
				for (int j = 0; j < P; j++) {
					if (i == j) continue;
					int to = pos(i);
					int from = pos(j);
					if ((s & to) && (s & from)) {
						int fs = unmark(s, to);
						f[i][s] = max(f[i][s], f[j][fs] - graph[node[j]][node[i]] + value[node[i]]);
					}
				}

		int result = 0;
		for (int s = 1; s < status_max; s++)
			for (int i = 0; i < P; i++) {
				int to = pos(i);
				if (s & to) {
					result = max(result, f[i][s] - graph[node[i]][0]);
				}
			}
		if (result <= 0) {
			printf("Don't leave the house\n");
		} else {
			printf("Daniel can save $%d.%02d\n", result / 100, result % 100);
		}
	}
}
