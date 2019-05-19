#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG

char in_c[1501][1501]; // A 혹은 B 입력
int in_num[1501][1501];  // 개수 입력
int max_sum_a[1501][1501];	// 사과의 부분합 (맨 끝에서부터 인덱스가 1인 쪽으로 더함)
int max_sum_b[1501][1501];	// 바나나의 부분합 (맨 끝에서부터 인덱스가 1인 쪽으로 더함)
int dp[1501][1501];

int main(void)
{
	// 입력받기
	int R, C;
	cin >> R >> C;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> in_c[i][j];
			cin >> in_num[i][j];
		}
	}

	// 행별로 사과의 부분합 구하기, 단, 끝에서 1로 가야 한다.
	for (int i = 1; i <= R; i++) {
		for (int j = C; j > 0; j--) {
			if (in_c[i][j] == 'A') {
				if (j == C)	max_sum_a[i][j] = in_num[i][j];
				else max_sum_a[i][j] = max_sum_a[i][j + 1] + in_num[i][j];
			}
			else {
				if (j == C) max_sum_a[i][j] = 0;
				else max_sum_a[i][j] = max_sum_a[i][j + 1];
			}
		}
	}
	
	// 열별로 바나나의 부분합 구하기, 단, 끝에서 1로 가야 한다.
	for (int j = 1; j <= C; j++) {
		for (int i = R; i > 0; i--) {
			if (in_c[i][j] == 'B') {
				if (j == R)	max_sum_b[i][j] = in_num[i][j];
				else max_sum_b[i][j] = max_sum_b[i+1][j] + in_num[i][j];
			}
			else {
				if (i == R) max_sum_b[i][j] = 0;
				else max_sum_b[i][j] = max_sum_b[i+1][j];
			}
		}
	}

#ifdef DEBUG

	cout << "\n\nmax_sum_a\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << max_sum_a[i][j] << " ";
		}
		cout << "\n";
	}


	cout << "\n\nmax_sum_b\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << max_sum_b[i][j] << " ";
		}
		cout << "\n";
	}

#endif

	// dp 배열 초기화
	for (int i = 0; i <= R; i++) {
		for (int j = 0; j <= C; j++) {
			dp[i][j] = -1;
		}
	}
	
	// dp[i][j] : (1,1)부터 (i,j)까지 불도저가 이동할 때,
	//			  사과와 바나나를 더한 최대 값
	
	// dp배열 초기값 설정
	// dp[1][1] = max_sum_a[1][1] + max_sum_a[2][1] + max_sum_a[3][1] + ...
	//			+ max_sum_b[1][1] + max_sum_b[1][1] + ...
	//			- max_sum_a[1][1] - max_sum_b[1][1]
	
	dp[1][1] = 0;
	for (int i = 2; i <= R; i++) {
		dp[1][1] += max_sum_a[i][1];
	}
	
	for (int i = 2; i <= C; i++) {
		dp[1][1] += max_sum_b[1][i];
	}

	cout << "\ndp[1][1]=" << dp[1][1] << "\n";

	// dp[i][j]의 경우는, 다음 3가지 경우가 있다.
	// 불도저가 위에서 내려오는 경우, 왼쪽에서 오는 경우, 대각선으로 오는 경우
	// 이 세 경우 중 사과와 바나나의 합이 더 크게 되는 값을 취한다.
	// index가 1인 경우는 특수한 경우이므로 이 경우는 한 면만 보면 된다.

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (i == 1 && j == 1) continue;
			if (i == 1) {
				// i == 1일 경우, 바나나에 영향을 준다. 따라서 그 줄 바나나는 일단 없앤다.
				dp[1][j] = dp[1][j - 1] - in_num[1][j];
			}
			else if (j == 1) {
				// j == 1일 경우, 사과에 영향을 준다. 따라서 그 줄 사과는 모두 없앤다.
				dp[i][1] = dp[i - 1][1] - in_num[i][1];
			}
			else {
				// 일반적인 경우 계산
				dp[i][j] = max(dp[i - 1][j - 1] - max_sum_a[i][j] - max_sum_b[i][j], max(dp[i][j - 1] - max_sum_a[i][j], dp[i - 1][j] - max_sum_b[i][j]));
			}
		}
	}
	
#ifdef DEBUG
	cout << "\n\ndp\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << dp[i][j] << " ";
		}
		cout << "\n";
	}

#endif
	/*
	// 불도저가 위에서 내려오는 경우, 사과에 영향을 준다. 따라서 그 줄 사과를 구한다.
	dp[i][j] = dp[i][j - 1] - max_sum_a[i][j];

	// 불도저가 왼쪽에서 오는 경우, 바나나에 영향을 준다. 따라서 그 줄 바나나를 구한다.
	dp[i][j] = dp[i - 1][j] - max_sum_b[i][j];

	// 불도저가 대각선으로 오는 경우, 사과와 바나나 모두에 영향을 주므로, 그 둘을 모두 구한다.
	dp[i][j] = dp[i - 1][j - 1] - max_sum_a[i][j] - max_sum_b[i][j];
	*/
	// 오른쪽으로 가는 경우
	// 다음 칸의 열에 해당하는 바나나의 부분합을 더한다. 
	
	
	// 대각선으로 가는 경우
	// 다음 칸의 행, 열에 해당하는 사과와 바나나의 부분합을 더한다.
	
	
	// 아래로 가는 경우
	// 다음 칸의 행에 해당하는 사과의 부분합을 더한다.

	// 답안 출력
	cout << dp[R][C];
	return 0;
}