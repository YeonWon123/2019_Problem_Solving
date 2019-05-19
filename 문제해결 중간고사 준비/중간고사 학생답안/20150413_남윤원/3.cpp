#include <iostream>
using namespace std;

#define DEBUG

int dp[10001] = { 0, };		// ������ �ݾ�

int dp_counts[100001] = { 0, }; // ��ġ�� ���������� ���ϱ�

int coins[101] = { 0, };		// ������ ��ġ
int counts[101] = { 0, };		// ������ ����

int main()
{
	// �Է¹ޱ�
	int T;			// ������ �ݾ�
	cin >> T;
	int k;			// ������ ������
	cin >> k;

	for (int i = 1; i <= k; i++) {
		cin >> coins[i];
		cin >> counts[i];
	}

	// dp�� ������, �� ������ �ݾ��� ����� ����� ã��
	// ������ �ݾ׸���...
	// ��������... �� �غ���!
	int p = 0;
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j <= counts[i]; j++) {

			for (int m = 0; m <= p; m++) {
				dp_counts[m] += coins[i] * j;
			}
			p++;

			dp[coins[i] * j]++;
			dp[0] = 1;
		}
	}

#ifdef DEBUG
	for (int m = 0; m <= p; m++) {
		cout << dp_counts[m] << " ";
	}
#endif

	cout << dp[T];
	return 0;
}