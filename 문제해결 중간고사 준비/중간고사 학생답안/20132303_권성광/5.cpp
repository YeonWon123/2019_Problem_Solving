#include <cstdio>
#include <cinttypes>
#include <set>
#include <utility>

using namespace std;

int N, M, K;
int64_t P[102][102];
set<int64_t> S;

int64_t conv(int64_t a, int64_t b, int64_t c, int64_t d) {
	if (a * 1000LL + b < c * 1000LL + d) return a * 1000000000LL + b * 1000000LL + c * 1000LL + d;
	return c * 1000000000LL + d * 1000000LL + a * 1000LL + b;
}

bool broken(int64_t n) {
	return S.find(n) != S.end();
}

int main() {
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &N, &M, &K);

	for (int a, b, c, d; ~scanf("%d%d%d%d", &a, &b, &c, &d);) {
		S.insert(conv(a, b, c, d));
	}

	P[0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		if (!broken(conv(i, 0, i - 1, 0))) P[i][0] = P[i-1][0];
	}
	for (int i = 1; i <= M; ++i) {
		if (!broken(conv(0, i, 0, i - 1))) P[0][i] = P[0][i-1];
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (!broken(conv(i, j, i - 1, j))) {
				P[i][j] += P[i - 1][j];
			}
			if (!broken(conv(i, j, i, j - 1))) {
				P[i][j] += P[i][j - 1];
			}
		}
	}

	printf("%" PRId64, P[N][M]);
}