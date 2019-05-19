#include <iostream>
using namespace std;

int arr[2001];
int dp[2001][2001]; // dp[i][j] : arr[i]부터 arr[j]까지가 팰린드롬인지 확인
int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;		// 수열의 크기
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	// arr[s] 부터 arr[e]까지 팰린드롬인지 확인해보자 (dp 이용)
	// 우선, s와 e가 같으면 팰린드롬이다. 따라서 dp배열을 초기화하자
	for (int j = 1; j <= N; j++)
		dp[j][j] = 1;

	// 만약 e = s+1이면 (즉 원소의 수가 2개이면) arr[s] = arr[e]여야 팰린드롬이다.
	for (int j = 1; j <= N - 1; j++) {
		if (arr[j] == arr[j + 1]) dp[j][j + 1] = 1;
		else dp[j][j + 1] = 0;
	}

	// dp 점화식 : dp[s][e] = dp[s+1][e-1] (arr[s] == arr[e])
	// dp 점화식 : dp[s][e] = 0			   (arr[s] != arr[e])
	for (int j = 2; j < N; j++) {
		for (int i = 1; (i + j) <= N; i++) {
			if (arr[i] == arr[i + j]) {
				dp[i][i + j] = dp[i + 1][i + j - 1];
			}
			else dp[i][i + j] = 0;
		}
	}

	int M;		// 질문의 개수
	cin >> M;

	for (int i = 1; i <= M; i++) {
		int S, E;
		cin >> S >> E;
		// arr[s] 부터 arr[e]까지 팰린드롬인지 확인해보자 (dp 이용)
		// dp 점화식 : dp[s][e] = dp[s+1][e-1] (arr[s] == arr[e])
		// dp 점화식 : dp[s][e] = 0			   (arr[s] != arr[e])
		cout << dp[S][E] << "\n";
	}
	return 0;
}