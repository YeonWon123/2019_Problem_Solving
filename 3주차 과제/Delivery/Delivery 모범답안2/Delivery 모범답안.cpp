#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> arr(n + 1), dp(n + 1), sum(n + 1);

	for (int i = 1; i <= n; i++) cin >> arr[i];
	sort(arr.begin() + 1, arr.end());
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + arr[i];

	int t, h; cin >> t >> h;

	for (int i = 1; i <= n; i++) {
		cout << i << "\n";
		dp[i] = dp[i - 1] + arr[i] * t;
		cout << dp[i] << "\n";
		for (int j = i; j >= 1; j--) {
			int mid = (i + j) >> 1;

			int left = (arr[mid] * (mid - j + 1) - (sum[mid] - sum[j - 1])) * t;
			int right = ((sum[i] - sum[mid - 1]) - (arr[mid] * (i - mid + 1))) * t;

			cout << "left : " << left << "\n";
			cout << "right : " << right << "\n";

			int cost = left + right + h;
			dp[i] = min(dp[i], dp[j - 1] + cost);
			cout << dp[i] << "\n";
		}
		cout << "dp_number : " << dp[i] << "\n";
	}

	cout << dp[n];
}

/*
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
*/