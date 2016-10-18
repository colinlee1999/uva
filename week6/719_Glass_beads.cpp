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

ifstream fin("719_input.txt");
#define cin fin

int main()
{
	int tttt;
	cin >> tttt;
	while (tttt--) {
		string s;
		cin >> s;
		int slen = s.length();
		s = s + s;
		int i = 0;
		int j = 1;
		int count = 0;
		while (i < slen && j < slen && count < slen) {
			if (s[i + count] == s[j + count])
				count++;
			else
			{
				if (s[i + count] > s[j + count]) {
					i = i + count + 1;
				} else {
					j = j + count + 1;
				}
				if (i == j)
					j++;
				count = 0;
			}
		}
		cout << min(i, j) + 1 << endl;
	}
}
