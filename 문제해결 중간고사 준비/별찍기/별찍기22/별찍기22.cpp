#include <iostream>
using namespace std;

char **board;
void printstar(int y, int x, int size, int direction);

int N;

int main(void)
{
	cin >> N;

	if (N == 1) {
		printf("*");
		return 0;
	}

	int size = 1 + 4 * (N - 1);

	board = new char*[size + 1];
	for (int i = 0; i <= size; i++) {
		board[i] = new char[size + 1];
	}

	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++) {
			if (i == 1 || j == 1 || i == size) board[i][j] = '*';
			else board[i][j] = ' ';
		}
	}
	
	printstar(size, size, size-1, 0);

	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	return 0;
}

void printstar(int y, int x, int size, int direction) {
	// 0, 1, 2�� ���� ����, 0�� ����(�ʱ⿡�� 0�̰� �������� 1�� 2 �Դٰ�����)
	// 1�� ���� -> �Ʒ���, 2�� ������ -> ����
	if (size == 2) {
		for (int i = 1; i <= size; i++) {
			board[y][x - i] = '*';
			board[y - i][x - size] = '*';
		}
		return;
	}

	printf("size : %d\n", size);
	int next_y, next_x;

	if (direction == 1) {
		for (int i = 1; i <= size; i++) {
			board[y][x - i] = '*';
			board[y - i][x - size] = '*';
			next_y = y + size;
			next_x = x - size;
		}
	}
	else if (direction == 2) {
		for (int i = 1; i <= size; i++) {
			board[y][x+i] = '*';
			board[y+i][x+size] = '*';
			next_y = y - size;
			next_x = x + size;
		}
	}
	else {	// �� ó�� ����
		for (int i = 1; i <= size; i++) {
			board[y - i][x] = '*';
			next_y = y + size;
			next_x = x;
		}
	}

	printf("\n");
	for (int i = 1; i <= 1 + 4 * (N - 1); i++) {
		for (int j = 1; j <= 1 + 4 * (N - 1); j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	printstar(next_y, next_x, size - 2, (direction == 0 || direction == 2) ? 1 : 2);
}