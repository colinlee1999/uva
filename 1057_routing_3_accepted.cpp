<<<<<<< HEAD
#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
int g[105][105];
int dp[105][105], inq[105][105];
int main() {
    //freopen("in.txt","r+t",stdin);
    //freopen("out2.txt","w+t",stdout);
    int n, m;
    int i, j, k;
    int x, y, cost;
    int cases = 0;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        memset(inq, 0, sizeof(inq));
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                g[i][j] = 0xfffffff;
            }
        }
        for(i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            g[x][y] = 1;
        }
        for(k = 1; k <= n; k++)
            for(i = 1; i <= n; i++)
                for(j = 1; j <= n; j++)
                    g[i][j] = min(g[i][j], g[i][k]+g[k][j]);

        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                dp[i][j] = 0xfffffff;
        queue<int> X, Y;
        X.push(1), Y.push(1);
        dp[1][1] = 1;
        while(!X.empty()) {
            x = X.front(), X.pop();
            y = Y.front(), Y.pop();
            inq[x][y] = 0;
            //printf("%2d %2d %d\n", x, y, dp[x][y]);
            for(i = 1; i <= n; i++) {
                cost = (x != i && y != i);
                if(g[x][i] == 1) {
                    if(dp[i][y] > dp[x][y]+cost) {
                        dp[i][y] = dp[x][y]+cost;
                        if(inq[i][y] == 0) {
                            inq[i][y] = 1;
                            X.push(i), Y.push(y);
                        }
                    }
                }
                if(g[i][y] == 1) {
                    if(dp[x][i] > dp[x][y]+cost) {
                        dp[x][i] = dp[x][y]+cost;
                        if(inq[x][i] == 0) {
                            inq[x][i] = 1;
                            X.push(x), Y.push(i);
                        }
                    }
                }
            }
            if(x != y) {
                if(dp[y][x] > dp[x][y] + g[x][y]-1) {
                    dp[y][x] = dp[x][y] + g[x][y]-1;
                    if(inq[y][x] == 0) {
                        inq[y][x] = 1;
                        X.push(y), Y.push(x);
                    }
                }
            }
        }
        printf("Network %d\n", ++cases);
        if(dp[2][2] == 0xfffffff)
            puts("Impossible");
        else
            printf("Minimum number of nodes = %d\n", dp[2][2]);
        puts("");
    }
    return 0;
}
=======
#include <iostream>
#include <vector>
#include <fstream>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
using namespace std;

ifstream fin("input.txt");
// #define cin fin

int main()
{
	int n, m, tttt = 0;
	cin >> n >> m;
	while (!(n == 0 && m == 0))
	{
		tttt++;
		cout << "Network " << tttt << endl;
		vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));
		int start, end;
		for (int i = 0; i < m; i++)
		{
			cin >> start >> end;
			g[start][end] = 1;
		}
		// for (int i = 1; i <= n; i++, cout<<endl)
		// 	for (int j = 1; j <= n; j++)
		// 		cout << g[i][j] << ' ';
		vector<vector<int>> f(n + 1, vector<int>(n + 1, UNREACHABLE));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i == j)
					f[i][j] = 0;
				else if (g[i][j] != 0)
					f[i][j] = g[i][j];
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
		start = 1;
		end = 2;
		if (f[start][end] == UNREACHABLE || f[end][start] == UNREACHABLE)
			cout << "Impossible" << endl;
		else
		{
			vector<vector<int>> v(n + 1, vector<int>(n + 1, UNREACHABLE));
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (i == j)
						v[i][j] = 1;
					else
						v[i][j] = f[i][j] + f[j][i];
			for (int k = 1; k <= n; k++)
				for (int i = 1; i <= n; i++)
					for (int j = 1; j <= n; j++)
							v[i][j] = min(v[i][j], v[i][k] + v[k][j] - 1);
			for (int l = 1; l <= n; l++)
				for (int k = 1; k <= n; k++)
					for (int i = 1; i <= n; i++)
						for (int j = 1; j <= n; j++)
							v[i][j] = min(v[i][j], v[i][k] + f[k][l] + v[l][j] - 1);
			cout << "Minimum number of nodes = ";
			cout << v[start][end] << endl;
		}
		cin >> n >> m;
		if (!(n == 0 && m == 0)) cout << endl;
	}
}
>>>>>>> d130f59fbd432ece9a4b404d0d3ef4b2c1910baf
