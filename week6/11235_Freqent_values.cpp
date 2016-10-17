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

ifstream fin("11235_input.txt");
#define cin fin
#define MAXM

class SegmentTree
{
public:
	int filter(int a) {
		return a;
	}

	int calc(int a, int b) {
		return max(a,b);
	}

	vector<int> st;
	int unit;

	SegmentTree(vector<int> & arr, int n) {
		unit = 0;
		int x = ceil(log(n) / log(2));
		int max_size = 2 * (1 << x) - 1;
		st = vector<int>(max_size, 0);
		constructSTUtil(arr, 0, n - 1, 0);
	}

	int constructSTUtil(vector<int> & arr, int ss, int se, int si) {
		if (ss == se) {
			st[si] = filter(arr[ss]);
			return st[si];
		}

		int mid = ss + (se - ss) / 2;
		int a = constructSTUtil(arr, ss, mid, si * 2 + 1);
		int b = constructSTUtil(arr, mid + 1, se, si * 2 + 2);
		st[si] = calc(a, b);
		return st[si];
	}

	int get_query(int ss, int se, int qs, int qe, int si) {
		if (qs <= ss && qe >= se) {
			return st[si];
		}
		if (se < qs || ss > qe)
			return unit;
		int mid = ss + (se - ss) / 2;
		int a = get_query(ss, mid, qs, qe, 2 * si + 1);
		int b = get_query(mid + 1, se, qs, qe, 2 * si + 2);
		return calc(a, b);
	}

	void output() {
		for (auto it : st) {
			cout << it << ' ';
		}
		cout << endl;
	}
};

int main()
{
	int n, q;
	cin >> n;
	
	while (n) {
		vector<int> v(n, 0);
		int min_a, max_a;
		min_a = INT_MAX;
		max_a = INT_MIN;
		cin >> q;
		for (int i = 0; i < n; i++) {
			cin >> v[i];
			min_a = min(min_a, v[i]);
			max_a = max(max_a, v[i]);
		}
	
		int clen = max_a - min_a + 1;
		vector<int> c(clen, 0);

		for (int i = 0; i < n; i++) {
			v[i] -= min_a;
			c[v[i]]++;
		}

		vector<int> start(n, 0);
		vector<int> end(n, 0);
		
		int last_num = -1;
		int last_index = 0;
		for (int i = 0; i < n; i++) {
			if (v[i] != last_num) {
				last_num = v[i];
				last_index = i;
			}
			start[i] = last_index;
		}

		last_num = -1;
		last_index = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (v[i] != last_num) {
				last_num = v[i];
				last_index = i;
			}
			end[i] = last_index;
		}

		/**********************debug begin**********************/
		// for (int i = 0; i < n; i++) {
		// 	cout << start[i] << ' ';
		// }
		// cout << endl;

		// for (int i = 0; i < n; i++) {
		// 	cout << end[i] << ' ';
		// }
		// cout << endl;

		// for (int i = 0; i < n; i++) {
		// 	cout << v[i] << ' ';
		// }
		// cout << endl;

		// for (int i = 0; i < clen; i++) {
		// 	cout << c[i] << ' ';
		// }
		// cout << endl;
		/**********************debug end***********************/

		SegmentTree tree(c, clen);
		// tree.output();

		int l, r;
		int ll, rr;
		for (int i = 0; i < q; i++) {
			int result = 0;
			cin >> l >> r;
			l--;
			r--;
			if (v[l] == v[r]) {
				result = r - l + 1;
			} else {
				ll = end[l] + 1;
				rr = start[r] - 1;
				// cout << l << ' ' << r << endl;
				// cout << ll << ' ' << rr << endl;
				result = max(result, ll - l);
				result = max(result, r - rr);
				if (ll <= rr) {
					// cout << "here" << endl;
					// cout << v[ll] << endl;
					// cout << v[rr] << endl;
					// cout << "there" << endl;
					result = max(result, tree.get_query(0, clen - 1, v[ll], v[rr], 0));
				}
			}
			cout << result << endl;
		}

		cin >> n;
	}
}
