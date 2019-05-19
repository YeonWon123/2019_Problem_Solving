#include <cstdio>
using namespace std;

int n, m, k;
long long answer[101][101];
bool p[101][101];

int start_x[101];
int start_y[101];
int end_x[101];
int end_y[101];

bool is_ok(int y1, int x1, int y2, int x2) {
	for (int i = 0; i < k; i++) {
		if (start_x[i] == x1 && start_y[i] == y1 && end_x[i] == x2 && end_y[i] == y2) return false;
		if (start_x[i] == x2 && start_y[i] == y2 && end_x[i] == x1 && end_y[i] == y1) return false;
	}

	return true;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w+", stdout);

	scanf("%d %d", &n, &m);
	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		scanf("%d %d %d %d", &start_y[i], &start_x[i], &end_y[i], &end_x[i]);
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 && j == 0) {
				answer[i][j] = 1;
			}
			else if (i == 0) {
				if (is_ok(i, j, i, j - 1)) {
					answer[i][j] = answer[i][j - 1];
				}
			}
			else if (j == 0) {
				if (is_ok(i, j, i - 1, j)) {
					answer[i][j] = answer[i - 1][j];
				}
			}
			else{
				if (is_ok(i, j, i, j - 1)) {
					answer[i][j] += answer[i][j - 1];
				}
				if (is_ok(i, j, i - 1, j)) {
					answer[i][j] += answer[i - 1][j];
				}
			}
		}
	}

	printf("%lld", answer[n][m]);

	return 0;
}