// memoization���� Ǫ�� ����
#include <iostream>
using namespace std;

// dp[x][y] -> [1][1]���� �����ؼ� [x][y]���� �� �� �ִ� ���� �ٸ� ����� ��
int dp[16][16] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M, K;
	cin >> N >> M >> K;

	// �ʼ��� �������� �ϴ� ��ǥ
	int p_x = 0;
	int p_y = 0;

	// ���� K�� 0�� �ƴ� ���
	if (K != 0) {
		// �� ��ǥ�� ���� ���Ѵ�.
		p_y = K / M;
		p_x = K % M;			// 0�� ������ �ȵǴµ�....
		if (p_x == 0) p_x = M;
		else p_y++;
	}

//	cout << p_y << " " << p_x << endl;

	// �ϴ� K�� ���ٰ� �����ϰ� ���� ����.
	// dp �迭 �ʱ�ȭ -> x, y �� 1�� ���� ���� 1�� ó��
	// ��, p_x, p_y�� 0�� ��� �ű������ 1�� ó��
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

	// dp �迭�� ä�� ����. dp[lim_x][lim_y]���� ä���.
	for (int i = 2; i <= lim_x; i++) {
		for (int j = 2; j <= lim_y; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}

	// ���� K�� 0�� �ƴϸ�, dp[lim_x][lim_y]���� dp[M][N]���� ä���.
	// dp �迭 �ٽ� �ʱ�ȭ
	if (K != 0) {
		for (int i = lim_x + 1; i <= M; i++) {
			dp[i][lim_y] = dp[lim_x][lim_y];
		}

		for (int i = lim_y + 1; i <= N; i++) {
			dp[lim_x][i] = dp[lim_x][lim_y];
		}

		// dp �迭�� ä�� ����. dp[M][N]���� ä���.
		for (int i = lim_x + 1; i <= M; i++) {
			for (int j = lim_y + 1; j <= N; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
	}

	cout << dp[M][N];
	return 0;
}