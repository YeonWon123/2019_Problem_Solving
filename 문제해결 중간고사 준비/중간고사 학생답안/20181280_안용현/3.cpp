#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t, k;
	cin >> t >> k;
	vector<pair<int, int>> v;
	for(int i = 0; i < k; i ++) {
		int p, n;
		cin >> p >> n;
		v.push_back(make_pair(p, n));
	}
	sort(v.begin(), v.end());
	vector<int> d(t + 1);
	d[0] = 1;
	int maxval = 0;
	for (auto it : v) {
		for (int T = maxval; T >=0; T--) {
			if (d[T]) {
				for (int i = 1; i <= it.second && T + it.first * i <= t; i++) {
					d[T + it.first * i] += d[T];
				}
			}
		}
		maxval = min(t, maxval + it.first * it.second);
	}
	cout << d.back();
	return 0;
}