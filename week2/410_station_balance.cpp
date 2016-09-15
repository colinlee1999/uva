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

void dfs(int depth, int last,
	const vector<int> & specimen,
	vector<vector<int>> & chamber_filled,
	double & min_imbalance,
	vector<vector<int>> & min_imbalance_chamber_state)
{
	if (depth == specimen.size())
	{
		vector<int> chamber_final_state;
		double average = 0;
		for (int i = 0; i < chamber_filled.size(); i++)
		{
			int temp = 0;
			for (int j = 0; j < chamber_filled[i].size(); j++)
				temp += specimen[chamber_filled[i][j]];
			chamber_final_state.push_back(temp);
			average += temp;
		}
		average /= (int)chamber_filled.size();
		double temp_imbalance = 0;
		for (int i = 0; i < chamber_final_state.size(); i++)
			temp_imbalance += dabs(chamber_final_state[i] - average);
		if (temp_imbalance < min_imbalance)
		{
			min_imbalance = temp_imbalance;
			min_imbalance_chamber_state = chamber_filled;
		}
	}
	else
	{
		for (int i = 0; i < chamber_filled.size(); i++)
		{
			if (chamber_filled[i].size() < 2)
			{
				chamber_filled[i].push_back(depth);
				dfs(depth + 1, i, specimen, chamber_filled, min_imbalance, min_imbalance_chamber_state);
				chamber_filled[i].pop_back();
			}
		}
	}
}

int main()
{
	int C, S;
	int case_count = 0;
	while (cin >> C >> S)
	{
		case_count++;
		vector<int> specimen(S, 0);
		for (int i = 0; i < S; i++)
			cin >> specimen[i];
		vector<vector<int>> chamber_filled(C, vector<int>()), result_state;
		double result = INF;
		dfs(0, 0, specimen, chamber_filled, result, result_state);
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
