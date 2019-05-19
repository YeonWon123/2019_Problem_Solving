#include <iostream>
#include <vector>
using namespace std;
struct Coin { int v, n; };
void Print(vector<int> a) {
	for (int i = 0, l = a.size(); i < l; i++) {
		cout << a[i] << ' ';
	}cout << '\n';
}
int main() {
	int t, k,v,n; cin >> t >> k;
	vector<int> dp(t + 1), tmp(t + 1);
	dp[0] = 1;
	for(int i=0;i<k;i++){
		cin >> v >> n;
		for (int j = 0, val = v; j < n; j++, val += v) {
			for (int b = 0; b <= t - val; b++) {
				tmp[b + val] += dp[b];
			}
		}
		for (int j = 0; j <= t; j++) {
			if (tmp[j]) { dp[j] += tmp[j]; tmp[j] = 0; }
		}
		Print(dp);
	}
	
	cout << dp[t];
	system("pause");
}