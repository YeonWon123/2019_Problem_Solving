#pragma warning(disable:4996)
#include <iostream>
using namespace std;

int main(void)
{
	int T;
	int k;
	int coin[100][2];

	scanf("%d", &T);
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
		scanf("%d %d", &coin[i][0], &coin[i][1]);


	int dp[10001] = { 0, };
	for (int i = 0; i < k; i++)
	{
		for (int p = T; p >= 0; p--)
		{
			if (dp[p] != 0 || p == 0)
				for (int o = coin[i][1]; o >= 1; o--)
				{
					if (p + coin[i][0] * o > T)
						continue;
					if(dp[p] == 0)
						dp[p + coin[i][0] * o] += 1;
					else
						dp[p + coin[i][0] * o] += dp[p];
				}

		}
	}
	
	printf("%d", dp[T]);

	return 0;
}
