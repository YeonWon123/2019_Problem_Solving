#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int T, K;
int p, n;
int d[100001] = { 0 };
int dp[100001] = { 0 };

int main() {
	int k = 0;
	cin >> T;
	cin >> K;

	for (int i = 0; i < K; i++) {

		cin >> p >> n;

		for (int j = 0; j < n; j++) {
			d[k++] = p;
		}
	}

	sort(d.begin(), d.end());

	for (int i = 0; i < k; i++) {

		for (int j = d[i]; j > 0; j--) {
			dp[i] += d[i];
		}

	}





}