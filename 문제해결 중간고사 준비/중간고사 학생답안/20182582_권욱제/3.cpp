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

/*
int t, n;
int d[10011];
int tmp[10011];

int main() {
	//cin.tie(0); ios_base::sync_with_stdio(0);
	scanf("%d %d", &t, &n);
	d[0] = 1;
	vector<int> v;
	for (int i = 0; i < n; i++) {		// 100
		int val, cnt;
		scanf("%d %d", &val, &cnt);
		int sum = 0;
		while (cnt--) {					// 1000
			sum += val;
			if (sum > t) break;
			for (int i = t; i - sum >= 0; i--) {	// 10000
				tmp[i] += d[i - sum];
			}
		}
		for (int i = 0; i <= t; i++) {
			d[i] += tmp[i];
		}
		memset(tmp, 0, sizeof(tmp));
	}

	printf("%d\n", d[t]);

	return 0;
}
*/

int t, n;
ll d[10011];
ll tmp2[10011];

int main() {
	//cin.tie(0); ios_base::sync_with_stdio(0);
	scanf("%d %d", &t, &n);
	d[0] = 1;
	for (int i = 0; i < n; i++) {		// 100
		int val, cnt;
		scanf("%d %d", &val, &cnt);
		memset(tmp2, 0, sizeof(tmp2));
		for (int j = 0; j < val; j++) {
			for (int k = j; k <= t; k += val) {
				tmp2[k] = tmp2[k - val] + d[k];
			}
		}
		for (int i = t; i - val >= 0; i--) {	// 10000
			d[i] += tmp2[i - val];
			if (i >= val*(cnt + 1)) d[i] -= tmp2[i - val*(cnt+1)];
		}
	}

	printf("%d\n", d[t]);

	return 0;
}


/*

20
3
5 3
10 2
1 5

32
4
2 2
5 3
3 1
8 2

8
3
3 2
5 1
1 3

23
4
2 2
5 3
3 1
8 2

*/