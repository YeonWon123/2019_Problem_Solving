#include <iostream>
#include <queue>
using namespace std;

char **board;
void printstar(int row_start, int row_end, int column_start, int column_end);
void divide(int row_start, int row_end, int column_start, int column_end);

int main()
{
	int N;
	cin >> N;

	board = new char*[N];
	for (int i = 0; i < N; i++)
		board[i] = new char[2 * N - 1];

	for (int i = 0; i < N ; i++)
		for (int j = 0; j < 2 * N - 1; j++)
			board[i][j] = '-';
	
	printstar(0, 2*N-2, 0, N-1);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 2 * N - 1; j++)
			cout << board[i][j];

		if (i == N) break;
		cout << "\n";
	}

	return 0;
}

void printstar(int row_start, int row_end, int column_start, int column_end)
{
	int N = (row_start + row_end)/2;
	board[N][column_start] = '*';

	board[N - 1][column_start + 1] = '*';
	board[N + 1][column_start + 1] = '*';

	board[N - 2][column_start + 2] = '*';
	board[N - 1][column_start + 2] = '*';
	board[N][column_start + 2] = '*';
	board[N + 1][column_start + 2] = '*';
	board[N + 2][column_start + 2] = '*';
}

void divide(int row_start, int row_end, int column_start, int column_end)
{
	if (row_end - row_start + 1 == 3) // 높이가 3일 경우
		// 삼각형을 그린다. 단 저 사각형 좌표에 맞게
		printstar(row_start, row_end, column_start, column_end);
	else
	{
		// 재귀 호출
		divide(row_start, (row_start + row_end) / 2, (column_start + column_end + 2) / 4, (3 * (column_start + column_end) - 2) / 4);
		divide((row_start + row_end) / 2 + 1, row_end, column_start, (column_start + column_end) / 2 - 1);
		divide((row_start + row_end)/2 + 1, row_end, (column_start + column_end)/2 + 1, column_end);
	}
}