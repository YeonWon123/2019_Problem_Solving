#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	int num;
	vector<vector<bool>> down(n + 1, vector<bool>(m + 1, true)), left(down);
	for (int i = 0; i <= n; i++) {
		left[i][0] = false;
	}
	for (int i = 0; i <= m; i++) {
		down[0][i] = false;
	}
	cin >> num;
	while (num--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 >= x2 && y1 >= y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		if (x1 == x2) {
			left[x2][y2] = false;
		}
		if (y1 == y2) {
			down[x2][y2] = false;
		}
	}
	vector<vector<long long>> d(n + 1, vector<long long>(m + 1));
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 && j == 0) {
				d[i][j] = 1;
				continue;
			}
			if (left[i][j]) {
				d[i][j] += d[i][j - 1];
			}
			if (down[i][j]) {
				d[i][j] += d[i - 1][j];
			}
		}
	}
	cout << d[n][m];
	return 0;
}