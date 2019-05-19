#include <iostream>
using namespace std;

int arr[2001];
int dp[2001][2001]; // dp[i][j] : arr[i]���� arr[j]������ �Ӹ�������� Ȯ��
int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;		// ������ ũ��
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	// arr[s] ���� arr[e]���� �Ӹ�������� Ȯ���غ��� (dp �̿�)
	// �켱, s�� e�� ������ �Ӹ�����̴�. ���� dp�迭�� �ʱ�ȭ����
	for (int j = 1; j <= N; j++)
		dp[j][j] = 1;

	// ���� e = s+1�̸� (�� ������ ���� 2���̸�) arr[s] = arr[e]���� �Ӹ�����̴�.
	for (int j = 1; j <= N - 1; j++) {
		if (arr[j] == arr[j + 1]) dp[j][j + 1] = 1;
		else dp[j][j + 1] = 0;
	}

	// dp ��ȭ�� : dp[s][e] = dp[s+1][e-1] (arr[s] == arr[e])
	// dp ��ȭ�� : dp[s][e] = 0			   (arr[s] != arr[e])
	for (int j = 2; j < N; j++) {
		for (int i = 1; (i + j) <= N; i++) {
			if (arr[i] == arr[i + j]) {
				dp[i][i + j] = dp[i + 1][i + j - 1];
			}
			else dp[i][i + j] = 0;
		}
	}

	int M;		// ������ ����
	cin >> M;

	for (int i = 1; i <= M; i++) {
		int S, E;
		cin >> S >> E;
		// arr[s] ���� arr[e]���� �Ӹ�������� Ȯ���غ��� (dp �̿�)
		// dp ��ȭ�� : dp[s][e] = dp[s+1][e-1] (arr[s] == arr[e])
		// dp ��ȭ�� : dp[s][e] = 0			   (arr[s] != arr[e])
		cout << dp[S][E] << "\n";
	}
	return 0;
}