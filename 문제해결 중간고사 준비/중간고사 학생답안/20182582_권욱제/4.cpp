#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int n, k;
int b[222];
ll d[222][222][22];

int main() {
	//cin.tie(0); ios_base::sync_with_stdio(0);
	memset(d, 0x3f, sizeof(d));

	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}
	vector<int> a;
	a.push_back(-1);
	for (int i = 1; i <= n; i++) {
		if (b[i] != b[i + 1]) a.push_back(b[i]);
	}
	n = a.size()-1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			d[i][i][j] = 1;
		}
		d[i][i][a[i]] = 0;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			d[i][i + 1][j] = (a[i] != j) + (a[i + 1] != j);
		}
	}
	a.push_back(0);

	for (int len = 3; len <= n; len++) {
		for (int lft = 1; lft <= n; lft++) {
			int rgt = lft + len - 1;
			if (rgt > n) break;
			for (int col = 1; col <= k; col++) {
				for (int kk = 1; kk <= k; kk++) {
					int cnt = (a[lft] != col) + (a[rgt] != col) + (kk != col);
					d[lft][rgt][col] = min(d[lft][rgt][col], d[lft + 1][rgt - 1][kk] + cnt);
					d[lft][rgt][col] = min(d[lft][rgt][col], d[lft][rgt - 1][kk] + (a[rgt] != col) + (kk != col));
					d[lft][rgt][col] = min(d[lft][rgt][col], d[lft + 1][rgt][kk] + (a[lft] != col) + (kk != col));
				}
			}
		}
	}

	ll ans = 1e18;
	for (int i = 1; i <= k; i++) {
		ans = min(ans, d[1][n][i]);
	}

	printf("%lld\n", ans);

	return 0;
}

/*

10 3
1 1 2 3 3 3 2 2 1 1

10 3
1 3 2 3 1 3 2 3 1 1

10 3
1 3 2 3 3 3 2 3 1 1

10 4
1 3 2 3 1 3 2 3 4 1

*/