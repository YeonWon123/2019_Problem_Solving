#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int N, M;
int n[5003];
int m[5003];
int r[5003];

int fgn;
int maxD = 0;

void devide(int sn, int dn, int rn, int rd)
{
	if (rd == 1) {
		int fn = 10000;
		int fx = 0;
		for (int j = sn + dn; j <= N - 1; j++) {
			fn = min(fn, n[j]);
			fx = max(fx, n[j]);
		}
		m[M] = fx - fn;
		
		for (int k = 1; k <= M; k++) {
			maxD = max(maxD, m[k]);
		}
		r[fgn] = min(r[fgn], maxD);
		maxD = 0;
		return;
	}

	for (int i = 1; i <= rn - rd + 1; i++) {
		int gn = 10000;
		int gx = 0;
		for (int j = sn + dn; j < sn + dn + i; j++) {
			gn = min(gn, n[j]);
			gx = max(gx, n[j]);
		}
		m[M - rd + 1] = gx - gn;

		devide(sn + dn, i, rn - i, rd - 1);
	}

	return;
}

int main(void)
{
	int minD = 10000;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &n[i]);
	}

	for (int i = 0; i <= N - M + 1; i++) {
		r[i] = 10000;
	}

	if (M == 1) {
		int gn = 10000;
		int gx = 0;
		for (int i = 0; i < N; i++) {
			gn = min(gn, n[i]);
			gx = max(gx, n[i]);
		}
		minD = gx - gn;
		printf("%d", minD);
		return 0;
	}

	for (fgn = 1; fgn <= N - M + 1; fgn++) {
		int gn = 10000;
		int gx = 0;
		for (int j = 0; j < fgn; j++) {
			gn = min(gn, n[j]);
			gx = max(gx, n[j]);
		}
		m[1] = gx - gn;

		devide(0, fgn, N - fgn, M - 1);

	}

	for (int i = 1; i <= N - M + 1; i++) {
		minD = min(minD, r[i]);
	}

	printf("%d", minD);

	return 0;
}
