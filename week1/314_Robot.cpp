#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("week1/314_input.txt");
#define cin fin

struct ele
{
	ele(int row, int col, int ori, int step)
	{
		this->row = row;
		this->col = col;
		this->ori = ori;
		this->step = step;
	}

	int row;
	int col;
	int ori;

	int step;
};

int main()
{
	int n, m;
	cin >> n >> m;

	unordered_map<string, int> orient;
	orient["east"] = 1;
	orient["south"] = 2;
	orient["west"] = 4;
	orient["north"] = 8;
	
	unordered_map<int, int> turn_left;
	turn_left[1] = 8;
	turn_left[2] = 1;
	turn_left[4] = 2;
	turn_left[8] = 4;
	
	unordered_map<int, int> turn_right;
	turn_right[1] = 2;
	turn_right[2] = 4;
	turn_right[4] = 8;
	turn_right[8] = 1;

	unordered_map<int, vector<pair<int, int>>> forward_dir;
	forward_dir[1] = vector<pair<int, int>>();
	forward_dir[1].push_back(pair<int, int>(0, 1));
	forward_dir[1].push_back(pair<int, int>(0, 2));
	forward_dir[1].push_back(pair<int, int>(0, 3));
	
	forward_dir[2] = vector<pair<int, int>>();
	forward_dir[2].push_back(pair<int, int>(1, 0));
	forward_dir[2].push_back(pair<int, int>(2, 0));
	forward_dir[2].push_back(pair<int, int>(3, 0));
	
	forward_dir[4] = vector<pair<int, int>>();
	forward_dir[4].push_back(pair<int, int>(0, -1));
	forward_dir[4].push_back(pair<int, int>(0, -2));
	forward_dir[4].push_back(pair<int, int>(0, -3));
	
	forward_dir[8] = vector<pair<int, int>>();
	forward_dir[8].push_back(pair<int, int>(-1, 0));
	forward_dir[8].push_back(pair<int, int>(-2, 0));
	forward_dir[8].push_back(pair<int, int>(-3, 0));

	// cout<<"ok-1"<<endl;

	while (n != 0 && m != 0)
	{
		vector<vector<int>> atlas(n, vector<int>(m, 0));
		// cout<<"ok-0.5"<<endl;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> atlas[i][j];

		// cout<<"ok0"<<endl;
		
		vector<vector<bool>> reachable(n, vector<bool>(m, true));
		reachable[0][0] = !(atlas[0][0] == 1);
		for (int i = 1; i<n; i++)
			reachable[i][0] = !(atlas[i][0] || atlas[i-1][0]);
		for (int j = 1; j<m; j++)
			reachable[0][j] = !(atlas[0][j] || atlas[0][j-1]);

		for (int i = 1; i<n; i++)
			for (int j = 1; j<m; j++)
				reachable[i][j] = !(atlas[i][j] || atlas[i-1][j] || atlas[i][j-1] || atlas[i-1][j-1]);

		// cout<<"ok1"<<endl;

		vector<vector<int>> status(n, vector<int>(m, 0));

		int s_row, s_col;
		int e_row, e_col;
		string s_orient;
		cin >> s_row >> s_col >> e_row >> e_col >> s_orient;

		// cout<<"ok2"<<endl;

		queue<ele> q;

		q.push(ele(s_row, s_col, orient[s_orient], 0));

		//begin bfs

		// cout<<"ok3"<<endl;

		bool found = false;
		int steps = -1;

		while (!q.empty() && !found)
		{
			ele cur = q.front();
			q.pop();

			int row = cur.row;
			int col = cur.col;
			int ori = cur.ori;
			int step = cur.step;

			// cout<<"ok4"<<endl;

			//turn left
			if (!(status[row][col] & turn_left[ori]))
			{
				q.push(ele(row, col, turn_left[ori], step+1));
				status[row][col] |= turn_left[ori];
			}

			// turn right
			if (!(status[row][col] & turn_right[ori]))
			{
				q.push(ele(row, col, turn_right[ori], step+1));
				status[row][col] |= turn_right[ori];
			}

			// cout<<"ok5"<<endl;

			// go forward
			for (auto it : forward_dir[ori])
			{
				int next_row = row + it.first;
				int next_col = col + it.second;
				if (next_row < 0) break;
				if (next_row >= n) break;
				if (next_col < 0) break;
				if (next_col >= m) break;
				if (!reachable[next_row][next_col]) break;
				if (!(status[next_row][next_col] & ori))
				{
					if (next_row == e_row && next_col == col)
					{
						steps = step + 1;
						found = true;
						break;
					}
					q.push(ele(next_row, next_col, ori, step+1));
					status[next_row][next_col] |= ori;
				}
			}

			// cout<<"ok6"<<endl;
		}

		//end bfs

		cout << steps << endl;
		
		cin >> n >> m;
	}
}
