#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
using namespace std;

ifstream fin("1062_input.txt");
#define cin fin

int main()
{
	string s;
	cin >> s;
	int case_count = 0;
	while (s != "end")
	{
		int slen = s.length();
        vector<int> f(slen, 1);

        for (int i = 0; i < slen; i++)
            for (int j = 0; j < i; j++)
                if (s[j] < s[i])
                    f[i] = max(f[i], f[j] + 1);
        
        int result = 0;

        for (int i = 0; i < slen; i++)
            result = max(result, f[i]);

		case_count++;
		cout << "Case " << case_count << ": " << result << endl;
		cin >> s;
	}
}
