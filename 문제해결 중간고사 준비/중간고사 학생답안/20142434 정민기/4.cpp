#pragma warning(disable:4996)
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

int change(int start, int end);
int dp[201][201];
array<int, 201> ball;
int main(void)
{
	int N;
	int K;
	scanf("%d %d", &N, &K);

	int count = 1;
	int check;

	scanf("%d", &ball.at(1));
	for (int i = 2; i <= N; i++)
	{
		scanf("%d", &check);
		if (check != ball.at(count))
		{
			count++;
			ball.at(count) = check;
		}
	}

	printf("%d", change(1, count));

	while (true)
		;
	return 0;
}

int change(int start, int end)
{
	int ans;
	if (start == end)
		return 0;
	else if (ball.at(start) == ball.at(end))
		ans = change(start + 1, end - 1) + 1;
	else if (dp[start][end] != 0)
		return dp[start][end];
	else
	{
		ans = min(change(start, end - 1), change(start + 1, end)) + 1;
		if (end - start >= 2)
			ans = min(change(start + 1, end - 1) + 2, ans);
		dp[start][end] = ans;
	}

	return ans;
}
