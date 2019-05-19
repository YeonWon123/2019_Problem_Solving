#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, k;
int p[101];//동전 하나의 금액
int n[101];//동전의 개수
int coin[101];
int position[101];
int dp[101];

int main()
{
	int result = 0;

	cin >> T >> k;
	for (int i = 0; i < k; i++) {
		cin >> p[i] >> n[i]; 
	}
	memcpy(coin, p, k*4);
	sort(coin, coin + k);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (coin[i] == p[j]) {
				position[i] = j;
				break;
			}
		}
	}

	for (int i = 1; i <= k; i++) {
		
	}

    return 0;
}

