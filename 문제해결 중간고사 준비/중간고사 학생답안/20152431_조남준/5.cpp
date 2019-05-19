#include <stdio.h>
#include <algorithm>

int N, M;
int K;
int a;
int b;
int c;
int d;
long long int map[100][100];
int block[100][4];

int main(void)
{
	scanf("%d %d", &N, &M);
	scanf("%d", &K);
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			map[j][i] = 1;
		}
	}
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		block[i][0] = a;
		block[i][1] = b;
		block[i][2] = c;
		block[i][3] = d;
		if (a > c || b > d) map[b][a] = 0;
		else if (a < c || b < d) map[d][c] = 0;

		if ((a == 0 && c == 0) || (b == 0 && d == 0)) {
			if (a == 0) {
				if (b > d) {
					for (int i = b; i <= M; i++) {
						map[i][0] = 0;
					}
				}
				else if (d > b) {
					for (int i = d; i <= M; i++) {
						map[i][0] = 0;
					}
				}
			}
			else if (b == 0) {
				if (a > c) {
					for (int i = a; i <= N; i++) {
						map[0][i] = 0;
					}
				}
				else if (c > a) {
					for (int i = c; i <= N; i++) {
						map[0][c] == 0;
					}
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[j][i] == 0) {
				for (int l = 0; l < K; l++) {
					if (block[l][0] == i || block[l][2] == i) {
						if (block[l][1] == j || block[l][3] == j) {
							if (block[l][0] - block[l][2] == 0) {
								map[j][i] = map[j][i - 1];
							}
							else if (block[l][1] - block[l][3] == 0) {
								map[j][i] = map[j - 1][i];
							}
						}
					}
				}
				continue;
			}
			map[j][i] = map[j][i - 1] + map[j - 1][i];
		}
	}

	printf("%ld\n", map[M][N]);

	return 0;
}