#include <iostream>
#include <algorithm>

using namespace std;

int dp[101][101];
int disable[100][4];

int main(void)
{
	int N, M, K; // M(Y), N(X)
	int tmp;

	cin >> N >> M;

	cin >> K;

	for (int i = 0; i < K; i++)
	{
		cin >> disable[i][0];
		cin >> disable[i][1];
		cin >> disable[i][2];
		cin >> disable[i][3];

		if (disable[i][0] > disable[i][2])
		{
			tmp = disable[i][0];
			disable[i][0] = disable[i][2];
			disable[i][2] = tmp;
		}
		
		if (disable[i][1] > disable[i][3])
		{
			tmp = disable[i][1];
			disable[i][1] = disable[i][3];
			disable[i][3] = tmp;
		}
	}



	dp[0][0] = 1;
	for (int y = 0; y <= M; y++)
	{
		for (int x = 0; x <= N; x++)
		{
			if (y == 0 || x == 0)
				dp[y][x] = 1;
			else
				dp[y][x] = dp[y - 1][x] + dp[y][x - 1];

			if (y > 0&& x == 0)
				dp[y][x] = dp[y - 1][x];
			else if (x > 0 && y == 0)
				dp[y][x] = dp[y][x - 1];


			for (int k = 0; k < K; k++)
			{
				if (disable[k][2] == x && disable[k][3] == y)
				{
					if (disable[k][0] == disable[k][2]) // X는 같고 Y가 다른 경우
					{
						dp[y][x] = dp[y][x-1];
						if (x == 0)
							dp[y][x] = 0;
					}
					else if (disable[k][1] == disable[k][3]) // Y가 같고 X가 다른 경우
					{
						dp[y][x] = dp[y-1][x];
						if (y == 0)
							dp[y][x] = 0;
					}
				}
				
			}
		}
	}

	cout << dp[M][N];
	
	return 0;
}