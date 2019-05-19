#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>>coins;
vector<vector<int>> dp;
int t, k;

int solve(int from, int price) {
	if (price == 0) {
		return 1;
	}
	if (from == k || price < 0) {
		return 0;
	}

	int &ret = dp[from][price];
	if (ret != -1) return ret;

	ret = 0;

	int val = coins[from].first, cnt = coins[from].second;
	for (int i = 0; i <= cnt; ++i) {
		ret += solve(from + 1, price - val*i);
	}
	return ret;
}

int main()
{
	cin >> t >> k;
	dp.resize(k, vector<int>(t + 1, -1));
	for (int i = 0; i < k; ++i) {
		int val, cnt;
		cin >> val >> cnt;
		coins.push_back(make_pair(val, cnt));
	}
	cout << solve(0, t) << endl;
	return 0;
}

