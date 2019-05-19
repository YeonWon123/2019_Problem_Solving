#include<iostream>
#include<cstdio>
#include<deque>
#include<algorithm>
using namespace std;

int dp[10001];
int T, k;
int n[10001];
deque<int> p;

int main() {
	int temp1, temp2;
	cin >> T;
	cin >> k;
	for (int i = 0; i < k; i++) {
		scanf("%d", &temp1);
		scanf("%d", &temp2);
		p.push_back(temp1);
		for (int j = 0; j < temp2; j++) {
			n[temp1]++;
		}
	}

	dp[0] = 1;
	while (!p.empty()) {
		int here = p.front();
		p.pop_front();
		for (int i = T; i >= 1; i--) {
			for (int j = 1; j <= n[here]; j++) {
				if((i - (here * j)) >= 0)
					dp[i] += dp[i - (here * j)];
			}
		}
	}

	cout << dp[T];

	return 0;
}