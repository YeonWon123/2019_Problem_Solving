#include <iostream>
#include <vector>
using namespace std;
vector<int> num;
void Parametric(int left, int right, int m,int & ans) {
	if (left > right) { return;}
	int mid = (left + right) / 2,sum=0,min,max;
	vector<int> bracket;
	min = max = num[0];
	for (int i = 1, l = num.size(); i < l; i++) {
		if (min > num[i]) {
			if (max - num[i] >mid) { bracket.push_back(i-1); min = max = num[i]; }
		}
		else if (max < num[i]) {
			if (num[i] - min >mid) { bracket.push_back(i-1); min = max = num[i]; }
		}
	}
	if (bracket.size() && bracket.back() != num.size()) { bracket.push_back(num.size()); }
	if (bracket.size() <= m) {
		if (mid < ans&&bracket.size()) { ans = mid; }
		Parametric(left, mid - 1, m, ans);
	}
	else {
		Parametric(mid + 1, right, m, ans);
	}
}
int main() {
	int n, m, max = 0,min=60000000,ans=min,tm=0; cin >> n >> m;
	num.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> num[i];
		if (min > num[i])min = num[i];
		if (tm < num[i])tm = num[i];
		max += num[i];
	}
	if (m == 1) { cout << tm - min;}
	else {
		Parametric(min, max, m, ans);
		cout << (ans == 60000000 ? 0 : ans);
	}
}