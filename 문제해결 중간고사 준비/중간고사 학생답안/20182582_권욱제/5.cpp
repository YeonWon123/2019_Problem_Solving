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

#define y1 asdfjwaefjoeafjai

int n, m, k;
bool c[102][102][2];
pii a, b;
ll d[101][101];

int main() {
	//cin.tie(0); ios_base::sync_with_stdio(0);

	scanf("%d %d %d", &n, &m, &k);
	while (k--) {
		scanf("%d %d %d %d", &a.first, &a.second, &b.first, &b.second);
		if (a > b) swap(a, b);
		c[b.first][b.second][a.first != b.first] = 1;
	}

	d[0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i - 1 >= 0 && !c[i][j][1]) {
				d[i][j] += d[i - 1][j];
			}
			if (j - 1 >= 0 && !c[i][j][0]) {
				d[i][j] += d[i][j - 1];
			}
			//printf("%4lld ", d[i][j]);
		}
		//puts("");
	}

	printf("%lld\n", d[n][m]);

	return 0;
}


/*

6 6
2
0 0 0 1
6 6 5 6

10 12
4
0 0 0 1
9 12 9 11
6 6 5 6
4 4 5 4

10 12
4
0 0 0 1
9 12 9 11
6 6 5 6
10 11 9 11

*/