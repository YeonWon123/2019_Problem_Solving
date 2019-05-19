/*
LCS�� ũ�⸦ ���ϴ� �����̴�.
�츮�� ���̳��� ���α׷����� �̿��Ͽ� LCS�� ���� �� �ִ�.
������ LCS4 ������ N�� 10���̱� ������ �ٸ� ����� �����غ��ƾ� �Ѵ�.
�ܼ��� N�� 10������ ���� ���� �κ� ������ ���϶�� �Ѵٸ� 
��ô ����� ������ �ǰ����� ������ ������ �� �־�����.
1~N ���� ������ �� ���� A, B���� ���� �ѹ� �� �־����ٴ� ���̴�.
�츮�� ���� A���� �Է��� ���� ��, 
�Է� ���� ���� �ε����� A[x]�� ���� ������ �����ϴ� ������� A������ ���� ���� ��, 
A[B[i]]�� LIS�� �������μ� ���� ���� �κ� ������ ���̸� ���� �� �ִ�.
�̶� N�� 10���̱� ������ N ^ 2 DP�� LIS�� ���ϴ� ����� �ȵǰ� NlogN �̺� Ž���� ������� LIS�� ���ؾ� �Ѵ�.
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_N 100000
using namespace std;

int a[MAX_N + 1], b[MAX_N + 1], x, n, r;
vector<int> vt;
int main() {
	// �Է��� �޴� �κ�
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		a[x] = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}

	// vector �ʱ�ȭ
	vt.push_back(-MAX_N - 100);

	// dp �õ�
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

	// dp�迭 �ʱ�ȭ
	for (int i = 0; i <= m; i++) {
		c[i][0] = 0;
	}

	for (int i = 0; i <= n; i++) {
		c[0][i] = 0;
	}

	// dp�迭 Ž��
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
	// dp�迭 Ž��
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