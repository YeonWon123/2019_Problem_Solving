#include <iostream>
#include <queue>
using namespace std;

// 보드판
char **board;

// 좌표를 입력받을 수 있는 클래스(구조체)
class Point {
public:
	int red_y;
	int red_x;
	int blue_y;
	int blue_x;
	int direction; // 0 : 처음 또는 bfs에서 동일한 깊이에 있는 끝 노드를 나타냄
				   // 1 : 왼쪽, 2 : 오른쪽, 3 : 위, 4 : 아래
};

// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 벡터
// 전역 변수로 지정하여 함수 호출 시 매개 변수로 지정하지 않아도 되게끔 설정
vector<Point> store;

// 구슬의 이동 횟수
int moves = 1;

// 함수 원형
void leftmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end);
void rightmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end);
void upmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end);
void downmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end);
void ending(int &true_end, int &bad_end);

int main()
{
	int N, M;
	cin >> N >> M;

	board = new char*[N];
	for (int i = 0; i < N; i++)
		board[i] = new char[M];

	// y : 세로, x : 가로
	int red_y, red_x;	// 빨간 구슬의 위치
	int blue_y, blue_x;	// 파란 구슬의 위치
	int o_y, o_x;		// 구멍의 위치

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

	// 너비 우선 탐색(BFS) 이용

	// 두 구슬이 멈췄던 좌표 중 아직 탐색하지 않은 좌표를 보관하는 큐
	queue<Point> RB_point;
	RB_point.push({ red_y, red_x, blue_y, blue_x, 0 });	 // 빨간 구슬의 시작 좌표를 저장

	int true_end, bad_end;
	true_end = 0; // 빨간 공이 구멍에 들어갔을 경우
	bad_end = 0;  // 파란 공이 구멍에 들어갔을 경우

	while (!RB_point.empty() && moves < 11) {
		Point RB_now = RB_point.front();	// 시작 좌표를 이전에 멈췄던 좌표 리스트에 포함
		RB_point.pop();

		// 왼쪽, 오른쪽, 위, 아래 네 방향에 대해 모두 검사한다.
		// 단, 이전에 방문한 방향은 다시 검사하지 않는다. (왼쪽 -> 왼쪽 X)
		// 이동 불가하거나, 이동했을 때 이전에 멈췄던 좌표이면 그 좌표는 새로 추가하지 않는다.
		// 만약 구슬이 구멍에 들어갔을 경우 움직인 횟수를 출력하고 종료한다. (ending 함수에서 이루어짐)
		if (RB_now.direction != 1 && RB_now.red_x != -1)
		{
			leftmove(RB_now, RB_point, true_end, bad_end);
			ending(true_end, bad_end);
		}
		if (RB_now.direction != 2 && RB_now.red_x != -1)
		{
			rightmove(RB_now, RB_point, true_end, bad_end);
			ending(true_end, bad_end);
		}
		if (RB_now.direction != 3 && RB_now.red_x != -1)
		{
			upmove(RB_now, RB_point, true_end, bad_end);
			ending(true_end, bad_end);
		}
		if (RB_now.direction != 4 && RB_now.red_x != -1)
		{
			downmove(RB_now, RB_point, true_end, bad_end);
			ending(true_end, bad_end);
		}

		// 0은 처음 또는 bfs에서 동일한 깊이(depth)에 있는 끝 노드를 나타냄
		// 따라서 direction이 0일 경우 bfs에서 이 깊이(depth)의 마지막임을 표시하기 위한 노드를 추가함
		if (RB_now.direction == 0)
		{
			RB_point.push({ -1, -1, -1, -1, 0 });
			moves++;
		}

	}
	
	// 10번 이내에 출력할 수 없는 경우
	cout << -1 << "\n";
	return 0;
}

void leftmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end)
{
	// 빨간 구슬 이동
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int block = 0;
	do
	{
		switch (board[RB_now.red_y][RB_now.red_x - i])
		{
		case 'O':
			true_end = 1; break;
		case '#':
			block = 1; i--; break;
		default:
			i++; break;
		}
	} while (true_end != 1 && block != 1);

	// 파란 구슬 이동
	int j = 1;	// 파란 구슬의 이동하는 거리
	block = 0;
	do
	{
		switch (board[RB_now.blue_y][RB_now.blue_x - j])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--;  break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	if (true_end == 1 || bad_end == 1)	return;

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 오른쪽에 있던 구슬이 우측에 있게 한다.
	if (RB_now.red_y == RB_now.blue_y)
	{
		if (RB_now.red_x - i == RB_now.blue_x - j)
		{
			if (i < j)
				j--;
			else
				i--;
		}
	}

	// 만약 빨간 구슬과 파란 구슬 모두 이동하지 않았을 경우, 함수를 종료한다.
	if (i == 0 && j == 0) return;

	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (unsigned int k = 0; k < store.size(); k++)
	{
		if ((RB_now.red_y == store[k].red_y) && ((RB_now.red_x - i) == store[k].red_x))
			if ((RB_now.blue_y == store[k].blue_y) && ((RB_now.blue_x - j) == store[k].blue_x))
				return;
	}

	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다. (왼쪽이므로 방향 1)
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 vector에도 저장한다.
	// cout << "새로 들어감 : " << RB_now.red_y << " " << RB_now.red_x - i << " 방향 1 " << endl;
	RB_point.push({ RB_now.red_y, RB_now.red_x - i, RB_now.blue_y, RB_now.blue_x - j, 1 });
	store.push_back({ RB_now.red_y, RB_now.red_x - i, RB_now.blue_y, RB_now.blue_x - j, 1 });

	// 함수 종료
	return;

}

void rightmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end)
{
	// 빨간 구슬 이동
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int block = 0;
	do
	{
		switch (board[RB_now.red_y][RB_now.red_x + i])
		{
		case 'O':
			true_end = 1; break;
		case '#':
			block = 1; i--; break;
		default:
			i++; break;
		}
	} while (true_end != 1 && block != 1);

	// 파란 구슬 이동
	int j = 1;	// 파란 구슬의 이동하는 거리
	block = 0;
	do
	{
		switch (board[RB_now.blue_y][RB_now.blue_x + j])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--;  break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	if (true_end == 1 || bad_end == 1)	return;

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 오른쪽에 있던 구슬이 우측에 있게 한다.
	if (RB_now.red_y == RB_now.blue_y)
	{
		if (RB_now.red_x + i == RB_now.blue_x + j)
		{
			if (i < j)
				j--;
			else
				i--;
		}
	}

	// 만약 빨간 구슬과 파란 구슬 모두 이동하지 않았을 경우, 함수를 종료한다.
	if (i == 0 && j == 0) return;

	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (unsigned int k = 0; k < store.size(); k++)
	{
		if ((RB_now.red_y == store[k].red_y) && ((RB_now.red_x + i) == store[k].red_x))
			if ((RB_now.blue_y == store[k].blue_y) && ((RB_now.blue_x + j) == store[k].blue_x))
				return;
	}

	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다. (오른쪽이므로 방향 2)
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 vector에도 저장한다.
	// cout << "새로 들어감 : " << RB_now.red_y << " " << RB_now.red_x + i << " 방향 2 " << endl;
	RB_point.push({ RB_now.red_y, RB_now.red_x + i, RB_now.blue_y, RB_now.blue_x + j, 2 });
	store.push_back({ RB_now.red_y, RB_now.red_x + i, RB_now.blue_y, RB_now.blue_x + j, 2 });

	// 함수 종료
	return;

}

void upmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end)
{
	// 빨간 구슬 이동
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int block = 0;
	do
	{
		switch (board[RB_now.red_y - i][RB_now.red_x])
		{
		case 'O':
			true_end = 1; break;
		case '#':
			block = 1; i--; break;
		default:
			i++; break;
		}
	} while (true_end != 1 && block != 1);

	// 파란 구슬 이동
	int j = 1;	// 파란 구슬의 이동하는 거리
	block = 0;
	do
	{
		switch (board[RB_now.blue_y - j][RB_now.blue_x])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--;  break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	if (true_end == 1 || bad_end == 1)	return;

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 오른쪽에 있던 구슬이 우측에 있게 한다.
	if (RB_now.red_y - i == RB_now.blue_y - j)
	{
		if (RB_now.red_x == RB_now.blue_x)
		{
			if (i < j)
				j--;
			else
				i--;
		}
	}

	// 만약 빨간 구슬과 파란 구슬 모두 이동하지 않았을 경우, 함수를 종료한다.
	if (i == 0 && j == 0) return;

	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (unsigned int k = 0; k < store.size(); k++)
	{
		if (((RB_now.red_y - i) == store[k].red_y) && (RB_now.red_x == store[k].red_x))
			if (((RB_now.blue_y - j) == store[k].blue_y) && (RB_now.blue_x == store[k].blue_x))
				return;
	}

	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다. (위쪽이므로 방향 3)
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 vector에도 저장한다.
	// cout << "새로 들어감 : " << RB_now.red_y - i << " " << RB_now.red_x << " 방향 3 " << endl;
	RB_point.push({ RB_now.red_y - i, RB_now.red_x, RB_now.blue_y - j, RB_now.blue_x, 3 });
	store.push_back({ RB_now.red_y - i, RB_now.red_x, RB_now.blue_y - j, RB_now.blue_x, 3 });

	// 함수 종료
	return;

}

void downmove(Point RB_now, queue<Point>& RB_point, int &true_end, int &bad_end)
{
	// 빨간 구슬 이동
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int block = 0;
	do
	{
		switch (board[RB_now.red_y + i][RB_now.red_x])
		{
		case 'O':
			true_end = 1; break;
		case '#':
			block = 1; i--; break;
		default:
			i++; break;
		}
	} while (true_end != 1 && block != 1);

	// 파란 구슬 이동
	int j = 1;	// 파란 구슬의 이동하는 거리
	block = 0;
	do
	{
		switch (board[RB_now.blue_y + j][RB_now.blue_x])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--;  break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	if (true_end == 1 || bad_end == 1)	return;

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 오른쪽에 있던 구슬이 우측에 있게 한다.
	if (RB_now.red_y + i == RB_now.blue_y + j)
	{
		if (RB_now.red_x == RB_now.blue_x)
		{
			if (i < j)
				j--;
			else
				i--;
		}
	}

	// 만약 빨간 구슬과 파란 구슬 모두 이동하지 않았을 경우, 함수를 종료한다.
	if (i == 0 && j == 0) return;

	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (unsigned int k = 0; k < store.size(); k++)
	{
		if (((RB_now.red_y + i) == store[k].red_y) && (RB_now.red_x == store[k].red_x))
			if (((RB_now.blue_y + j) == store[k].blue_y) && (RB_now.blue_x == store[k].blue_x))
				return;
	}

	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다. (아래쪽이므로 방향 4)
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 vector에도 저장한다.
	// cout << "새로 들어감 : " << RB_now.red_y + i << " " << RB_now.red_x << " 방향 3 " << endl;
	RB_point.push({ RB_now.red_y + i, RB_now.red_x, RB_now.blue_y + j, RB_now.blue_x, 4 });
	store.push_back({ RB_now.red_y + i, RB_now.red_x, RB_now.blue_y + j, RB_now.blue_x, 4 });

	// 함수 종료
	return;

}

void ending(int &true_end, int &bad_end)
{
	if (bad_end == 1)
	{
		bad_end = 0;
		true_end = 0;
		return;
	}
	else if (true_end == 1)
	{
		cout << moves << "\n";
		exit(0);
	}
	else
	{
		bad_end = 0;
		true_end = 0;
	}
}