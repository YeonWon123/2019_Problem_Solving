#include <iostream>
#include <queue>
using namespace std;

char **board;

// y : 세로, x : 가로
int red_y, red_x;	// 빨간 구슬의 위치
int blue_y, blue_x;	// 파란 구슬의 위치
int o_y, o_x;		// 구멍의 위치

int main()
{
	int N, M;
	cin >> N >> M;

	board = new char*[N];
	for (int i = 0; i < N; i++)
		board[i] = new char[M];
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			switch (board[i][j])
			{
			case 'O':
				o_y = i; o_x = j; break;
			case 'R':
				red_y = i; red_x = j; break;
			case 'B':
				blue_y = i; blue_x = j; break;
			default:
				break;
			}
		}

	int true_end, bad_end, move;
	true_end = 0; // 빨간 공이 구멍에 들어갔을 경우
	bad_end = 0;  // 파란 공이 구멍에 들어갔을 경우
	move = 0;	  // 이동 횟수

	

	return 0;
}


void red_move(int &move, int &true_end, int &bad_end, int &i, int &j)
{
	int movesw = 0;
	int block = 0; // 막힌 경우 1로 표시
	int RB = 0; // R과 B가 붙어 있는 경우 1로 표시

	int direction = 0;

	switch (i)
	{
	case 0: // leftmove or rightmove
		switch (j)
		{
		case -1: // leftmove
			direction = 1;
			break;
		case 1: // rightmove
			direction = 2;
			break;
		}
		break;
	case -1: // upmove
		direction = 3;
		break;
	case 1: // downmove
		direction = 4;
		break;
	default:
		cout << "오류!";
		exit(0);
	}

	// 빨간 공 기준
	do
	{
		switch (board[red_y + i][red_x + j])
		{
		case 'O':
			true_end = 1; break;
		case 'B':
			RB = 1; block = 1; break;
		case '#':
			block = 1; break;
		default:
			switch (direction)
			{
			case 1:
				j--; break;
			case 2:
				j++; break;
			case 3:
				i--; break;
			case 4:
				i++; break;
			}
			break;
		}
	} while (true_end != 1 || block != 1);

	// 이동했는지 막혀서 이동을 안했는지 확인
	switch (i)
	{
	case 0: // leftmove or rightmove
		switch (j)
		{
		case -1: // leftmove
			break;
		case 1: // rightmove
			break;
		}
		break;
	case -1: // upmove
		break;
	case 1: // downmove
		break;
	default:
		move++;
		movesw++;
		break;
	}

	// 이동했으면 보드판 수정
	if (movesw != 0)
	{
		board[red_y][red_x] = '.';
		board[red_y + i][red_x + j] = 'R';
	}

	return;
}

void blue_move(int &true_end, int &bad_end, int &i, int &j)
{
	int movesw = 0;

	int block = 0; // 막힌 경우 1로 표시
	int RB = 0; // R과 B가 붙어 있는 경우 1로 표시

	int direction = 0;

	switch (i)
	{
	case 0: // leftmove or rightmove
		switch (j)
		{
		case -1: // leftmove
			direction = 1;
			break;
		case 1: // rightmove
			direction = 2;
			break;
		}
		break;
	case -1: // upmove
		direction = 3;
		break;
	case 1: // downmove
		direction = 4;
		break;
	default:
		cout << "오류!";
		exit(0);
	}

	// 파란 공 기준
	do
	{
		switch (board[blue_y + i][blue_x + j])
		{
		case 'O':
			bad_end = 1; break;
		case 'R':
			RB = 1; block = 1; break;
		case '#':
			block = 1; break;
		default:
			switch (direction)
			{
			case 1:
				j--; break;
			case 2:
				j++; break;
			case 3:
				i--; break;
			case 4:
				i++; break;
			}
			break;
		}
	} while (bad_end != 1 || block != 1);

	// 이동했는지 막혀서 이동을 안했는지 확인
	switch (i)
	{
	case 0: // leftmove or rightmove
		switch (j)
		{
		case -1: // leftmove
			break;
		case 1: // rightmove
			break;
		}
		break;
	case -1: // upmove
		break;
	case 1: // downmove
		break;
	default:
		movesw++;
		break;
	}

	if (movesw != 0)
	{
		board[blue_y][blue_x] = '.';
		board[blue_y + i][blue_x + j] = 'B';
	}

	return;
}

void leftmove(int &move, int &true_end, int &bad_end)
{
	int i = 0; int j = -1;
	red_move(move, true_end, bad_end, i, j);
	i = 0; j = -1;
	blue_move(true_end, bad_end, i, j);
	i = 0; j = -1;
	red_move(move, true_end, bad_end, i, j);
}

void rightmove(int &move, int &true_end, int &bad_end)
{
	int i = 0; int j = 1;
	red_move(move, true_end, bad_end, i, j);
	i = 0; j = 1;
	blue_move(true_end, bad_end, i, j);
	i = 0; j = 1;
	red_move(move, true_end, bad_end, i, j);
}

void upmove(int &move, int &true_end, int &bad_end)
{
	int i = -1; int j = 0;
	red_move(move, true_end, bad_end, i, j);
	i = -1; j = 0;
	blue_move(true_end, bad_end, i, j);
	i = -1; j = 0;
	red_move(move, true_end, bad_end, i, j);
}

void downmove(int &move, int &true_end, int &bad_end)
{
	int i = 1; int j = 0;
	red_move(move, true_end, bad_end, i, j);
	i = 1; j = 0;
	blue_move(true_end, bad_end, i, j);
	i = 1; j = 0;
	red_move(move, true_end, bad_end, i, j);
}


