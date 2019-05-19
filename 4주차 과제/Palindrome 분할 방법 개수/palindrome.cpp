#include <iostream>
#include <string.h>
using namespace std;

int chk[2500][2500];
char input[2501];	// '\0' ���� ����!
int dp[2500] = { 0, };

int main(void)
{
	cin >> input;
	int length = strlen(input);
//	for (int i = 0; i < length; i++)
//		cout << input[i];
//	cout << "\n";

	// ���̰� 1�� ���ڿ��� ������ �Ӹ����
	// �밢�� ��������, �ϴ� 1�� �ʱ�ȭ
	for (int i = 0; i < length; i++) {
			chk[i][i] = 1;
	//		printf("chk[%d][%d] = %d\n", i, i, chk[i][i]);
	}


	// ���̰� 2�� ���ڿ��� �Ӹ�������� ���캸��
	// chk[i][j]���� -> input[i] = input[j]�̸� 1, �ƴϸ� 0���� ����.
	for (int i = 0; i < length-1; i++) {
		if (input[i] == input[i + 1])
			chk[i][i + 1] = 1;
		else
			chk[i][i + 1] = 0;
	//	printf("chk[%d][%d] = %d\n", i, i+1, chk[i][i + 1]);
	}

	// ����, �� ������ ���ڰ� ������, �� ���� ���ڿ��� �Ӹ�������� �˾ƺ��� �ȴ�!
	for (int j = 2; j < length; j++) {
		for (int i = 0; i < length - j; i++)  {
		//	printf("input[%d]: %c, input[%d]: %c\n", i, input[i], i + j, input[i + j]);
			if (input[i] == input[i + j]) {
		//		printf("����!\n");
				chk[i][i + j] = chk[i + 1][i + j - 1];
		//		printf("chk[%d][%d] = %d\n", i + 1, i + j - 1, chk[i+1][i + j - 1]);
			}
			else {
				chk[i][i + j] = 0;
			}
			//	printf("chk[%d][%d] = %d\n", i, i + j, chk[i][i + j]);
		}
	}

	// ���� �Ӹ���� ������ ������ �ּڰ��� �˾ƺ���.
	// �߰��Ǵ� ���ڴ� 1����, �װŴ� �Ӹ�����̴�.
	// ��ü�� �Ӹ�����ϰ�� 1 �߰��Ѵ�.
	dp[0] = 1;
	for (int i = 1; i < length; i++) {
		dp[i] += dp[i - 1];
		for (int j = 0; j < i; j++) {
			if (j == 0) dp[i] += chk[j][i];
			else
				// chk[0][i - j - 2]�� chk[j][i]�� ��� 1�� ��� �Ӹ���� ������ ����!
				dp[i] += (chk[0][i - j - 2] * chk[j][i]);
		}
	}

//	for (int i = 0; i < length; i++)
//		cout << dp[i] << " ";

	cout << dp[length - 1];
	return 0;
}