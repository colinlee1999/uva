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
#include <complex>
using namespace std;

#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define eps (1e-9)
#define MODULO 1000000007

ifstream fin("12879_input.txt");
#define cin fin

#define MAXM 200001

typedef complex<double> T;
typedef vector<T> VT;
const double PI = 4*atan(1);

void FFT(VT &a, bool invert) {
    size_t n = a.size();

    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        T wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            T w(1);
            for (int j=0; j<len/2; ++j) {
                T u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert)
        for (int i=0; i<n; ++i)
            a[i] /= n;
}
// END

int main()
{
	int n, m;
	vector<int> tk(MAXM, 0);
	vector<int> td(MAXM, 0);
	int case_count = 0;
	while (cin >> n) {
		case_count++;
		int max_num = -1;
		for (int i = 0; i < n; i++) {
			cin >> tk[i];
			max_num = max(max_num, tk[i]);
		}
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> td[i];
			max_num = max(max_num, td[i]);
		}

		int len = 1;
		while (len < max_num) len <<= 1;
		len <<= 1;

		VT k(len, T(0, 0));
		VT h(len, T(0, 0));
		vector<bool> d(len, false);

		k[0] = 1;
		for (int i = 0; i < n; i++) {
			k[tk[i]] = 1;
		}

		for (int i = 0; i < m; i++) {
			d[td[i]] = true;
		}

		FFT(k, false);
		for (int i = 0; i < k.size(); i++)
			h[i] = k[i] * k[i];
		FFT(h, true);

		int result = 0;
		for (int i = 0; i < d.size(); i++)
			if (d[i] && h[i].real() > 0.5)
				result++;
		cout << result << endl;

		// if (case_count == 61) {
		// 	cout << n << endl;
		// 	for (int i = 0; i < n; i++)
		// 		cout << tk[i] << ' ';
		// 	cout << endl;
		// 	cout << m << endl;
		// 	for (int i = 0; i < m; i++)
		// 		cout << td[i] << ' ';
		// 	cout << endl;
		// 	for (int i = 0; i < len; i++)
		// 		if (h[i].real() < 0.5)
		// 			cout << 0 << endl;
		// 		else cout << h[i].real() << endl;
		// }
		
	}
}
