#include <iostream>

int dp[102][102];

int main(void) {

	long long result = 0;
	int N, M, k;
	int a, b, c, d, temp1, temp2;
	scanf("%d%d", &N, &M);
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (a == c) {
			if (b > d) {
				dp[b][a] = -1;
			}
			else {
				dp[d][c] = -1;
			}

		}
		else {
			if (a > c) {
				dp[b][a] = -2;
			}
			else {
				dp[d][c] = -2;
			}

		}
	}

	for (int i = 0; i < N + 1; i++) {
		if (dp[0][i] != -1) {
			dp[0][i] = 1;
		}
		else {
			dp[0][i] = 0;
			break;
		}
	}

	for (int i = 0; i < M + 1; i++) {
		if (dp[i][0] != -1) {
			dp[i][0] = 1;
		}
		else {
			dp[i][0] = 0;
			break;
		}
	}

	for (int i = 1; i < M + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (dp[i][j] == -1) {
				dp[i][j] = dp[i][j - 1];
			}
			else if (dp[i][j] == -2) {
				dp[i][j] = dp[i - 1][j];
			}
			else{
				temp1 = dp[i][j - 1];
				temp2 = dp[i - 1][j];
				if (dp[i][j - 1] == -1) {
					temp1 = 0;
				}
				if (dp[i - 1][j] == -1) {
					temp2 = 0;
				}
				dp[i][j] = temp1 + temp2;
			}
		}
	}
	printf("%d",dp[M][N]);

	return 0;
}