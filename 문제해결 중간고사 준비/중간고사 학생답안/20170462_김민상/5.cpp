#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
typedef long long ll;

bool Map[105][105];
ll DP[105][105];
const int dy[] = { 1,0 };
const int dx[] = { 0,1 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> m >> n;
	m++;
	n++;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		Map[b][a] = Map[d][c] = 1;
	}

	DP[0][0] = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				int qy = dy[k] + i;
				int qx = dx[k] + j;

				if (0 > qy || qy >= n || 0 > qx || qx >= m)
					continue;
				if (Map[qy][qx] && Map[i][j])
					continue;
				DP[qy][qx] += DP[i][j];
			}
		}
	}

	cout << DP[n-1][m-1];
	return 0;
}