#include <iostream>
using namespace std;

/*
1 : *

3 : ***
    * *
    ***

9 : *********
    * ** ** *
	*********
	***   ***
	* *   * *
	***   ***
    *********
	* ** ** *
	*********
 **/

char **board;
void printstar(int end_x, int end_y, int length);

int main(void)
{
	int N;
	cin >> N;

	board = new char*[N+1];
	for (int i = 0; i <= N; i++) {
		board[i] = new char[N+1];
	}

	// 보드판 초기화
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			board[i][j] = ' ';
		}
	}

	if (N == 1) {
		printf("*"); 
		return 0;
	}

	if (N == 3) {
		printf("***\n");
		printf("* *\n");
		printf("***");
		return 0;
	}

	printstar(N, N, N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%c", board[i][j]);

		printf("\n");
	}
	return 0;
}

void printstar(int end_x, int end_y, int length) {
	if (length == 3) {
		board[end_x][end_y] = '*';
		board[end_x][end_y - 1] = '*';
		board[end_x][end_y - 2] = '*';
		board[end_x - 1][end_y] = '*';
		board[end_x - 1][end_y - 1] = ' ';
		board[end_x - 1][end_y - 2] = '*';
		board[end_x - 2][end_y] = '*';
		board[end_x - 2][end_y - 1] = '*';
		board[end_x - 2][end_y - 2] = '*';
		return;
	}
	
	// 9등분해서, 가운데를 제외한 나머지 구간을 재귀호출
	int length3 = length / 3;
	printstar(end_x, end_y, length3);
	printstar(end_x, end_y - length3, length3);
	printstar(end_x, end_y - length3 * 2, length3);
	printstar(end_x - length3, end_y, length3);
	printstar(end_x - length3, end_y - length3 * 2, length3);
	printstar(end_x - length3 * 2, end_y, length3);
	printstar(end_x - length3 * 2, end_y - length3, length3);
	printstar(end_x - length3 * 2, end_y - length3 * 2, length3);
}