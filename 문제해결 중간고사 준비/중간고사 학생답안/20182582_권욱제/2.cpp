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

int n, m;
int a[100001];

int f(int mid) {
	int cnt = 1;
	int mn = 1e9;
	int mx = -1;
	for (int i = 1; i <= n; i++) {
		mn = min(mn, a[i]);
		mx = max(mx, a[i]);
		if (mx - mn > mid) {
			cnt++;
			mn = a[i], mx = a[i];
		}
	}
	return cnt <= m;
}

int main() {
	//cin.tie(0); ios_base::sync_with_stdio(0);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	int lft = 0, rgt = 1e9;
	int ans;
	while (lft <= rgt) {
		int mid = (lft + rgt) / 2;
		if (f(mid)) {
			ans = mid;
			rgt = mid - 1;
		}
		else {
			lft = mid + 1;
		}
	}

	printf("%d", ans);

	return 0;
}

/*
8 3
1 5 4 6 2 1 3 7

7 4
1 2 3 1 2 3 1

5 2
1 100 99 2 3

4 2
1 1 1 1

5 1
1 100 99 2 3

5 3
1 100 99 2 3
*/