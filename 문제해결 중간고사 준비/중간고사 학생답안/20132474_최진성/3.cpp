#include <cstdio>
#include <map>
using namespace std;

int T, k;
long long dp[10005];
map<int, int> coin;

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w+", stdout);

	scanf("%d", &T);
	scanf("%d", &k);
	for (int i = 0,a,b; i < k; i++) {
		scanf("%d %d", &a, &b);
		coin[a] = b;
	}

	dp[0] = 1;

	for (auto it = coin.begin(); it != coin.end(); it++) {
		pair<int, int> c = *it;

		for (int i = T; i >= 0; i--) {
			if (dp[i] > 0){
				for (int j = 1; j <= c.second; j++) {
					if (i + c.first*j > 10002) break;
					dp[i + c.first*j] += dp[i];
				}
			}
		}
	}

	printf("%lld", dp[T]);

	return 0;
}