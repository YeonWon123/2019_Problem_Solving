#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n, a[3001], x, y, dp[3001];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	sort(a + 1, a + 1 + n);
	scanf("%d%d", &x, &y);

	for (int i = 1; i <= n; i++) {
		dp[i] = a[i] * x + dp[i - 1];
		cout << "i : " << i << "\n";
		cout << dp[i] << "\n";
		for (int j = i, t = y; j; j--) {
			t += (a[i + j + 1 >> 1] - a[j])*x;
			cout << dp[j-1] + t << "\n";
			dp[i] = min(dp[i], dp[j - 1] + t);
		}
		cout << "dp_answer: " << dp[i] << "\n";
	}
	printf("%d", dp[n]);
	return 0;
}