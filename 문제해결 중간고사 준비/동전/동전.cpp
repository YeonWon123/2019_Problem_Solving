#include <iostream>
using namespace std;

int arr[21];
int dp[10001] = { 0, };		// 1���� 10000���� �ݾ��� ����� ����� ��
	//ex) k-arr[j]�� ���� �� �ִ� ����� �� : dp[k-arr[j]]

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;	// �׽�Ʈ ���̽��� ����
	cin >> T;

	for (int i = 0; i < T; i++) {
		int N, M;
		cin >> N; // ������ ���� ��
		for (int j = 1; j <= N; j++) {
			cin >> arr[j];	// N���� ������ �� �ݾ��� ������������ ���ĵǾ� �־���
		}
		cin >> M; // �־��� N���� �������� ������ �� �ݾ�

		// �տ������� dp�� �Ѵ�.
		// ù ��° �������� ���� �� �ִ� ����� ���� dp�� ����...
		// ù ��° + �� ��° �������� ���� �� �ִ� ����� ���� dp�� ����...

		dp[0] = 1;
		// ������ ��ġ ���� ���� loop
		for (int j = 1; j <= N; j++) {
			// �ݾ��� 1���� M���� ������ ���� loop
			for (int k = 1; k <= M; k++) {
				// ���� k-arr[j]�� 0���� ũ�ų� ������ 
				// ��, arr[j]�� k-arr[j]�� ���ؼ� k�� ä�� �� ������ (�� ���� �����̸� �ȵ�)
				// k-arr[j]�� ���� �� �ִ� ����� ���� dp[k-arr[j]]�� dp[k]�� �����ش�.
				if (k - arr[j] >= 0) dp[k] += dp[k - arr[j]];
			}
		}

		cout << dp[M] << "\n";

		for (int j = 1; j <= M; j++) {
			dp[j] = 0;
		}
	}

	return 0;
}