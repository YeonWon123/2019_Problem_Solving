#include<iostream>
#include<vector>

#define ll long long
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll n;
	cin >> n;
	vector<ll> len({ 3 });
	while (n > len.back()) {
		len.push_back(2*len.back() + len.size() + 3);
	}
	while (len.size() > 1 && (n <= len[len.size() - 2] || n > len[len.size() - 2] + len.size() + 2)) {
		if (n > len[len.size() - 2] + len.size() + 2) {
			n -= len[len.size() - 2] + len.size() + 2;
		}
		len.pop_back();
	}
	if (len.size() == 1 && n == 1 || len.size() > 1 && n == len[len.size() - 2] + 1) {
		cout << "m";
	}
	else {
		cout << "o";
	}
	return 0;
}