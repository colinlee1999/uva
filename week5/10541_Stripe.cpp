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

ifstream fin("10541_input.txt");
#define cin fin

#define NLEN 10
#define CARRY_LEN 8
#define CARRY 100000000

struct Number {
	Number() {
		num.resize(NLEN);
		for (int i = 0; i < NLEN; i++)
			num[i] = 0;
	}

	Number(const Number & a) {
		num = vector<long long>(NLEN, 0);
		for (int i = 0; i < NLEN; i++)
			this->num[i] = a.num[i];
	}

	string toString() {
		int i = NLEN - 1;
		while (i > 0 && num[i] == 0) i--;
		string s = to_string(num[i--]);
		while (i >= 0) {
			string ts = to_string(num[i]);
			int tlen = ts.length();
			for (int j = 0; j < CARRY_LEN - tlen; j++) {
				s = s + '0';
			}
			s = s + ts;
			i--;
		}
		return s;
	}

	Number & operator+(Number a) {
		long long carry = 0;
		for (int i = 0; i < NLEN; i++) {
			num[i] += a.num[i] + carry;
			carry = num[i] / CARRY;
			num[i] %= CARRY;			
		}
		return *this;
	}	

	Number & operator=(Number a) {
		num.swap(a.num);
		return *this;
	}

	Number & operator=(long long a) {
		for (int i = 1; i < NLEN; i++)
			num[i] = 0;
		num[0] = a;
		return *this;
	}

	vector<long long> num;
};

Number f[202][102];

int main()
{
	int tttt;
	cin >> tttt;
	while (tttt--) {
		// cout << "==================" << endl;
		int n, k;
		cin >> n >> k;
		n++;
		vector<long long> a(k, 0);
		for (int i = 0 ; i < k; i++) {
			cin >> a[i];
			// cout << a[i] << ' ';
		}
		// cout << endl;
		
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= k; j++)
				f[i][j] = Number();

		for (int i = 0; i <= n; i++) {
			f[i][0] = 1;
		}

		

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= k; j++) {
				for (int l = 0; l <= i - a[j - 1] - 1; l++) {
					f[i][j] = f[i][j] + f[l][j - 1];
				}
			}
		}

		// for (int i = 0; i <= n; i++, cout << endl)
		// 	for (int j = 0; j <= k; j++)
		// 		cout << f[i][j].toString() << ' ';

		cout << f[n][k].toString() << endl;
	}
}
