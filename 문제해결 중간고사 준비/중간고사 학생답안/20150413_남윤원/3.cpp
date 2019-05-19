#include <iostream>
using namespace std;

#define DEBUG

int dp[10001] = { 0, };		// 지폐의 금액

int dp_counts[100001] = { 0, }; // 가치를 누적합으로 구하기

int coins[101] = { 0, };		// 동전의 가치
int counts[101] = { 0, };		// 동전의 개수

int main()
{
	// 입력받기
	int T;			// 지폐의 금액
	cin >> T;
	int k;			// 동전의 가지수
	cin >> k;

	for (int i = 1; i <= k; i++) {
		cin >> coins[i];
		cin >> counts[i];
	}

	// dp를 돌려서, 그 지폐의 금액을 만드는 방법을 찾자
	// 지폐의 금액마다...
	// 동전마다... 다 해보자!
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