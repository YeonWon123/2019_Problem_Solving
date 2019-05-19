#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG

char in_c[1501][1501]; // A Ȥ�� B �Է�
int in_num[1501][1501];  // ���� �Է�
int max_sum_a[1501][1501];	// ����� �κ��� (�� ���������� �ε����� 1�� ������ ����)
int max_sum_b[1501][1501];	// �ٳ����� �κ��� (�� ���������� �ε����� 1�� ������ ����)
int dp[1501][1501];

int main(void)
{
	// �Է¹ޱ�
	int R, C;
	cin >> R >> C;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> in_c[i][j];
			cin >> in_num[i][j];
		}
	}

	// �ະ�� ����� �κ��� ���ϱ�, ��, ������ 1�� ���� �Ѵ�.
	for (int i = 1; i <= R; i++) {
		for (int j = C; j > 0; j--) {
			if (in_c[i][j] == 'A') {
				if (j == C)	max_sum_a[i][j] = in_num[i][j];
				else max_sum_a[i][j] = max_sum_a[i][j + 1] + in_num[i][j];
			}
			else {
				if (j == C) max_sum_a[i][j] = 0;
				else max_sum_a[i][j] = max_sum_a[i][j + 1];
			}
		}
	}
	
	// ������ �ٳ����� �κ��� ���ϱ�, ��, ������ 1�� ���� �Ѵ�.
	for (int j = 1; j <= C; j++) {
		for (int i = R; i > 0; i--) {
			if (in_c[i][j] == 'B') {
				if (j == R)	max_sum_b[i][j] = in_num[i][j];
				else max_sum_b[i][j] = max_sum_b[i+1][j] + in_num[i][j];
			}
			else {
				if (i == R) max_sum_b[i][j] = 0;
				else max_sum_b[i][j] = max_sum_b[i+1][j];
			}
		}
	}

#ifdef DEBUG

	cout << "\n\nmax_sum_a\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << max_sum_a[i][j] << " ";
		}
		cout << "\n";
	}


	cout << "\n\nmax_sum_b\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << max_sum_b[i][j] << " ";
		}
		cout << "\n";
	}

#endif

	// dp �迭 �ʱ�ȭ
	for (int i = 0; i <= R; i++) {
		for (int j = 0; j <= C; j++) {
			dp[i][j] = -1;
		}
	}
	
	// dp[i][j] : (1,1)���� (i,j)���� �ҵ����� �̵��� ��,
	//			  ����� �ٳ����� ���� �ִ� ��
	
	// dp�迭 �ʱⰪ ����
	// dp[1][1] = max_sum_a[1][1] + max_sum_a[2][1] + max_sum_a[3][1] + ...
	//			+ max_sum_b[1][1] + max_sum_b[1][1] + ...
	//			- max_sum_a[1][1] - max_sum_b[1][1]
	
	dp[1][1] = 0;
	for (int i = 2; i <= R; i++) {
		dp[1][1] += max_sum_a[i][1];
	}
	
	for (int i = 2; i <= C; i++) {
		dp[1][1] += max_sum_b[1][i];
	}

	cout << "\ndp[1][1]=" << dp[1][1] << "\n";

	// dp[i][j]�� ����, ���� 3���� ��찡 �ִ�.
	// �ҵ����� ������ �������� ���, ���ʿ��� ���� ���, �밢������ ���� ���
	// �� �� ��� �� ����� �ٳ����� ���� �� ũ�� �Ǵ� ���� ���Ѵ�.
	// index�� 1�� ���� Ư���� ����̹Ƿ� �� ���� �� �鸸 ���� �ȴ�.

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (i == 1 && j == 1) continue;
			if (i == 1) {
				// i == 1�� ���, �ٳ����� ������ �ش�. ���� �� �� �ٳ����� �ϴ� ���ش�.
				dp[1][j] = dp[1][j - 1] - in_num[1][j];
			}
			else if (j == 1) {
				// j == 1�� ���, ����� ������ �ش�. ���� �� �� ����� ��� ���ش�.
				dp[i][1] = dp[i - 1][1] - in_num[i][1];
			}
			else {
				// �Ϲ����� ��� ���
				dp[i][j] = max(dp[i - 1][j - 1] - max_sum_a[i][j] - max_sum_b[i][j], max(dp[i][j - 1] - max_sum_a[i][j], dp[i - 1][j] - max_sum_b[i][j]));
			}
		}
	}
	
#ifdef DEBUG
	cout << "\n\ndp\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << dp[i][j] << " ";
		}
		cout << "\n";
	}

#endif
	/*
	// �ҵ����� ������ �������� ���, ����� ������ �ش�. ���� �� �� ����� ���Ѵ�.
	dp[i][j] = dp[i][j - 1] - max_sum_a[i][j];

	// �ҵ����� ���ʿ��� ���� ���, �ٳ����� ������ �ش�. ���� �� �� �ٳ����� ���Ѵ�.
	dp[i][j] = dp[i - 1][j] - max_sum_b[i][j];

	// �ҵ����� �밢������ ���� ���, ����� �ٳ��� ��ο� ������ �ֹǷ�, �� ���� ��� ���Ѵ�.
	dp[i][j] = dp[i - 1][j - 1] - max_sum_a[i][j] - max_sum_b[i][j];
	*/
	// ���������� ���� ���
	// ���� ĭ�� ���� �ش��ϴ� �ٳ����� �κ����� ���Ѵ�. 
	
	
	// �밢������ ���� ���
	// ���� ĭ�� ��, ���� �ش��ϴ� ����� �ٳ����� �κ����� ���Ѵ�.
	
	
	// �Ʒ��� ���� ���
	// ���� ĭ�� �࿡ �ش��ϴ� ����� �κ����� ���Ѵ�.

	// ��� ���
	cout << dp[R][C];
	return 0;
}