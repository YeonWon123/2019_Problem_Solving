#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<numeric>
#define FOR(i,n) for(int i=0;i<(n);++i)
#define INF 2147483647
using namespace std;

int n, m, k, a, b, c, d,fail[105][105];
long long dp[105][105];

int main() {
	cin >> n >> m;
	cin >> k;
	while(k--) {
		scanf(" %d %d %d %d", &a, &b, &c, &d);
		fail[min(a, c)][min(b, d)] = 1;
	}
	for(int i=0;i<n;++i) {
		if (fail[0][i] != 1) { dp[0][i + 1] = 1; }
		else break;
	}
	for (int i = 0; i < n; ++i) {
		if (fail[i][0] != 1) {
			dp[i + 1][0] = 1; 
		}
		else break;
	}
	
	for(int i=1;i<=n;++i) {
		for (int j = 1; j <= m; ++j) {
			if (fail[i-1][j]) dp[i][j] = dp[i][j-1]; //i길 공사
			else if (fail[i][j-1]) dp[i][j] = dp[i-1][j]; //j길 공사
			else dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}
	cout << dp[n][m]<<'\n';

	//d[i][j]=d[i-1][j]+d[i][j-1]
	//if(i-1 -> i 공사) d[i][j]=d[i-1][j]
	//if(j-1 -> j 공사) d[i][j]=d[i][j-1]

}