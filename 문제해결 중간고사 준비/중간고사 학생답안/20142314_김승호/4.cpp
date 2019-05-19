#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;
vector<vector<int>>dp;
int n, k;

int solve(int lo, int hi) {
	if (hi - lo == 0) {
		return 0;
	}

	int &ret = dp[lo][hi];
	if (ret != -1) return ret;
	ret = n * k + 1;
	for (int i = lo; i < hi; ++i) {
		ret = min(ret, solve(lo, i) + solve(i + 1, hi) + (arr[lo] == arr[hi] ? 0 : 1));
	}
	return ret;
}

int main()
{
	cin >> n >> k;
	arr.resize(n);
	dp.resize(n, vector<int>(n, -1));
	for (auto &i : arr) {
		cin >> i;
	}

	cout << solve(0, n - 1) << endl;
	return 0;
}

