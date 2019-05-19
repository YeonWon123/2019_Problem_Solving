#include <iostream>
#include <algorithm>

using namespace std;

int N, M, K;
int a[101], b[101], c[101], d[101];
int dp[101][101];

int main()
{
	cin >> N >> M;
	cin >> K;
	for (int i = 1; i <= N; i++) dp[i][0] = 1;
	for (int i = 1; i <= M; i++) dp[0][i] = 1;
	for (int i = 1; i <= K; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		if (a[i] == 0 && c[i] == 0) {
			if (b[i] - d[i] > 0) {
				for (int j = d[i]+1; j <= M; j++) {
					dp[0][j] = 0;
				}
			}
			else {
				for (int j = b[i]+1; j <= M; j++) {
					dp[0][j] = 0;
				}
			}
		}
		else if (b[i] == 0 && d[i] == 0) {
			if (a[i] - c[i] > 0) {
				for (int j = c[i]+1; j <= N; j++) {
					dp[j][0] = 0;
				}
			}
			else {
				for (int j = a[i]+1; j <= N; j++) {
					dp[j][0] = 0;
				}
			}
		}
	}
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int tmp1 = dp[i - 1][j];
			int tmp2 = dp[i][j - 1];
			for (int k = 1; k <= K; k++) {
				if ((i == a[k] && j == b[k]) || (i == c[k] && j == d[k])) {
					if ((i - 1 == a[k] && j == b[k]) || (i - 1 == c[k] && j == d[k])) {
						dp[i - 1][j] = 0;
					}
					else if ((i == a[k] && j - 1 == b[k]) || (i == c[k] && j - 1 == d[k])) {
						dp[i][j - 1] = 0;
					}
				}
			}
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			dp[i - 1][j] = tmp1;
			dp[i][j - 1] = tmp2;
		}
	}
	cout << dp[N][M] << endl;
    return 0;
}

