#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<int> v(n);
	for (auto i = 0; i < n; i++) {
		cin >> v[i];
	}
	int maxval = *max_element(v.begin(), v.end()), minval = *min_element(v.begin(), v.end());
	vector<int> s;
	for (int i = 0; i <= maxval - minval; i++) {
		s.push_back(i);
	}
	auto cmp = [=](int A, int B) {
		int cnt = 1;
		int curmin = 100000, curmax = 1;
		for (int i = 0; i < v.size(); i++) {
			curmin = min(curmin, v[i]);
			curmax = max(curmax, v[i]);
			if (curmax - curmin > B) {
				cnt++;
				curmax = curmin = v[i];
			}
			if (cnt > m) {
				break;
			}
		}
		return cnt <= m;
	};
	auto p = upper_bound(s.begin(), s.end(), 0, cmp);
	cout << *p;
	return 0;
}