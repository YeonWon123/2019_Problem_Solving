#include <iostream>
using namespace std;

void star(int N, int row);

char **board;

int main()
{
	int N;
	cin >> N;

	board = new char*[N + 1];
	for (int i = 0; i < N + 1; i++)
		board[i] = new char[2 * N + 1];

	for (int i = 0; i < N + 1; i++)
		for (int j = 0; j < 2 * N + 1; j++)
			board[i][j] = ' ';



	return 0;
}

void star(int N, int row)
{
	board[row][N] = '*';

	board[row + 1][N - 1] = '*';
	board[row + 1][N + 1] = '*';

	board[row + 2][N - 2] = '*';
	board[row + 2][N - 1] = '*';
	board[row + 2][N] = '*';
	board[row + 2][N + 1] = '*';
	board[row + 2][N + 2] = '*';
}