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
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define eps (1e-9)
using namespace std;

ifstream fin("1111_input.txt");
#define cin fin

struct Line {
	Line(long long x1, long long y1, long long x2, long long y2) {
		this->A = y1 - y2;
		this->B = x2 - x1;
		this->C = x1 * (y2 - y1) - y1 * (x2 - x1);
		denominator = sqrt((double)A * A + B * B);
	}

	double distToPoint(long long x, long long y) {
		double numerator = abs((double)A * x + B * y + C);
		return numerator / denominator;
	}

	long long getPointDir(long long x, long long y) {
		return A * x + B * y + C;
	}

	long long A, B, C;
	double denominator;
};

int main()
{
	int n;
	int case_count = 0;
	cin >> n;
	while (n != 0) {
		vector<long long> x(n, 0), y(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> x[i] >> y[i];
		}

		double result = INF;

		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++) {
				Line l = Line(x[i], y[i], x[j], y[j]);
				vector<long long> v(n, 0);
				for (int k = 0; k < n; k++) {
					v[k] = l.getPointDir(x[k], y[k]);
				}
				int positive, negative;
				positive = negative = 0;
				for (int k = 0; k < n; k++)
					if (v[k] != 0) {
						if (v[k] > 0) positive++;
						else negative++;
					}
				if (positive > 0 && negative > 0) continue;
				double tmp_max = 0;
				for (int k = 0; k < n; k++) {
					double tmp = l.distToPoint(x[k], y[k]);
					tmp_max = max(tmp_max, tmp);
				}
				result = min(tmp_max, result);
			}

		case_count++;
		// result = ceil(100 * result) / 100;
		printf("Case %d: %.2f\n", case_count, result);

		cin >> n;
	}
}
