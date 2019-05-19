#include <iostream>
using namespace std;

char **board;
void printstar(int xy, int size);

int main(void)
{
	int N;
	cin >> N;
	
	if (N == 1) {
		printf("*");
		return 0;
	}

	int size = 1 + 4 * (N - 1);

	board = new char*[size+1];
	for (int i = 0; i <= size; i++) {
		board[i] = new char[size+1];
	}

	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++) {
			if (i == 1 || j == 1 || i == size || j == size) board[i][j] = '*';
			else board[i][j] = ' ';
		}
	}

	printstar(3, size - 4);

	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	return 0;
}

void printstar(int xy, int size) {
	if (size == 1) {
		board[xy][xy] = '*';
		return;
	}

	for (int i = xy; i < xy+size; i++) {
		board[i][xy] = '*';
		board[xy][i] = '*';
		board[i][xy + size-1] = '*';
		board[xy + size-1][i] = '*';
	}
	printstar(xy + 2, size - 4);
}