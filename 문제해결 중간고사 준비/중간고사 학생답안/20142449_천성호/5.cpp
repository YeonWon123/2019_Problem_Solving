#include <cstdio>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

int N, M, k;
int gs[100][4];
long long dp[101][101];

typedef struct {
	int sx, sy, dx, dy;
}myS;

vector<myS> myV;

//source to destination
//true : 통행가능 / false : 공사중
bool judge(int sx, int sy, int dx, int dy) {
//	printf("x = %d y =%d xx = %d yy = %d\n", sx, sy, dx, dy);
	for (int i = 0; i < myV.size(); ++i) {
		myS tmp = myV[i];
		if (sx == tmp.sx && sy == tmp.sy && dx == tmp.dx && dy == tmp.dy) {
			//if ((sx == tmp.sx) && (sy == tmp.sy && dx = tmp.dx && dy == tmp.dy) {
	//		printf("return false\n");
			return false;
		}
	}

//	printf("return true");
	return true;
}

void print(void) {
	printf("\n");
	for (int i = 0; i <= M; ++i) {
		for (int j = 0; j <= N; ++j) {
			printf("%10d", dp[i][j]);
		}
		printf("\n");
	}
}

void print_v(void) {
	for (int i = 0; i < myV.size(); ++i) {
		myS tmp = myV[i];
		printf("x = %d y =%d xx = %d yy = %d\n", tmp.sx, tmp.sy, tmp.dx, tmp.dy);
	}
}

int main(void)
{
	scanf("%d %d", &N, &M);
	scanf("%d", &k);
	for (int i = 0; i < k; ++i) {
		int a, b, c, d;
		scanf(" %d %d %d %d", &b, &a, &d, &c);//&gs[i][0], &gs[i][1], &gs[i][2], &gs[i][3]);
											  //상하
		myS tmp;
		if (b == d) {
		//	printf("b==d\n");
			int low, high;
			if (a > c) {
				low = c; high = a;
			}
			else {
				low = a; high = c;
			}
			for (int i = low; i < high; ++i) {
				tmp.sx = i;
				tmp.sy = b;
				tmp.dx = i + 1;
				tmp.dy = d;
				myV.push_back(tmp);
//				printf("push_back %d %d -> %d %d\n", i, b, i + 1, d);
			}

		}
		//좌우
		else if (a == c) {
		//	printf("a=c\n");
			int left, right;
			if (b > d) {
				right = b; left = d;
			}
			else {
				right = d; left = b;
			}
			for (int i = left; i < right; ++i) {
				tmp.sx = a;
				tmp.sy = i;
				tmp.dx = c;
				tmp.dy = i + 1;
				myV.push_back(tmp);
//				printf("push_back %d %d -> %d %d\n", a, i, c, i+1);
			}
		}
	}

	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;

	for (int i = 0; i < M; ++i) {
		if (judge(i, 0, i + 1, 0)) {
			dp[i + 1][0] += dp[i][0];
		}
	}

	for (int j = 0; j < N; ++j) {
		if (judge(0, j, 0, j + 1)) {
			dp[0][j + 1] += dp[0][j];
		}
	}

//	print();

	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (judge(i-1, j, i, j)) {
				dp[i][j] += dp[i - 1][j];
			}
			if (judge(i, j - 1, i, j)) {
				dp[i][j] += dp[i][j - 1];
			}
		}
	//	print();
	}

	//print_v();
//	print();
	printf("%d\n", dp[M][N]);


	return 0;
}