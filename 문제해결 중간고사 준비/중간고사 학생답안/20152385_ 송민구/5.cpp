#include <iostream>
#include <queue>

using namespace std;

typedef struct point {
	int y;
	int x;
} point;

queue<point> q;
point p;
int h[102][102];
long long dp[102][102];

const int goY[] = { 0,1,0,-1 };
const int goX[] = { 1,0,-1,0 };

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	int k;
	int a, b, c, d;

	cin >> n >> m;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> a >> b >> c >> d;

		if (a > c) {
			int t = a;
			a = c;
			c = t;
		}
		else if (b > d) {
			int t = b;
			b = d;
			d = t;
		}

		if (a == c) {
			h[c][d] = -1;
		}
		else {
			h[c][d] = 1;
		}
	}

	dp[0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 && j == 0) {
				continue;
			}

			if (h[i][j] != 0) {
				if (h[i][j] == 1 && j > 0) {
					dp[i][j] = dp[i][j - 1];
				}
				else if (h[i][j] == -1 && i > 0) {
					dp[i][j] = dp[i - 1][j];
				}
			}
			else {
				if (i == 0) {
					dp[i][j] = dp[i][j - 1];
				}
				else if (j == 0) {
					dp[i][j] = dp[i - 1][j];
				}
				else {
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}

			cout << dp[i][j] << " ";
		}
		cout << endl;
	}


	cout << dp[n][m];

	return 0;
}