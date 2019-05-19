#include <iostream>
#include <algorithm>
using namespace std;

int coins[101];	// 동전의 가치가 순서대로 들어감 (정렬 필요)
int dp[100001]; // 가치의 합이 i원이 될 때의 최소 동전 개수
				// 가치의 합은 최대 100000이 될 수 있으니
				// dp[100001]이렇게 선언!!

int main(void)
{
	// 입력 받기
	int n, k;
	cin >> n >> k;

	coins[0] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> coins[i];
	}

	// dp 배열을 채우자
	// 우선 dp 배열을 -1로 초기화
	for (int i = 0; i <= 10000; i++) {
		dp[i] = -1;
	}

	sort(coins, coins + n + 1);

	// 동전이 있으면, 그 값은 무조건 그 동전 하나로 만들 수 있으니
	// dp[]의 값은 1임!
	for (int i = 1; i <= n; ++i) {
		dp[coins[i]] = 1;
	}

	// 각 가치에 대해 dp[]를 채움 (그래서 dp가 100001인거임!)
	for (int i = 1; i <= k; ++i) {
		// dp가 1이면 해당 가치의 합은 이미 최솟값은 1로 정해져 있으니 패스
		if (dp[i] == 1) continue;

		// coins를 탐색해야 함
		for (int j = 1; j <= n; ++j) {
			// 탐색하려는 coins[j]의 값이 현재의 가치의 합인 i보다 커지면
			// 더이상 둘 필요가 없으니 탈출
			if (coins[j] - i >= 0) break;

			// dp[i]가 그 어떤 동전으로도 가치의 합을 구할 수 없을 때에 해당하니 패스
			if (dp[i - coins[j]] == -1) continue;
			else {
				// 여기에 도달하면, 가치의 합을 구할 수 있음
				// dp[i]의 값을 처음 바꿀 때는 별다른 조건 없이 값을 변경해 준다.
				if (dp[i] == -1) dp[i] = dp[i - coins[j]] + 1;
				// 그게 아니고 기존에 바꾼 적이 있다면, 지금의 값과 비교하여 더 작은 값으로 변경해준다.
				else if (dp[i - coins[j]] + 1 < dp[i]) dp[i] = dp[i - coins[j]] + 1;
			}
		}
	}

	cout << dp[k];
	return 0;
}