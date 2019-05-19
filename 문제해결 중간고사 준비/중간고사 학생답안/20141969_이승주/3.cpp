#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#define FOR(i,n) for(int i=0;i<(n);++i)
using namespace std;

int t, k, a[105], cnt[105], d[10005];

int main() {
	cin >> t >> k;
	FOR(i, k) {
		scanf("%d%d", &a[i], &cnt[i]);
	}
	d[0] = 1;
	FOR(i, k) {
		for (int j = 10000; j >= 0; --j) {
			for (int k = 1; k <= cnt[i]; ++k) {
				if (j - k*a[i] < 0) break;
				d[j] += d[j - k*a[i]];
			}
		}
	}
	cout << d[t]<<'\n';
}