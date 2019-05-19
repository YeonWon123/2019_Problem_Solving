#include <iostream>
#include <algorithm>

using namespace std;

int T;
int k;
int dp[102][10002];
int p[102];
int n[102];

int main()
{
	cin >> T;
	cin >> k;

	for (int i = 1; i <= k; i++) {
		cin >> p[i] >> n[i];
	}

	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n[i]; j++) {
			dp[i][p[i] * j] = 1;
		}

	}

	for (int i = 2; i <= k; i++) {
		for (int j = 1; j <= T; j++) {
			if (p[i] > j) {
				dp[i][j] = dp[i - 1][j];
				continue;
			}
			dp[i][j] += dp[i - 1][j];
			for (int k = 1; k <= n[i]; k++) {
				if (j - k * p[i] > 0) {
					dp[i][j] += dp[i - 1][j - k * p[i]];
				}

			}


		}

	}



	cout << dp[k][T] << endl;


	return 0;
}
