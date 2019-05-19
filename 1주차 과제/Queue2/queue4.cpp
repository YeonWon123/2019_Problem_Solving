#include <iostream>
#include <vector>
#include <queue>
using namespace std;

char **board;

// 좌표를 입력받을 수 있는 구조체
typedef struct {
	int y, x;
} Point;

// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐
// 전역 변수로 지정하여 함수 호출 시 매개 변수로 지정하지 않아도 되게끔 설정
vector<Point> store;
vector<Point> store_blue;

int store_size_count = 1;	 // 트리 잎 개수
int moves = 0;				 // 이동 횟수

//Point tree_node_first; // 트리의 깊이마다 맨 왼쪽에 있는 좌표를 저장
//int tree_node_first_sw = 1; // 스위치(1이 있는 거, 0이 없는 거)

// 함수 원형
void ending(int &true_end, int &bad_end);
void leftmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end);
void rightmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end);
void upmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end);
void downmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end);

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

	// 빨간 구슬이 멈췄던 좌표 중 아직 탐색하지 않은 좌표를 보관하는 큐
	queue<Point> red_point, blue_point;
	red_point.push({ red_y, red_x });	 // 빨간 구슬의 시작 좌표를 저장
	blue_point.push({ blue_y, blue_x }); // 파란 구슬의 시작 좌표를 저장
	store.push_back({ red_y, red_x });	 // 빨간 구슬이 멈췄던 좌표이므로 저장
	store_blue.push_back({ blue_y, blue_x });	 // 빨간 구슬이 멈췄던 좌표이므로 저장

	//tree_node_first = { red_y, red_x };  // 트리의 깊이마다 맨 왼쪽에 있는 좌표를 저장

	int true_end, bad_end;
	true_end = 0; // 빨간 공이 구멍에 들어갔을 경우
	bad_end = 0;  // 파란 공이 구멍에 들어갔을 경우

	while (!red_point.empty() && store_size_count < 4194304) {
		Point red_now = red_point.front();	// 시작 좌표를 이전에 멈췄던 좌표 리스트에 포함
		Point blue_now = blue_point.front();
		red_point.pop();
		blue_point.pop();

		if ((store_size_count == 1))
		{
			//tree_node_first_sw = 0;
			moves++;
			cout << "move증가!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}

		cout << "(" << red_now.y << " " << red_now.x << ")" << endl;

		// 왼쪽, 오른쪽, 위, 아래 네 방향에 대해 모두 검사한다.
		// 이동 불가하거나, 이동했을 때 이전에 멈췄던 좌표이면 그 좌표는 새로 추가하지 않는다.
		// 만약 구슬이 구멍에 들어갔을 경우 움직인 횟수를 출력하고 종료한다. (ending 함수에서 이루어짐)
		leftmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
		rightmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
		upmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
		downmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
	}
	
	// 10번 이내에 출력할 수 없는 경우
	cout << -1 << "\n";
	return 0;
}

void ending(int &true_end, int &bad_end)
{
	if (bad_end == 1)
	{
		cout << "bad_end가 1이네" << "\n";
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

void leftmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int j = 1;	// 파란 구슬의 이동하는 거리
	int block = 0;
	do
	{
		switch (board[red_now.y][red_now.x - i])
		{
		case 'O':
			true_end = 1; cout << "끝!" << endl; break;
		case '#':
			block = 1; i--; cout << "막힘!" << endl; break;
		default:
			i++; cout << "계속!" << endl; break;
		}
	} while (true_end != 1 && block != 1);

	block = 0;
	do
	{
		switch (board[blue_now.y][blue_now.x - j])
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
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (true_end == 1 || bad_end == 1)
	{
		//red_point.push({ -1, -1 });
		//blue_point.push({ -1, -1 });
		//store.push_back({ -1,-1 });
		//store_blue.push_back({ -1, -1 });
		store_size_count = store_size_count + 1;
		cout << "store_size_count:" << store_size_count << endl;

		if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
			(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
			(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
			|| (store_size_count == 349462) || (store_size_count == 1398038))
		{
			//tree_node_first_sw = 0;
			moves++;
			cout << "move증가!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}
	
	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 오른쪽에 있던 구슬이 우측에 있게 한다.
	if (red_now.y == blue_now.y)
		if (red_now.x - i == blue_now.x - j)
		{
			cout << "겹침!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// 만약 빨간 구슬이 이동하지 않았을 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (i == 0)
	{
		cout << "빨간 구슬 이동 안함!" << endl;
		//! 빨간 구슬 이동 안해도, 파란 구슬이 이동하는 경우가 있으니 수정 바람!

		store.push_back({ -1,-1 });
		return;
	}
	*/
	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (int k = 0; k < store.size(); k++)
	{
		if ((red_now.y == store[k].y) && ((red_now.x - i) == store[k].x))
		{
			if ((blue_now.y == store_blue[k].y) && ((blue_now.x - j) == store_blue[k].x))
			{
				cout << "이전에 멈춘 적 있음!" << endl;

				//red_point.push({ -1, -1 });
				//blue_point.push({ -1, -1 });
				//store.push_back({ -1,-1 });
				//store_blue.push_back({ -1, -1 });
				store_size_count = store_size_count + 1;
				cout << "store_size_count:" << store_size_count << endl;

				if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
					(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
					(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
					|| (store_size_count == 349462) || (store_size_count == 1398038))
				{
					//tree_node_first_sw = 0;
					moves++;
					cout << "move증가!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	
	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다.
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐에도 저장한다.
	cout << "저장! ";
	cout << "(" << red_now.y << " " << red_now.x - i << ")" << endl;
	/*
	if (tree_node_first_sw == 0)
	{
		tree_node_first.x = red_now.x - i;
		tree_node_first.y = red_now.y;
		tree_node_first_sw = 1;
	}
	*/
	red_point.push({ red_now.y, red_now.x - i });
	blue_point.push({ blue_now.y, blue_now.x - j });
	store.push_back({ red_now.y, red_now.x - i});
	store_blue.push_back({ blue_now.y, blue_now.x - j });
	store_size_count = store_size_count + 1;
	cout << "store_size_count:" << store_size_count << endl;

	if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
		(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
		(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
		|| (store_size_count == 349462) || (store_size_count == 1398038))
	{
		//tree_node_first_sw = 0;
		moves++;
		cout << "move증가!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// 함수 종료
	return;
}


void rightmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int j = 1;	// 파란 구슬의 이동하는 거리
	int block = 0;
	do
	{
		switch (board[red_now.y][red_now.x + i])
		{
		case 'O':
			true_end = 1; cout << "끝!" << endl; break;
		case '#':
			block = 1; i--; cout << "막힘!" << endl; break;
		default:
			i++; cout << "계속!" << endl; break;
		}
	} while (true_end != 1 && block != 1);
	
	block = 0;
	do
	{
		switch (board[blue_now.y][blue_now.x + j])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--; break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (true_end == 1 || bad_end == 1)
	{
		//red_point.push({ -1, -1 });
		//blue_point.push({ -1, -1 });
		//store.push_back({ -1,-1 });
		//store_blue.push_back({ -1, -1 });
		store_size_count = store_size_count + 1;
		cout << "store_size_count:" << store_size_count << endl;

		if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
			(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
			(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
			|| (store_size_count == 349462) || (store_size_count == 1398038))
		{
			//tree_node_first_sw = 0;
			moves++;
			cout << "move증가!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 왼쪽에 있던 구슬이 좌측에 있게 한다.
	if (red_now.y == blue_now.y)
		if (red_now.x + i == blue_now.x + j)
		{
			cout << "겹침!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// 만약 빨간 구슬이 이동하지 않았을 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (i == 0)
	{
		cout << "빨간 구슬 이동 안함!" << endl;
		store.push_back({ -1,-1 });
		return;
	}
	*/
	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (int k = 0; k < store.size(); k++)
	{
		if ((red_now.y == store[k].y) && ((red_now.x + i) == store[k].x))
		{
			if ((blue_now.y == store_blue[k].y) && ((blue_now.x + j) == store_blue[k].x))
			{
				cout << "이전에 멈춘 적 있음!" << endl;
				//red_point.push({ -1, -1 });
				//blue_point.push({ -1, -1 });
				//store.push_back({ -1,-1 });
				//store_blue.push_back({ -1, -1 });
				store_size_count = store_size_count + 1;
				cout << "store_size_count:" << store_size_count << endl;

				if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
					(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
					(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
					|| (store_size_count == 349462) || (store_size_count == 1398038))
				{
					//tree_node_first_sw = 0;
					moves++;
					cout << "move증가!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다.
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐에도 저장한다.
	cout << "저장! ";
	cout << "(" << red_now.y << " " << red_now.x + i << ")" << endl;
	/*
	if (tree_node_first_sw == 0)
	{
		tree_node_first.x = red_now.x + i;
		tree_node_first.y = red_now.y;
		tree_node_first_sw = 1;
	}*/
	red_point.push({ red_now.y, red_now.x + i });
	blue_point.push({ blue_now.y, blue_now.x + j });
	store_blue.push_back({ blue_now.y, blue_now.x + j });
	store.push_back({ red_now.y, red_now.x + i});
	store_size_count = store_size_count + 1;
	cout << "store_size_count:" << store_size_count << endl;

	if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
		(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
		(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
		|| (store_size_count == 349462) || (store_size_count == 1398038))
	{
		//tree_node_first_sw = 0;
		moves++;
		cout << "move증가!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// 함수 종료
	return;
}

void upmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int j = 1;	// 파란 구슬의 이동하는 거리
	int block = 0;
	do
	{
		switch (board[red_now.y - i][red_now.x])
		{
		case 'O':
			true_end = 1; cout << "끝!" << endl; break;
		case '#':
			block = 1; i--; cout << "막힘!" << endl; break;
		default:
			i++; cout << "계속!" << endl; break;
		}
	} while (true_end != 1 && block != 1);
	block = 0;
	do
	{
		switch (board[blue_now.y - j][blue_now.x])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--; break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (true_end == 1 || bad_end == 1)
	{
		//red_point.push({ -1, -1 });
		//blue_point.push({ -1, -1 });
		//store.push_back({ -1,-1 });
		//store_blue.push_back({ -1, -1 });
		store_size_count = store_size_count + 1;
		cout << "store_size_count:" << store_size_count << endl;

		if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
			(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
			(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
			|| (store_size_count == 349462) || (store_size_count == 1398038))
		{
			//tree_node_first_sw = 0;
			moves++;
			cout << "move증가!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 아래에 있던 구슬이 아래에 있게 한다.
	if (red_now.y - i == blue_now.y - j)
		if (red_now.x == blue_now.x)
		{
			cout << "겹침!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// 만약 빨간 구슬이 이동하지 않았을 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (i == 0)
	{
		cout << "빨간 구슬 이동 안함!" << endl;
		store.push_back({ -1,-1 });
		return;
	}
	*/
	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (int k = 0; k < store.size(); k++)
	{
		if (((red_now.y - i) == store[k].y) && (red_now.x == store[k].x))
		{
			if (((blue_now.y - j) == store_blue[k].y) && (blue_now.x == store_blue[k].x))
			{
				cout << "이전에 멈춘 적 있음!" << endl;
				//red_point.push({ -1, -1 });
				//blue_point.push({ -1, -1 });
				//store.push_back({ -1,-1 });
				//store_blue.push_back({ -1, -1 });
				store_size_count = store_size_count + 1;
				cout << "store_size_count:" << store_size_count << endl;

				if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
					(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
					(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
					|| (store_size_count == 349462) || (store_size_count == 1398038))
				{
					//tree_node_first_sw = 0;
					moves++;
					cout << "move증가!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다.
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐에도 저장한다.
	cout << "저장! ";
	cout << "(" << red_now.y-i << " " << red_now.x << ")" << endl;
	/*
	if (tree_node_first_sw == 0)
	{
		tree_node_first.x = red_now.x;
		tree_node_first.y = red_now.y - i;
		tree_node_first_sw = 1;
	}*/
	red_point.push({ red_now.y - i, red_now.x });
	blue_point.push({ blue_now.y - j, blue_now.x });
	store.push_back({ red_now.y - i, red_now.x });
	store_blue.push_back({ blue_now.y - j, blue_now.x });
	store_size_count = store_size_count + 1;
	cout << "store_size_count:" << store_size_count << endl;

	if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
		(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
		(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
		|| (store_size_count == 349462) || (store_size_count == 1398038))
	{
		//tree_node_first_sw = 0;
		moves++;
		cout << "move증가!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// 함수 종료
	return;
}

void downmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// 빨간 구슬이 이동하는 거리
	int j = 1;	// 파란 구슬의 이동하는 거리
	int block = 0;
	do
	{
		switch (board[red_now.y + i][red_now.x])
		{
		case 'O':
			true_end = 1; cout << "끝!" << endl; break;
		case '#':
			block = 1; i--; cout << "막힘!" << endl; break;
		default:
			i++; cout << "계속!" << endl; break;
		}
	} while (true_end != 1 && block != 1);
	block = 0;
	do
	{
		switch (board[blue_now.y + j][blue_now.x])
		{
		case 'O':
			bad_end = 1; break;
		case '#':
			block = 1; j--; break;
		default:
			j++; break;
		}
	} while (bad_end != 1 && block != 1);

	// 만약 빨간 구슬이나 파란 구슬이 구멍에 들어간 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (true_end == 1 || bad_end == 1)
	{
		//red_point.push({ -1, -1 });
		//blue_point.push({ -1, -1 });
		//store.push_back({ -1,-1 });
		//store_blue.push_back({ -1, -1 });
		store_size_count = store_size_count + 1;
		cout << "store_size_count:" << store_size_count << endl;

		if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
			(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
			(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
			|| (store_size_count == 349462) || (store_size_count == 1398038))
		{
			//tree_node_first_sw = 0;
			moves++;
			cout << "move증가!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}

	// 그렇지 않고, 빨간 구슬과 파란 구슬의 위치가 같을 경우, 더 왼쪽에 있던 구슬이 좌측에 있게 한다.
	if (red_now.y + i == blue_now.y + j)
		if (red_now.x == blue_now.x)
		{
			cout << "겹침!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// 만약 빨간 구슬이 이동하지 않았을 경우, 함수를 종료한다.
	// 이 때 "빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐"에는 (-1,-1)을 넣는다.
	if (i == 0)
	{
		cout << "빨간 구슬 이동 안함!" << endl;
		store.push_back({ -1,-1 });
		return;
	}
	*/
	// 빨간 구슬이 멈춘 좌표와 파란 구슬이 멈춘 좌표가 이전에 멈춘 적이 있는지 조사한다.
	// 이동하지 않았을 경우는 store 큐에서 맨 마지막에 있는 좌표와 똑같으므로 함수를 종료한다.
	for (int k = 0; k < store.size(); k++)
	{
		if (((red_now.y + i) == store[k].y) && (red_now.x == store[k].x))
		{
			if (((blue_now.y + j) == store_blue[k].y) && (blue_now.x == store_blue[k].x))
			{
				cout << "이전에 멈춘 적 있음!" << endl;
				//red_point.push({ -1, -1 });
				//blue_point.push({ -1, -1 });
				//store.push_back({ -1,-1 });
				//store_blue.push_back({ -1, -1 });
				store_size_count = store_size_count + 1;
				cout << "store_size_count:" << store_size_count << endl;
				if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
					(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
					(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
					|| (store_size_count == 349462) || (store_size_count == 1398038))
				{
					//tree_node_first_sw = 0;
					moves++;
					cout << "move증가!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	// 그렇지 않다면, 두 구슬이 멈춘 좌표를, 아직 탐색하지 않은 좌표를 보관하는 큐에 저장한다.
	// 빨간 구슬이 이전에 멈췄던 좌표를 저장하는 큐에도 저장한다.
	cout << "저장! ";
	cout << "(" << red_now.y + i << " " << red_now.x << ")" << endl;
	/*
	if (tree_node_first_sw == 0)
	{
		tree_node_first.x = red_now.x;
		tree_node_first.y = red_now.y + i;
		tree_node_first_sw = 1;
	} */
	red_point.push({ red_now.y + i, red_now.x });
	blue_point.push({ blue_now.y + j, blue_now.x });
	store.push_back({ red_now.y + i, red_now.x });
	store_blue.push_back({ blue_now.y + j, blue_now.x });
	store_size_count = store_size_count + 1;
	cout << "store_size_count:" << store_size_count << endl;

	if ((store_size_count == 1) || (store_size_count == 2) || (store_size_count == 6) ||
		(store_size_count == 22) || (store_size_count == 278) || (store_size_count == 1302) ||
		(store_size_count == 5398) || (store_size_count == 21782) || (store_size_count == 87318)
		|| (store_size_count == 349462) || (store_size_count == 1398038))
	{
		//tree_node_first_sw = 0;
		moves++;
		cout << "move증가!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// 함수 종료
	return;
}