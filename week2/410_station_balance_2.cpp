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

ifstream fin("410_input.txt");
#define cin fin

double dabs(const double & a)
{
	return a < 0 ? -a : a;
}

int main()
{
	int C, S;
	int case_count = 0;
	while (cin >> C >> S)
	{
		case_count++;
		vector<int> specimen(S, 0);
		double average = 0;
		for (int i = 0; i < S; i++)
		{
			cin >> specimen[i];
			average += specimen[i];
		}
		average /= C;
			
		vector<vector<int>> result_state(C, vector<int>());
		double result = 0;

		sort(specimen.begin(), specimen.end());
		int cur_specimen = (int)specimen.size() - 1;
		int cur_chamber = 0;
		while (cur_specimen >= 0)
		{
			while (cur_specimen>=0 && cur_chamber < C)
				result_state[cur_chamber++].push_back(cur_specimen--);
			cur_chamber = C - 1;
			while (cur_specimen >= 0 && cur_chamber >= 0)
				result_state[cur_chamber--].push_back(cur_specimen--);
		}

		for (int i = 0; i < C; i++)
		{
			double temp = 0;
			for (int j = 0; j < result_state[i].size(); j++)
				temp += specimen[result_state[i][j]];
			result += dabs(temp - average);
		}

		cout << "Set #" << case_count << endl;
		for (int i = 0; i < C; i++)
		{
			cout << i << ':';
			for (int j = 0; j < result_state[i].size(); j++)
				cout << ' ' << specimen[result_state[i][j]];
			cout << endl;
		}
		cout << "IMBALANCE = ";
		printf("%.5f\n", result);
		cout << endl;
	}
}
