#include <iostream>
using namespace std;

char **board;
void divide(int col_start, int col_end, int row_start, int row_end);
void starprint(int col_start, int col_end, int row_start, int row_end);

int main()
{
	int N;
	cin >> N;

	board = new char*[N+1];
	for (int i = 0; i < N+1; i++)
		board[i] = new char[2*N];

	for (int i = 0; i < N + 1; i++)
		for (int j = 0; j < 2 * N; j++)
			board[i][j] = ' ';

	// 1~N, 1~2N-1의 사각형이 초기값이라고 생각하고 이를 초기 인자로 집어넣는다.
	divide(1, N, 1, 2 * N - 1);

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < 2 * N; j++)
			cout << board[i][j];
		if (i == N) break;
		cout << "\n";
	}
	return 0;
}

// 재귀호출 함수, 인자로 시작 열 번호, 끝 열 번호, 시작 행 번호, 끝 행 번호를 받음
void divide(int col_start, int col_end, int row_start, int row_end)
{
	// 사각형의 높이가 3일 경우, 별을 찍는다.
	if (col_end - col_start + 1 == 3) starprint(col_start,col_end,row_start,row_end);
	else
	{
		// 아닐 경우 3개의 사각형으로 나눈다. 이를 재귀함수로 처리한다.
		divide(col_start, (col_start + col_end) / 2, row_start + (row_end - row_start + 2) / 4, row_end - (row_end - row_start + 2) / 4);
		divide((col_start + col_end) / 2 + 1, col_end, row_start, (row_start + row_end) / 2 - 1);
		divide((col_start + col_end) / 2 + 1, col_end, (row_start + row_end) / 2 + 1, row_end);
	}
}

// 3*5 사각형에 별을 찍는 함수
// 인자로 시작 열 번호, 끝 열 번호, 시작 행 번호, 끝 행 번호를 받음
void starprint(int col_start, int col_end, int row_start, int row_end)
{
	board[col_start][row_start + 2] = '*';
	board[col_start + 1][row_start + 1] = '*';
	board[col_start + 1][row_end - 1] = '*';
	board[col_start + 2][row_start] = '*';
	board[col_start + 2][row_start + 1] = '*';
	board[col_start + 2][row_start + 2] = '*';
	board[col_start + 2][row_end - 1] = '*';
	board[col_start + 2][row_end] = '*';
}