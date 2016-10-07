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

ifstream fin("10777_input.txt");
#define cin fin

int main()
{
	int tttt;
	int case_count = 0;
	cin >> tttt;
	while (tttt--) {
		case_count++;
		int n;
		cin >> n;
		vector<double> a(n, 0);
		vector<double> p(n, 0);
		double prob_exit = 0;
		double numerator = 0;
		double denominator = 1;
		for (int i = 0; i < n; i++) {
			cin >> a[i] >> p[i];
			numerator += abs(a[i]) * p[i];
			if (a[i] < 0) denominator -= p[i];
			if (a[i] > 0) prob_exit += p[i];
		}
		if (prob_exit == 0) {
			printf("Case %d: God! Save me\n", case_count);
		}
		else {
			double result = numerator / denominator;
			printf("Case %d: %.2f\n", case_count, result);
		}
	}
}
