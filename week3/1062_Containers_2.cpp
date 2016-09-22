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
		this->pos = pos;
		this->letter = letter;
	}

	int pos;
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
		
		int prev_max = -1;
		int v_count = 0;

		buffer.push_back(ele(0, 30));

		while (v_count < slen)
		{
			vector<ele> new_buffer();

			for (auto it : buffer)
			{
				it.pos;
			}



			prev_max = -1;
			for (int i = 0; i < slen; i++)
				if (!visited[i] && s[i] - 'A'>prev_max)
				{
					bool found = false;
					for (int j = 0; j < buffer.size(); j++)
						if (buffer[j] >= s[i])
						{
							buffer[j] = s[i];
							found = true;
							break;
						}
					if (!found)
						buffer.push_back(s[i]);

					prev_max = s[i] - 'A';
					v_count++;
					visited[i] = true;
				}
		}

		int result = buffer.size();

		case_count++;
		cout << "Case " << case_count << ": " << result << endl;
		cin >> s;
	}
}
