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
	ele(int pos, int letter)
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
		// cout<<"+++++++++++++++++++++++++"<<endl;
		int slen = s.length();

		vector<ele> buffer;
		vector<bool> visited(slen, false);
		
		int prev_max = -1;
		int v_count = 0;

		while (v_count < slen)
		{
			vector<ele> no_father;

			prev_max = -1;
			for (int i = 0; i < slen; i++)
				if (!visited[i] && s[i] - 'A'>prev_max)
				{
					no_father.push_back(ele(i, s[i] - 'A'));

					prev_max = s[i] - 'A';
					v_count++;
					visited[i] = true;
				}

			int pold, pnew;
			pold = pnew = 0;
			vector<ele> new_buffer;

			while (pold < buffer.size() && pnew < no_father.size())
			{
				// cout<<"pold\t"<<pold<<"\tpnew\t"<<pnew<<endl;
				if (buffer[pold].pos >= no_father[pnew].pos)
				{
					new_buffer.push_back(no_father[pnew]);
					pnew++;
				}
				else
				{

					if (buffer[pold].letter >= no_father[pnew].letter)
					{
						new_buffer.push_back(no_father[pnew]);
						pnew++;
						pold++;
					}
					else
					{
						new_buffer.push_back(buffer[pold++]);
					}
					
				}
			}

			while (pnew < no_father.size())
				new_buffer.push_back(no_father[pnew++]);

			while (pold < buffer.size())
				new_buffer.push_back(buffer[pold++]);

			buffer.swap(new_buffer);

			// cout<<"=============="<<endl;
			// for (auto it : buffer)
			// {
			// 	cout<<(char)(it.letter+'A')<<' ';
			// }
			// cout<<endl;
		}

		int result = buffer.size();

		case_count++;
		cout << "Case " << case_count << ": " << result << endl;
		cin >> s;
	}
}
