#include <stdio.h>
#include <algorithm>
using namespace std;

int n, k;
int dp[100001];
int arr[101]; // 동전의 가치가 순서대로 들어간다.

int main(void)
{
	// 입력받는 부분
	scanf("%d %d", &n, &k);
	arr[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}

	// dp 배열을 초기화 (불가능한 경우 -1을 출력할 수 있게 하기 위해서)
	// 전부 -1로 일단 초기화한다.
	for (int i = 0; i <= 10000; i++) {
		dp[i] = -1;
	}

	// 입력받은 동전의 가치들을 정렬함
	sort(arr, arr + n + 1);

	// 각 동전들은 일단 1개로 가치가 되므로,
	// dp배열에 각 동전을 할당함.
	// ex) arr[0] = 1, arr[1] = 5, arr[2] = 12이면,
	// dp[1] = 1; dp[5] = 1; dp[12] = 1;이 되는 형식
	// 따라서 dp[arr[0]] = 1; dp[arr[1]] = 1; dp[arr[2]] = 1;이 된다.
	for (int i = 1; i <= n; i++) {
		dp[arr[i]] = 1;
	}

	// dp를 돌리자
	for (int i = 1; i <= k; i++) {
		// dp[i] == 1이면 해당 가치의 합은 이미 최솟값인 1로 정해져 있으므로
		// continue로 넘어간다.
		if (dp[i] == 1) continue;

		for (int j = 1; j <= n; ++j) {
			// 탐색하려는 arr[j]의 값이 현재의 가치의 합인 i보다 커지면,
			// 더 이상 둘 필요가 없으니 탈출
			if (arr[j] >= i) break;

			// dp[i]가 그 어떤 동전으로도 가치의 합을 구할 수 없을 때에 해당하니 탈출
			if (dp[i - arr[j]] == -1) continue;
			else {
				// else 안에 들어온다면, 가치의 합을 구할 수 있는 것이다.
				if (dp[i] == -1) {
					// dp[i]의 값을 처음 바꿀 때는 별다른 조건 없이 값을 변경
					dp[i] = dp[i - arr[j]] + 1;
				}
				else if (dp[i - arr[j]] + 1 < dp[i]) {
					// dp[i]의 값을 이미 바꾼적이 있다면, 둘 중 더 작은 값으로 변경
					dp[i] = dp[i - arr[j]];
				}
			}
		}
	}

	printf("%d", dp[k]);

}