#include <iostream>

using namespace std;

int seq_len[28];

bool solve(int m) {
	if (m == 1) return true;
	if (m == 2 || m == 3) return false;
	int k = 0;
	while (m > seq_len[k]) {
		++k;
	}
	int cur = seq_len[k];
	int prev = seq_len[k - 1];
	if (m == prev + 1) {
		return true;
	}
	if (m <= cur - prev) {
		return false;
	}
	return solve(m - cur + prev);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int m;
	cin >> m;

	for (int k = 0, len = 3; k < 28;) {
		seq_len[k] = len;
		++k;
		len = 2 * len + k + 3;
	}
	cout << (solve(m) ? 'm' : 'o') << endl;
	return 0;
}

