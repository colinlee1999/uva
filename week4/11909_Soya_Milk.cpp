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

ifstream fin("11909_input.txt");
#define cin fin

#define PI (3.1415926535897932384626)

int main()
{
	double l, w, h;
	double theta;
	double result;
	while (cin >> l >> w >> h >> theta) {
		result = w;
		if (h > tan(theta * PI / 180) * l) {
			result *= l * h - l * l * tan(theta * PI / 180) / 2;
		}
		else {
			result *= h * h / tan(theta * PI / 180) / 2;
		}
		printf("%.3f mL\n", result);
	}
}
