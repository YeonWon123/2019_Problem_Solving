#include <cstdio>

int N, K;
int E[200];

int main() {
	// freopen("input5.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", E + i);
	}

	int i = 0, j = N - 1;
	int c = -1;

	while (i <= j) {
		while (E[i] == E[i + 1]) ++i;
		while (E[j] == E[j - 1]) --j;

		if (E[i] == E[j]) {
			++i;
			--j;
		}
		else {
			int _j = j;
			while (E[--_j] == E[i]);

			int _i = i;
			while (E[++_i] == E[j]);

			if (j - _j < _i - i) {
				++i;
			}
			else {
				--j;
			}
		}

		++c;
	}

	printf("%d", c);
}