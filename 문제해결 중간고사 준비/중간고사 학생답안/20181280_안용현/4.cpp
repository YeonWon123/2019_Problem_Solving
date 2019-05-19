#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	vector<int> v;
	while (n--) {
		int val;
		cin >> val;
		if (!v.empty() && v.back() == val) {
			v.pop_back();
		}
		v.push_back(val);
	}
	n = v.size();
	vector<vector<int>> d(n, vector<int>(n));
	for (int dif = 1; dif < n; dif++) {
		for (int b = 0; b + dif < n; b++) {
			int i = b, j = b + dif;
			if (v[i] == v[j]) {
				d[i][j] = d[i][j - 1];
			}
			else {
				d[i][j] = min(d[i][j - 1], d[i + 1][j]) + 1;
			}
		}
	}
	cout << d[0][n - 1];
	return 0;
}
/*
10 3
1 1 2 3 3 3 2 2 1 1
*/