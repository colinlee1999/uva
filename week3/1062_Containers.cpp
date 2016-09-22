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

struct ele
{
	ele(int step, int letter)
	{
		this->step = step;
		this->letter = letter;
	}

	int step;
	int letter;
};

int main()
{
	string s;
	cin >> s;
	int case_count = 0;
	while (s != "end")
	{
		int slen = s.length();

		vector<ele> buffer;
		vector<bool> visited(slen, false);
		int step = 0;
		int prev_max = -1;
		int v_count = 0;
		while (v_count < slen)
		{
			prev_max = -1;
			step++;
			for (int i = 0; i < slen; i++)
				if (!visited[i] && s[i] - 'A'>prev_max)
				{
					prev_max = s[i] - 'A';
					v_count++;
					visited[i] = true;
					buffer.push_back(ele(step, prev_max));
				}
		}
		buffer.push_back(ele(-1, -1));

		int result = 0;
		int last = -1;
		int count = 0;
		for (auto it : buffer)
		{
			if (it.step != last)
			{
				result = max(result, count);
				last = it.step;
				count = 1;
			}
			else
				count++;
		}

		case_count++;
		cout << "Case " << case_count << ": " << result << endl;
		cin >> s;
	}
}
