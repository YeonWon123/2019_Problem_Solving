#include <iostream>
#include <string.h>
using namespace std;

int chk[2500][2500];
char input[2501];	// '\0' 문자 조심!
int dp[2500] = { 0, };

int main(void)
{
	cin >> input;
	int length = strlen(input);
//	for (int i = 0; i < length; i++)
//		cout << input[i];
//	cout << "\n";

	// 길이가 1인 문자열은 무조건 팰린드롬
	// 대각선 방향으로, 일단 1로 초기화
	for (int i = 0; i < length; i++) {
			chk[i][i] = 1;
	//		printf("chk[%d][%d] = %d\n", i, i, chk[i][i]);
	}


	// 길이가 2인 문자열이 팰린드롬인지 살펴보자
	// chk[i][j]에서 -> input[i] = input[j]이면 1, 아니면 0으로 두자.
	for (int i = 0; i < length-1; i++) {
		if (input[i] == input[i + 1])
			chk[i][i + 1] = 1;
		else
			chk[i][i + 1] = 0;
	//	printf("chk[%d][%d] = %d\n", i, i+1, chk[i][i + 1]);
	}

	// 이제, 양 끝단의 문자가 같으면, 그 안의 문자열이 팰린드롬인지 알아보면 된다!
	for (int j = 2; j < length; j++) {
		for (int i = 0; i < length - j; i++)  {
		//	printf("input[%d]: %c, input[%d]: %c\n", i, input[i], i + j, input[i + j]);
			if (input[i] == input[i + j]) {
		//		printf("같음!\n");
				chk[i][i + j] = chk[i + 1][i + j - 1];
		//		printf("chk[%d][%d] = %d\n", i + 1, i + j - 1, chk[i+1][i + j - 1]);
			}
			else {
				chk[i][i + j] = 0;
			}
			//	printf("chk[%d][%d] = %d\n", i, i + j, chk[i][i + j]);
		}
	}

	// 이제 팰린드롬 분할의 개수의 최솟값을 알아보자.
	// 추가되는 문자는 1개고, 그거는 팰린드롬이다.
	// 전체가 팰린드롬일경우 1 추가한다.
	dp[0] = 1;
	for (int i = 1; i < length; i++) {
		dp[i] += dp[i - 1];
		for (int j = 0; j < i; j++) {
			if (j == 0) dp[i] += chk[j][i];
			else
				// chk[0][i - j - 2]과 chk[j][i]이 모두 1인 경우 팰린드롬 분할이 가능!
				dp[i] += (chk[0][i - j - 2] * chk[j][i]);
		}
	}

//	for (int i = 0; i < length; i++)
//		cout << dp[i] << " ";

	cout << dp[length - 1];
	return 0;
}