#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int n;
int d[500005];

void go(int i) {
	if (d[i - 1] < n && n <= d[i - 1] + i + 2 + 1) {
		puts(d[i - 1] + 1 == n ? "m" : "o");
		exit(0);
	}
	if (n <= d[i - 1]) {
		go(i - 1);
	}
	else {
		n = n - (i + 2 + 1) - d[i - 1];
		go(i - 1);
	}
}

int main() {
	//cin.tie(0); ios_base::sync_with_stdio(0);
	
	scanf("%d", &n);
	d[0] = 3;
	d[1] = 10;
	for (int i = 2; i <= 500000; i++) {
		d[i] = d[i - 1] + d[i - 1] + i + 2 + 1;
		if (d[i] >= 1e9) {
			break;
		}
	}

	if (n == 1) {
		puts("m");
		return 0;
	}
	else if (n == 2 || n == 3) {
		puts("o");
		return 0;
	}

	int m = 27;
	int idx;
	for (int i = 1; i <= m; i++) {
		if (d[i-1] < n && n <= d[i]) {
			go(i); break;
		}
	}

	return 0;
}