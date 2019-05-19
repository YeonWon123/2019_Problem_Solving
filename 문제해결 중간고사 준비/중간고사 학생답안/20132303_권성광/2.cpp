#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
int P[5000];

int Max[5000][5000], Min[5000][5000];

int solve(int idx, int part) {
	if (part == 1) return Max[idx][N-1] - Min[idx][N-1];

	--part;
	int minimum = 100000;
	for (int i = 0; i < N - part; ++i) {
		minimum = min(minimum, max(Max[idx][idx + i] - Min[idx][idx + i], solve(idx + i + 1, part)));
	}
	return minimum;
}

int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) scanf("%d", P + i);
	for (int i = 0; i < N; ++i) {
		int M = 0;
		int m = 10000;
		for (int j = i; j < N; ++j) {
			M = max(M, P[j]);
			m = min(m, P[j]);
			Max[i][j] = M;
			Min[i][j] = m;
		}
	}
	printf("%d", solve(0, M));
}