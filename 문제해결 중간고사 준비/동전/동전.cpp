#include <iostream>
using namespace std;

int arr[21];
int dp[10001] = { 0, };		// 1부터 10000까지 금액을 만드는 방법의 수
	//ex) k-arr[j]를 만들 수 있는 방법의 수 : dp[k-arr[j]]

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;	// 테스트 케이스의 개수
	cin >> T;

	for (int i = 0; i < T; i++) {
		int N, M;
		cin >> N; // 동전의 가지 수
		for (int j = 1; j <= N; j++) {
			cin >> arr[j];	// N가지 동전의 각 금액이 오름차순으로 정렬되어 주어짐
		}
		cin >> M; // 주어진 N가지 동전으로 만들어야 할 금액

		// 앞에서부터 dp를 한다.
		// 첫 번째 동전으로 만들 수 있는 방법의 수를 dp에 저장...
		// 첫 번째 + 두 번째 동전으로 만들 수 있는 방법의 수를 dp에 저장...

		dp[0] = 1;
		// 동전의 가치 수에 대해 loop
		for (int j = 1; j <= N; j++) {
			// 금액을 1부터 M까지 따지기 위해 loop
			for (int k = 1; k <= M; k++) {
				// 만약 k-arr[j]가 0보다 크거나 같으면 
				// 즉, arr[j]과 k-arr[j]를 더해서 k를 채울 수 있으면 (이 값이 음수이면 안됨)
				// k-arr[j]를 만들 수 있는 방법의 수인 dp[k-arr[j]]를 dp[k]에 더해준다.
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