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

ifstream fin("10394_input.txt");
#define cin fin

int main()
{
	int plen = 20000001;
	vector<bool> prime(plen, true);
	prime[0] = prime[1] = false;
	for (int i = 2; i < plen; i++)
		if (prime[i]) {
			for (int j = i + i; j < plen; j += i)	 {
				prime[j] = false;
			}
		}

	int pplen = 100001;
	vector<pair<int, int> > p_pairs(pplen, pair<int, int>());
	int count = 1;
	for (int i = 5; i < plen; i++)
		if (prime[i] && prime[i - 2]) {
			p_pairs[count++] = pair<int, int>(i - 2, i);
			if (count >= pplen) break;
		}

	int n;
	while (cin >> n) {
		printf("(%d, %d)\n", p_pairs[n].first, p_pairs[n].second);
	}
}
