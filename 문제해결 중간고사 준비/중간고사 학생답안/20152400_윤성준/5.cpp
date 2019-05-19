#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int N, M, K;
int street[103][103];

int main(void)
{
	long long res;

	scanf("%d %d", &N, &M);

	for (int i = 0; i <= M; i++) {
		for (int j = 0; j <= N; j++) {
			if ((i == 0) || (j == 0)) {
				street[j][i] = 1;
			}
			else
				street[j][i] = street[j-1][i] + street[j][i-1];
		}
	}
	res = street[N][M];
	printf("res: %ld\n", res);

	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		int a, b, c, d, tmp;
		long long fix;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if (a > c) {
			tmp = a;
			a = c;
			c = tmp;
		}
		if (b > d) {
			tmp = b;
			b = d;
			d = tmp;
		}

		fix = street[a][b] * street[N-c][M-d];
		res -= fix;
	}
	res += street[5][5];

	printf("%d", res);
	return 0;
}
