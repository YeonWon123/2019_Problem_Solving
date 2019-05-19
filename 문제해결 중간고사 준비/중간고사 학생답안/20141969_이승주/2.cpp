#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<numeric>
#define FOR(i,n) for(int i=0;i<(n);++i)
#define INF 2147483647
using namespace std;

int n, a[5005], m, mx, flag, sum, cnt, res,Mx,Mn;

int main() {
	cin >> n >> m;
	FOR(i, n) {
		scanf("%d", &a[i]);
		mx=max(mx,a[i]);
	}
	int left = 0;
	int right = mx + 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		Mx = 0, Mn = 987654321, cnt = 1;
		FOR(i, n) {
			Mx = max(Mx, a[i]);
			Mn = min(Mn, a[i]);
			if (Mx-Mn > mid) {
				Mx = 0, Mn = 987654321;
				++cnt;
			}
		}
		if (cnt > m) right = mid - 1;
		else {
			left = mid + 1;
			if (res < mid) res = mid;
		}
	}
	cout << res << '\n';
}