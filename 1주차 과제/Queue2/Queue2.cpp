#include <iostream>
#include <queue>
using namespace std;

char **board;

// y : ����, x : ����
int red_y, red_x;	// ���� ������ ��ġ
int blue_y, blue_x;	// �Ķ� ������ ��ġ
int o_y, o_x;		// ������ ��ġ

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
	true_end = 0; // ���� ���� ���ۿ� ���� ���
	bad_end = 0;  // �Ķ� ���� ���ۿ� ���� ���
	move = 0;	  // �̵� Ƚ��

	

	return 0;
}


void red_move(int &move, int &true_end, int &bad_end, int &i, int &j)
{
	int movesw = 0;
	int block = 0; // ���� ��� 1�� ǥ��
	int RB = 0; // R�� B�� �پ� �ִ� ��� 1�� ǥ��

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
		cout << "����!";
		exit(0);
	}

	// ���� �� ����
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

	// �̵��ߴ��� ������ �̵��� ���ߴ��� Ȯ��
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

	// �̵������� ������ ����
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

	int block = 0; // ���� ��� 1�� ǥ��
	int RB = 0; // R�� B�� �پ� �ִ� ��� 1�� ǥ��

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
		cout << "����!";
		exit(0);
	}

	// �Ķ� �� ����
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

	// �̵��ߴ��� ������ �̵��� ���ߴ��� Ȯ��
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


