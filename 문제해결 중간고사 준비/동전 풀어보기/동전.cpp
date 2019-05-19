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

	// dp �迭�� ä�� ����
	dp[0] = 1; // �켱, dp[0] = 1���� �ʱ�ȭ
	
	// �ϳ��� ������ ���ؼ� (n���� ������ ����)
	for (int i = 1; i <= n; i++) {
		// �� ��ġ�� ���� �� �ִ����� ���� ����. (k����)
		for (int j = 1; j <= k; j++) {
			// ���� i��° �������� j�� ��ġ�� ���� �� �ִٸ�
			if (j - coins[i] >= 0) {
				// dp[j]�� dp[j - coins[i]]�� ���Ѵ�.
				dp[j] += dp[j - coins[i]];
			}
		}
	}

	cout << dp[k];
	return 0;
}