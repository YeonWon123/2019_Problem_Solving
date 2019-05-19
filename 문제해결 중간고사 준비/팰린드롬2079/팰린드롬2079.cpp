// 팰린드롬 분할과 비슷한 문제
#include <iostream>
#include <string.h>
using namespace std;

char input[2001];
int dp[2001][2001];			// dp[x][y] : x부터 y까지 팰린드롬인지 확인
int dp_one[2001] = { 0, };	// 최소 갯수로 나눠지는 팰린드롬
int chk_1(int i, int j);	// 팰린드롬이면 1, 팰린드롬이 아니면 자릿수 구해서 넣음

int main(void)
{
	int input_size;
	cin >> input;
	input_size = strlen(input);

	// 팰린드롬인지 확인 -> O(n^2)

	// dp 배열 초기화
	// 한 자리 문자는 모두 팰린드롬
	for (int i = 1; i <= input_size; i++)
		dp[i][i] = 1;

	// 두 자리 문자의 경우 input[i] == input[j]이면 팰린드롬
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

	// 팰린드롬의 최소 개수 출력 (O(n^2))
	// 문자를 하나씩 추가해가는 것은 정방향으로 진행 (dp_one 배열 이용)
	// 그러나 그 문자가 팰린드롬에 들어가는지 확인하는 것은 역방향으로 진행(이중 for문)
	dp_one[1] = 1;	// 초기화					// index로 0은 안씀
	for (int i = 2; i <= input_size; i++) {		// index 초기화 조심! (1부터 아님!)
		int temp1, temp2;
		temp1 = dp_one[i - 1] + 1; // 새로 추가되는 문자를 그냥 붙이고 확인
		for (int j = 1; j < i; j++) {
			if (dp[i - j][i] == 1) { // [4][4] -> [3][4] -> [2][4] 이런 식으로, 역으로 탐색
									 // 만약 [3][4]가 1이라면,
									 // ((1 2) (3 4)) 이렇게 나눌 수 있으며,
									 // 이 때 팰린드롬의 개수는 dp[1][2] + 1이다.
				temp2 = dp_one[i - j - 1] + 1;
				if (temp1 > temp2) temp1 = temp2;
			}
		}
		if (temp1 > chk_1(1, i)) temp1 = chk_1(1, i);	// 전체에 대해서 비교해본다.
														// 만약 전체가 팰린드롬이면 1일 것이고
														// 팰린드롬이 아니면 j - 1 + 1일 것이다.(자릿수)
		dp_one[i] = temp1;
	}

	cout << dp_one[input_size];
	return 0;
}

// 팰린드롬이면 1, 팰린드롬이 아니면 자릿수 구해서 넣음
int chk_1(int i, int j)
{
	if (dp[i][j] == 1) return 1;
	else return j - 1 + 1;
}