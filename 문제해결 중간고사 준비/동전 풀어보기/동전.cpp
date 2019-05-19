#include <iostream>
using namespace std;

int coins[101];
int dp[10001] = { 0, };

int main(void)
{
	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		cin >> coins[i];
	}

	// dp 배열을 채워 보자
	dp[0] = 1; // 우선, dp[0] = 1으로 초기화
	
	// 하나의 동전에 대해서 (n개의 동전이 있음)
	for (int i = 1; i <= n; i++) {
		// 각 가치를 만들 수 있는지를 따져 보자. (k까지)
		for (int j = 1; j <= k; j++) {
			// 만약 i번째 동전으로 j의 가치를 만들 수 있다면
			if (j - coins[i] >= 0) {
				// dp[j]에 dp[j - coins[i]]를 더한다.
				dp[j] += dp[j - coins[i]];
			}
		}
	}

	cout << dp[k];
	return 0;
}