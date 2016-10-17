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

ifstream fin("12532_input.txt");
#define cin fin

class SegmentTree
{
public:
	int filter(int a) {
		if (a > 0) return 1;
		if (a < 0) return -1;
		return 0;
	}

	int calc(int a, int b) {
		return a * b;
	}

	vector<int> st;
	int unit;

	SegmentTree(vector<int> & arr, int n) {
		unit = 1;
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
			// if (qs == 0 && qe == 3) {
			// 	cout << "++++++++++++++" << endl;
			// 	cout << st[si] << endl;
			// 	cout << "--------------" << endl;
			// }
			return st[si];
		}
		if (se < qs || ss > qe)
			return unit;
		int mid = ss + (se - ss) / 2;
		int a = get_query(ss, mid, qs, qe, 2 * si + 1);
		int b = get_query(mid + 1, se, qs, qe, 2 * si + 2);
		return calc(a, b);
	}

	int query(int n, int qs, int qe) {
		return get_query(0, n - 1, qs, qe, 0);
	}

	int update(int ss, int se, int i, int new_number, int si) {
		if (i < ss || i > se) {
			return st[si];
		}
		if (se != ss) {
			int mid = ss + (se - ss) / 2;
			int a = update(ss, mid, i, new_number, 2 * si + 1);
			int b = update(mid + 1, se, i, new_number, 2 * si + 2);
			st[si] = calc(a, b);
		} else {
			st[si] = filter(new_number);
		}
		return st[si];
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
	int n, k;
	while (cin >> n >> k) {
		vector<int> a(n, 0);
		for (int i = 0; i < n; i++)
			cin >> a[i];
		SegmentTree tree(a, n);
		string s;
		int l, r;
		for (int i = 0; i < k; i++) {
			// tree.output();
			cin >> s >> l >> r;
			switch (s[0]) {
				case 'C':
					tree.update(0, n - 1, l - 1, r, 0);
					break;
				case 'P':
				{
					int tmp = tree.get_query(0, n - 1, l - 1, r - 1, 0);
					// printf("tmp: %d\n", tmp);
					string ts;
					switch (tmp) {
						case 1:
							ts = "+";
							break;
						case -1:
							ts = "-";
							break;
						case 0:
							ts = "0";
						default:
							break;
					}
					// cout << '[' << ts << ']';
					cout << ts;
				}
					break;
				default:
					break;
			}
		}
		cout << endl;
	}
}
