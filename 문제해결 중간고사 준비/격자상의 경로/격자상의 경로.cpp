// memoization으로 푸는 문제
#include <iostream>
using namespace std;

// dp[x][y] -> [1][1]에서 시작해서 [x][y]까지 갈 수 있는 서로 다른 경로의 수
int dp[16][16] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M, K;
	cin >> N >> M >> K;

	// 필수로 지나가야 하는 좌표
	int p_x = 0;
	int p_y = 0;

	// 만약 K가 0이 아닐 경우
	if (K != 0) {
		// 그 좌표를 먼저 구한다.
		p_y = K / M;
		p_x = K % M;			// 0이 나오면 안되는데....
		if (p_x == 0) p_x = M;
		else p_y++;
	}

//	cout << p_y << " " << p_x << endl;

	// 일단 K가 없다고 생각하고 구해 보자.
	// dp 배열 초기화 -> x, y 중 1인 곳은 전부 1로 처리
	// 단, p_x, p_y가 0인 경우 거기까지만 1로 처리
	int lim_x = M;
	int lim_y = N;

	if (K != 0) {
		lim_x = p_x;
		lim_y = p_y;
	}
	for (int i = 1; i <= lim_x; i++) {
		dp[i][1] = 1;
	}

	for (int i = 1; i <= lim_y; i++) {
		dp[1][i] = 1;
	}

	// dp 배열을 채워 간다. dp[lim_x][lim_y]까지 채운다.
	for (int i = 2; i <= lim_x; i++) {
		for (int j = 2; j <= lim_y; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}

	// 만약 K가 0이 아니면, dp[lim_x][lim_y]부터 dp[M][N]까지 채운다.
	// dp 배열 다시 초기화
	if (K != 0) {
		for (int i = lim_x + 1; i <= M; i++) {
			dp[i][lim_y] = dp[lim_x][lim_y];
		}

		for (int i = lim_y + 1; i <= N; i++) {
			dp[lim_x][i] = dp[lim_x][lim_y];
		}

		// dp 배열을 채워 간다. dp[M][N]까지 채운다.
		for (int i = lim_x + 1; i <= M; i++) {
			for (int j = lim_y + 1; j <= N; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
	}

	cout << dp[M][N];
	return 0;
}