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

ifstream fin("10090_input.txt");
#define cin fin

struct Triple
{
	Triple(long long a, long long b, long long c) {
		d = a;
		x = b;
		y = c;
	}

	long long d;
	long long x;
	long long y;
};

Triple extended_euclid(long long a, long long b) {
	if (b == 0)
		return Triple(a, 1, 0);
	else {
		Triple t = extended_euclid(b, a % b);
		return Triple(t.d, t.y, t.x - a / b * t.y);
	}
}

int main()
{
	int n, c1, c2, n1, n2;
	cin >> n;
	while (n != 0) {
		cin >> c1 >> n1;
		cin >> c2 >> n2;

		Triple t = extended_euclid(n1, n2);
		long long lcm = n1 * n2 / t.d;

		if (n % t.d !=0) {
			cout << "failed" << endl;
		} else {
			int tmp = n / t.d;
			t.x *= tmp;
			t.y *= tmp;
			if (t.x < 0) {
				tmp = lcm / n2;
				abs(t.x) / (lcm / n2)
			} else if (t.y < 0) {

			}

		}

		cin >> n;
	}
}
