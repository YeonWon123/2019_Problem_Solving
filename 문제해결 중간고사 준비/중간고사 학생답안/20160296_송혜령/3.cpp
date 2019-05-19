#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<stack>

using namespace std;

pair<int, int> price[105];
int dp[10005];
int T, K;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T >> K;
	for (int i = 0; i < K; ++i)
		cin >> price[i].first >> price[i].second;

	sort(price, price + K);

	dp[0] = 1;

	for (int i = 0; i < K; ++i)
	{
		for (int j = T; j >= 1; --j)
		{
			for (int x = 1; x <= price[i].second; ++x)
			{
				int num = price[i].first*x;
				if (num <= j)
					dp[j] = dp[j - 1]+1;
			}
		}
	}

	cout << dp[T];


	return 0;
}