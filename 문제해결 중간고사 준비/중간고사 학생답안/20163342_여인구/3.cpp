#include <iostream>
#define MAX 100
#define P 0	// 동전의 금액
#define N 1	// 동전의 개수
using namespace std;
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <queue>

int main() {
	int t, k;
	int count = 0;
	int coin[MAX + 1][2] = { 0, };
	int sortedCoin[MAX + 1][2] = { 0, };

	cin >> t >> k;
	for (int i = 0; i < k; i++) {
		cin >> coin[i][P] >> coin[i][N];
		for (int j = i; j >= 0; j--) {
			if (coin[i][P] > sortedCoin[j][P]) {
				for (int m = i - 1; m >= j; m--) {
					sortedCoin[m + 1][P] = sortedCoin[m][P];
					sortedCoin[m + 1][N] = sortedCoin[m][N];
				}
				sortedCoin[j][P] = coin[i][P];
				sortedCoin[j][N] = coin[i][N];
			}
		}
	}

	while (1) {
		int temp = t;
		for (int i = 0; i < k; i++) {
			int curCion = sortedCoin[i][N];

		}

		// 다음 금액 ....
		// else break;

	}

	cout << count;

	return 0;
}