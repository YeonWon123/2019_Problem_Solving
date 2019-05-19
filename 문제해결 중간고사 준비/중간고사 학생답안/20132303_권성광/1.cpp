#include <cstdio>
#include <cinttypes>

int64_t P[29] = { 0, };

bool S(int N) {
	int i = 0;
	for (; P[i + 1] <= N; ++i);

	N -= P[i];
	if (N < i + 3) {
		return N == 0;
	}
	N -= i + 3;
	return S(N);
}

int main() {
	//freopen("input.txt", "r", stdin);
	int N;
	scanf("%d", &N);
	--N;
	int i = 1;
	for (; i < 29; ++i) {
		P[i] = P[i - 1] * 2 + i + 2;
	}
	puts(S(N) ? "m" : "o");
}
