#include <iostream>
#include <algorithm>
using namespace std;
int sum, n;
int a[111];
int b[111];
int coin;
int dp[111][10011];


int main() {
	cin >> sum >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cin >> b[a[i]];;
	}
	
	sort(a + 1, a + 1 + n);
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = 1;
		for (int j = 1; j <= sum; j++) {
			dp[i][j] = dp[i - 1][j];
			for (int k = 1; k <= b[a[i]]; k++) {
				if (j - a[i] * k >= 0)  dp[i][j] += dp[i-1][j - a[i] * k];
			}
		}
	}

	cout << dp[n][sum];
	return 0;
}

