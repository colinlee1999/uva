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
#define INF (1e300)
#define eps (1e-9)
#define MODULO 1000000007

ifstream fin("11402_input.txt");
#define cin fin

#define MAX_LEN 1048576

#define F 1
#define E 2
#define I 3

class LazySegmentTree {
public:
	vector<int> tree;
	vector<int> lazy;
	int n;
	int unit;

	int filter(char ch) {
		return ch - '0';
	}

	int get_mid(int a, int b) {
		return a + (b - a) / 2;
	}

	int calc(int a, int b) {
		return a + b;
	}

	LazySegmentTree(string & s, int nn) {
		n = nn;
		unit = 0;
		int x = ceil(log(n) / log(2));
		tree = vector<int>(2 * (1 << x) - 1, 0);
		lazy = vector<int>(2 * (1 << x) - 1, 0);
		constructSTUtil(s, 0, n - 1, 0);
	}

	int constructSTUtil(string & s, int ss, int se, int si) {
		if (ss > se)
			return unit;
		if (ss == se) {
			tree[si] = filter(s[ss]);
			return tree[si];
		}

		int mid = get_mid(ss, se);
		int a = constructSTUtil(s, ss, mid, si * 2 + 1);
		int b = constructSTUtil(s, mid + 1, se, si * 2 + 2);
		tree[si] = calc(a, b);
		return tree[si];
	}

	void ease_lazy(int ss, int se, int si) {
		switch(lazy[si]) {
				case F:
					tree[si] = se - ss + 1;
					break;
				case E:
					tree[si] = 0;
					break;
				case I:
					tree[si] = se - ss + 1 - tree[si];
					break;
				default:
					break;
			}
		if (ss != se) {
			int cur;
			switch (lazy[si]) {
				case F:
					lazy[si * 2 + 1] = F;
					lazy[si * 2 + 2] = F;
					break;
				case E:
					lazy[si * 2 + 1] = E;
					lazy[si * 2 + 2] = E;
					break;
				case I:
					cur = si * 2 + 1;
					switch (lazy[cur]) {
						case F:
							lazy[cur] = E;
							break;
						case E:
							lazy[cur] = F;
							break;
						case I:
							lazy[cur] = 0;
							break;
						default:
							lazy[cur] = lazy[si];
							break;
					}
					cur = si * 2 + 2;
					switch (lazy[cur]) {
						case F:
							lazy[cur] = E;
							break;
						case E:
							lazy[cur] = F;
							break;
						case I:
							lazy[cur] = 0;
							break;
						default:
							lazy[cur] = lazy[si];
							break;
					}
					break;
				default:
					break;
			}
		}
		lazy[si] = 0;
	}

	int get_sum(int qs, int qe) {
		return getSumUtil(0, n - 1, qs, qe, 0);
	}

	int getSumUtil(int ss, int se, int qs, int qe, int si) {
		// printf("si: %d\tlazy[si]: %d\n", si, lazy[si]);
		// printf("si: %d\ttree[si]: %d\n", si, tree[si]);

		if (lazy[si]) {
			ease_lazy(ss, se, si);
		}
		// printf("si: %d\ttree[si]: %d\n", si, tree[si]);

		if (ss > qe || se < qs)
			return unit;
		if (ss >= qs && se <= qe)
			return tree[si];
		int mid = get_mid(ss, se);
		int a = getSumUtil(ss, mid, qs, qe, 2 * si + 1);
		int b = getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
		// printf("si: %d\ta: %d\tb: %d\n", si, a, b);
		return calc(a, b);
	}

	int updateRange(int us, int ue, int mode) {
		updateRangeUtil(0, n-1, us, ue, 0, mode);
	}

	int updateRangeUtil(int ss, int se, int us, int ue, int si, int mode) {
		// printf("si: %d\tlazy[si]: %d\n", si, lazy[si]);
		// printf("si: %d\ttree[si]: %d\n", si, tree[si]);
		if (lazy[si]) {
			ease_lazy(ss, se, si);
		}
		// printf("si: %d\ttree[si]: %d\n", si, tree[si]);

		if (ss> ue || se < us) {
			return tree[si];
		}
		
		if (ss >= us && se <= ue) {
			lazy[si] = mode;
			ease_lazy(ss, se, si);
			return tree[si];
		}

		int mid = get_mid(ss, se);
		int a = updateRangeUtil(ss, mid, us, ue, si * 2 + 1, mode);
		int b = updateRangeUtil(mid + 1, se, us, ue, si * 2 + 2, mode);
		tree[si] = calc(a, b);
		// printf("si: %d\ta: %d\tb: %d\n", si, a, b);
		return tree[si];
	}

	void output() {
		printf("[");
		for (auto it : tree) {
			printf("%d,", it);
		}
		printf("]\n");
	}

};

int main()
{
	int tttt;
	cin >> tttt;
	int case_count = 0;
	string pirates;
	pirates.resize(MAX_LEN);
	while (tttt--) {
		case_count++;
		printf("Case %d:\n", case_count);
		int M, Q;
		cin >> M;
		int nn = 0;
		for (int i = 0; i < M; i++) {
			int t;
			string s;
			cin >> t;
			cin >> s;
			while (t--) {
				int j = 0;
				while (j < s.length()) {
					pirates[nn++] = s[j++];
					// cout << j <<' ';
				} 
				// cout << endl;
			}
			// cout << "yes" << endl;
		}
		// cout << pirates << endl;
		LazySegmentTree stree(pirates, nn);
		cin >> Q;
		int query_count = 0;
		for (int i = 0; i < Q; i++) {
			string ch;
			int a, b;
			cin >> ch >> a >> b;
			switch(ch[0]) {
				case 'F':
					stree.updateRange(a, b, F);
					break;
				case 'E':
					stree.updateRange(a, b, E);
					break;
				case 'I':
					stree.updateRange(a, b, I);
					break;
				case 'S':
					printf("Q%d: %d\n", ++query_count, stree.get_sum(a, b));
					break;
			}
			// stree.output();
		}
	}
}
