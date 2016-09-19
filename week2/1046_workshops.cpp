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

ifstream fin("1046_input.txt");

struct ele
{
	ele(int p, int d)
	{
		this->p = p;
		this->d = d;
	}

	int p, d;
};

struct
{
	bool operator()(const ele & a, const ele & b)
	{
		return a.d < b.d;
	}
} my_comp_0;

int main()
{
	int w;
	int cases_count = 0;
	scanf("%d", &w);
	while (w)
	{
		vector<ele> people(w, ele(0, 0));
		for (int i = 0; i < w; i++)
			scanf("%d %d", &(people[i].p), &(people[i].d));
		int r;
		scanf("%d", &r);
		vector<ele> room(r, ele(0, 0));
		for (int i = 0; i < r; i++)
		{
			int h, m;
			scanf("%d %d:%d", &(room[i].p), &h, &m);
			room[i].d = (h - 14) * 60 + m;
		}

		sort(people.begin(), people.end(), my_comp_0);
		sort(room.begin(), room.end(), my_comp_0);

		vector<bool> selected(w, false);

		int num_tents = 0;
		int num_people = 0;

		for (int j = 0; j < r; j++)
		{
			int max_p = -1;
			int max_p_pos = 0;
			for (int i = 0; i < w; i++)
			{
				if (selected[i]) continue;
				if (people[i].d > room[j].d) break;
				if (people[i].p <= room[j].p && people[i].p>max_p)
				{
					max_p = people[i].p;
					max_p_pos = i;
				}
			}
			if (max_p != -1)
				selected[max_p_pos] = true;
		}
			

		for (int i = 0; i < w; i++)
			if (!selected[i])
			{
				num_tents++;
				num_people += people[i].p;
			}

		cases_count++;
		cout << "Trial " << cases_count << ':' << ' ' << num_tents << ' ' << num_people << endl;
		cout << endl;
		scanf("%d", &w);
	}
}
