// �Ӹ���� ���Ұ� ����� ����
#include <iostream>
#include <string.h>
using namespace std;

char input[2001];
int dp[2001][2001];			// dp[x][y] : x���� y���� �Ӹ�������� Ȯ��
int dp_one[2001] = { 0, };	// �ּ� ������ �������� �Ӹ����
int chk_1(int i, int j);	// �Ӹ�����̸� 1, �Ӹ������ �ƴϸ� �ڸ��� ���ؼ� ����

int main(void)
{
	int input_size;
	cin >> input;
	input_size = strlen(input);

	// �Ӹ�������� Ȯ�� -> O(n^2)

	// dp �迭 �ʱ�ȭ
	// �� �ڸ� ���ڴ� ��� �Ӹ����
	for (int i = 1; i <= input_size; i++)
		dp[i][i] = 1;

	// �� �ڸ� ������ ��� input[i] == input[j]�̸� �Ӹ����
	for (int i = 1; i <= input_size; i++) {
		if (input[i - 1] == input[i])
			dp[i][i + 1] = 1;
		else
			dp[i][i + 1] = 0;
	}
	
	// dp[i][j] = dp[i+1][j-1]	(input[i] == input[j])
	// dp[i][j] = 0				(input[i] != input[j])
	for (int j = 2; j <= input_size; j++) {
		for (int i = 1; (i + j) <= input_size; i++) {
			if (input[i - 1] == input[i + j - 1]) {
				dp[i][i + j] = dp[i + 1][i + j - 1];
			}
			else
				dp[i][i + j] = 0;
		}
	}

	// �Ӹ������ �ּ� ���� ��� (O(n^2))
	// ���ڸ� �ϳ��� �߰��ذ��� ���� ���������� ���� (dp_one �迭 �̿�)
	// �׷��� �� ���ڰ� �Ӹ���ҿ� ������ Ȯ���ϴ� ���� ���������� ����(���� for��)
	dp_one[1] = 1;	// �ʱ�ȭ					// index�� 0�� �Ⱦ�
	for (int i = 2; i <= input_size; i++) {		// index �ʱ�ȭ ����! (1���� �ƴ�!)
		int temp1, temp2;
		temp1 = dp_one[i - 1] + 1; // ���� �߰��Ǵ� ���ڸ� �׳� ���̰� Ȯ��
		for (int j = 1; j < i; j++) {
			if (dp[i - j][i] == 1) { // [4][4] -> [3][4] -> [2][4] �̷� ������, ������ Ž��
									 // ���� [3][4]�� 1�̶��,
									 // ((1 2) (3 4)) �̷��� ���� �� ������,
									 // �� �� �Ӹ������ ������ dp[1][2] + 1�̴�.
				temp2 = dp_one[i - j - 1] + 1;
				if (temp1 > temp2) temp1 = temp2;
			}
		}
		if (temp1 > chk_1(1, i)) temp1 = chk_1(1, i);	// ��ü�� ���ؼ� ���غ���.
														// ���� ��ü�� �Ӹ�����̸� 1�� ���̰�
														// �Ӹ������ �ƴϸ� j - 1 + 1�� ���̴�.(�ڸ���)
		dp_one[i] = temp1;
	}

	cout << dp_one[input_size];
	return 0;
}

// �Ӹ�����̸� 1, �Ӹ������ �ƴϸ� �ڸ��� ���ؼ� ����
int chk_1(int i, int j)
{
	if (dp[i][j] == 1) return 1;
	else return j - 1 + 1;
}