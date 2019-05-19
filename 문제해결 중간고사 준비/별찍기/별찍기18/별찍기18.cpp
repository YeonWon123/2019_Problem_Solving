#include <iostream>
using namespace std;

char **board;
void printstar(int N, int start_y, int start_x);

int main(void)
{
	int N;
	cin >> N;

	if (N == 1) {
		printf("*");
		return 0;
	}
	else if (N == 2) {
		printf("*****\n");
		printf(" ***\n");
		printf("  *");
		return 0;
	}

	int y = 3;
	for (int i = 3; i <= N; i++) {
		y = y * 2 + 1;
	//	printf("y : %d\n", y);
	}

	int x = 5;
	for (int i = 3; i <= N; i++) {
		x = x * 2 + 3;
	//	printf("y : %d\n", y);
	}
	x = x + 1;

	board = new char*[y];
	for (int i = 0; i <= y; i++) {
		board[i] = new char[x];
	}

	for (int i = 0; i <= y; i++) {
		for (int j = 0; j <= x; j++) {
			board[i][j] = ' ';
		}
	}

	// ¦���� �������� y��ǥ�� �� ��(y)�� �ְ�, Ȧ���� �������� �� ��(1)�� �ִ�.
	// �������� x��ǥ�� �׻� x/2�̴�.
	printstar(N, (((N % 2) == 0) ? y : 1), x / 2);

	// Ȧ���̸�, �� �� ������ ������� �ʴ´�.
	if (N % 2 != 0) {
		for (int i = 1; i <= y; i++) {
			for (int j = 1; j < x / 2 + i; j++)		// ����! �� �� ������ ������� ����!
				printf("%c", board[i][j]);

			printf("\n");
		}
	}
	else {
		// ¦���϶��� ��������������, Ȧ���� ���� ������ �ݴ��̴�.
		for (int i = 1; i <= y; i++) {
			for (int j = 1; j < x + 1 - i; j++)		// ����! �� �� ������ ������� ����!
				printf("%c", board[i][j]);

			printf("\n");
		}
	}
	return 0;
}

void printstar(int N, int start_y, int start_x) {

	//printf("N : %d, start_y : %d, start_x : %d\n", N, start_y, start_x);

	int y = 3;
	for (int i = 3; i <= N; i++) {
		y = y * 2 + 1;
	//	printf("y : %d\n", y);
	}
	y = y + 1;

	if (N == 2) {
		board[start_y - 2][start_x + 2] = '*';
		board[start_y - 2][start_x + 1] = '*';
		board[start_y - 2][start_x] = '*';
		board[start_y - 2][start_x - 1] = '*';
		board[start_y - 2][start_x - 2] = '*';
		board[start_y - 1][start_x + 1] = '*';
		board[start_y - 1][start_x] = '*';
		board[start_y - 1][start_x - 1] = '*';
		board[start_y][start_x] = '*';
		return;
	}

	// ¦���� ���
	if (N % 2 == 0) {
		board[start_y][start_x] = '*';
		for (int i = 1; i < y-1; i++) {
			board[start_y - i][start_x - i] = '*';
			board[start_y - i][start_x + i] = '*';
		}
		// ���������� ���� ä���.
		board[start_y - y+2][start_x] = '*';
		for (int i = 1; i < y; i++) {
			board[start_y - y+2][start_x - i] = '*';
			board[start_y - y+2][start_x + i] = '*';
		}
	}
	else { // Ȧ���� ���
		board[start_y][start_x] = '*';
		for (int i = 1; i < y-1; i++) {
			board[start_y + i][start_x - i] = '*';
			board[start_y + i][start_x + i] = '*';
		}
		// ���������� ���� ä���.
		board[start_y + y-2][start_x] = '*';
		for (int i = 1; i < y; i++) {
			board[start_y + y-2][start_x - i] = '*';
			board[start_y + y-2][start_x + i] = '*';
		}
	}
	//printf("y : %d\n", y);
	printstar(N - 1, (((N - 1) % 2 == 0) ? start_y - 1 + y-2 : start_y - y + 3), start_x);
}