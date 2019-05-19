#include <iostream>
#include <vector>
using namespace std;

vector<int> dp;

int main(void) {
	int N;
	int sum = 3;
	dp.push_back(3);
	for (int i = 2; i < 29; i++) {
		dp.push_back(sum = 2 * sum + i + 2);
	}

	for (int i = 0; i < 28; i++) {
		for (int j = i; j < 28; j++) {
			dp.push_back(dp[j + 1] - dp[i]);
		}
	}
	
	scanf("%d", &N);

	for (int i = 0; i < dp.size(); i++) {
		if (N == dp[i] + 1) {
			printf("m");
			return 0;
		}
	}

	printf("o");
	return 0;
}