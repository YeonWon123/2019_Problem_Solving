#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#define N 100
#define pii pair<int, int>
using namespace std;
typedef long long ll;
map<pii, set<pii> > mp;
ll dp[N + 1][N + 1];
int n, m;
ll go(int y, int x) {
	if (y > m || x > n) return 0;
	if (y == m && x == n) return 1;
	ll& ret = dp[y][x];
	if (ret != -1) return ret;
	ret = 0;
	pii p = make_pair(y, x + 1);
	auto v = mp[make_pair(y, x)].find(p);
	if (v == mp[make_pair(y, x)].end()) ret += go(y, x + 1);

	p = make_pair(y + 1, x);
	v = mp[make_pair(y, x)].find(p); 
	if (v == mp[make_pair(y, x)].end()) ret += go(y + 1, x);
	return ret;
}
int main(void)
{
	scanf("%d %d", &n, &m);
	int k;
	scanf("%d", &k);
	while (k--) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		pii p1 = make_pair(b, a), p2 = make_pair(d, c);
		if (p1.first + p1.second > p2.first + p2.second) swap(p1, p2);
		mp[p1].insert(p2);
	}
	memset(dp, -1, sizeof(dp));
	printf("%lld\n", go(0, 0));
}