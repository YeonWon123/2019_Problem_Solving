#include <cstdio>
#include <vector>
#include <algorithm>
#define N 10000
using namespace std;
vector<pair<int, int> > v;
int dp[N + 1] = { 1, };
bool compare(pair<int, int>& a, pair<int, int>& b) {
	return a.first < b.first;
}
int main(void)
{
	int t, q;
	scanf("%d %d", &t, &q);
	int i, j, k;
	for (i = 0; i < q; ++i) {
		int p, n;
		scanf("%d %d", &p, &n);
		v.push_back(make_pair(p, n));
	}
	sort(v.begin(), v.end());
	for (i = 0; i < q; ++i) {
		for (j = t; j > 0; --j) {
			for (k = 1; k <= v[i].second; ++k) {
				int cost = v[i].first * k;
				if (cost > j) break;
				dp[j] += dp[j - cost];
			}
		}
	}
	printf("%d", dp[t]);
}