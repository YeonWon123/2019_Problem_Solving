/*
LCS의 크기를 구하는 문제이다.
우리는 다이나믹 프로그래밍을 이용하여 LCS를 구할 수 있다.
하지만 LCS4 문제는 N이 10만이기 때문에 다른 방법을 생각해보아야 한다.
단순히 N이 10만에서 최장 공통 부분 수열을 구하라고 한다면 
무척 어려운 문제가 되겠지만 다행히 조건이 더 주어진다.
1~N 까지 정수는 두 수열 A, B에서 전부 한번 씩 주어진다는 것이다.
우리는 수열 A에서 입력을 받은 후, 
입력 받은 수의 인덱스로 A[x]의 들어온 순서를 삽입하는 방식으로 A수열을 정의 해준 뒤, 
A[B[i]]의 LIS를 구함으로서 최장 공통 부분 수열의 길이를 구할 수 있다.
이때 N이 10만이기 때문에 N ^ 2 DP로 LIS를 구하는 방법은 안되고 NlogN 이분 탐색의 방법으로 LIS를 구해야 한다.
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_N 100000
using namespace std;

int a[MAX_N + 1], b[MAX_N + 1], x, n, r;
vector<int> vt;
int main() {
	// 입력을 받는 부분
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		a[x] = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}

	// vector 초기화
	vt.push_back(-MAX_N - 100);

	// dp 시도
	for (int i = 1; i <= n; i++) {
		if (vt.back() < a[b[i]]) {
			vt.push_back(a[b[i]]);
			r++;
		}
		else {
			// iterator(?)
			auto it = lower_bound(vt.begin(), vt.end(), a[b[i]]);
			*it = a[b[i]];
		}
	}

	printf("%d\n", r);
	return 0;
}

/*
#include <iostream>
#include <string.h>
using namespace std;

char input1[1001];
char input2[1001];
int c[1001][1001];
int b[1001][1001];	// N : 1, W : 2, NW : 3
int length = 0;
int sw = 0;
void LCS_length(char X[], char Y[], int m, int n);
void print_LCS(char X[], int i, int j);

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> input1;
	cin >> input2;

	int m, n;
	m = strlen(input1);
	n = strlen(input2);

	// dp배열 초기화
	for (int i = 0; i <= m; i++) {
		c[i][0] = 0;
	}

	for (int i = 0; i <= n; i++) {
		c[0][i] = 0;
	}

	// dp배열 탐색
	// LCS_length(input1, input2, m, n);

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (input1[i - 1] == input2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 3;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 1;
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 2;
			}
		}
	}
	print_LCS(input1, m, n);
	return 0;
}

// LCS-length(X,Y,m,n)
void LCS_length(char X[], char Y[], int m, int n)
{
	// dp배열 탐색
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i] == Y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 3;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 1;
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 2;
			}
		}
	}
}

void print_LCS(char X[], int i, int j) {
	if (i == 0 || j == 0) return;
	if (b[i][j] == 3) {	// NW
		length++;
		print_LCS(X, i - 1, j - 1);
		if (sw == 0) cout << length << "\n";
		sw = 1;
		cout << X[i - 1];
	}
	else if (b[i][j] == 1) { // N
		print_LCS(X, i - 1, j);
	}
	else { // b[i][j] == 2 // W
		print_LCS(X, i, j - 1);
	}
}
*/