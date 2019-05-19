#include <iostream>
#include <vector>
#include <queue>
using namespace std;

char **board;

// ��ǥ�� �Է¹��� �� �ִ� ����ü
typedef struct {
	int y, x;
} Point;

// ���� ������ ������ ����� ��ǥ�� �����ϴ� ť
// ���� ������ �����Ͽ� �Լ� ȣ�� �� �Ű� ������ �������� �ʾƵ� �ǰԲ� ����
vector<Point> store;
vector<Point> store_blue;

int store_size_count = 1;	 // Ʈ�� �� ����
int moves = 0;				 // �̵� Ƚ��

//Point tree_node_first; // Ʈ���� ���̸��� �� ���ʿ� �ִ� ��ǥ�� ����
//int tree_node_first_sw = 1; // ����ġ(1�� �ִ� ��, 0�� ���� ��)

// �Լ� ����
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

	// y : ����, x : ����
	int red_y, red_x;	// ���� ������ ��ġ
	int blue_y, blue_x;	// �Ķ� ������ ��ġ
	int o_y, o_x;		// ������ ��ġ

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
	
	// �ʺ� �켱 Ž��(BFS) �̿�

	// ���� ������ ����� ��ǥ �� ���� Ž������ ���� ��ǥ�� �����ϴ� ť
	queue<Point> red_point, blue_point;
	red_point.push({ red_y, red_x });	 // ���� ������ ���� ��ǥ�� ����
	blue_point.push({ blue_y, blue_x }); // �Ķ� ������ ���� ��ǥ�� ����
	store.push_back({ red_y, red_x });	 // ���� ������ ����� ��ǥ�̹Ƿ� ����
	store_blue.push_back({ blue_y, blue_x });	 // ���� ������ ����� ��ǥ�̹Ƿ� ����

	//tree_node_first = { red_y, red_x };  // Ʈ���� ���̸��� �� ���ʿ� �ִ� ��ǥ�� ����

	int true_end, bad_end;
	true_end = 0; // ���� ���� ���ۿ� ���� ���
	bad_end = 0;  // �Ķ� ���� ���ۿ� ���� ���

	while (!red_point.empty() && store_size_count < 4194304) {
		Point red_now = red_point.front();	// ���� ��ǥ�� ������ ����� ��ǥ ����Ʈ�� ����
		Point blue_now = blue_point.front();
		red_point.pop();
		blue_point.pop();

		if ((store_size_count == 1))
		{
			//tree_node_first_sw = 0;
			moves++;
			cout << "move����!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}

		cout << "(" << red_now.y << " " << red_now.x << ")" << endl;

		// ����, ������, ��, �Ʒ� �� ���⿡ ���� ��� �˻��Ѵ�.
		// �̵� �Ұ��ϰų�, �̵����� �� ������ ����� ��ǥ�̸� �� ��ǥ�� ���� �߰����� �ʴ´�.
		// ���� ������ ���ۿ� ���� ��� ������ Ƚ���� ����ϰ� �����Ѵ�. (ending �Լ����� �̷����)
		leftmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
		rightmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
		upmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
		downmove(red_now, blue_now, red_point, blue_point, true_end, bad_end);
		ending(true_end, bad_end);
	}
	
	// 10�� �̳��� ����� �� ���� ���
	cout << -1 << "\n";
	return 0;
}

void ending(int &true_end, int &bad_end)
{
	if (bad_end == 1)
	{
		cout << "bad_end�� 1�̳�" << "\n";
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
	int i = 1;	// ���� ������ �̵��ϴ� �Ÿ�
	int j = 1;	// �Ķ� ������ �̵��ϴ� �Ÿ�
	int block = 0;
	do
	{
		switch (board[red_now.y][red_now.x - i])
		{
		case 'O':
			true_end = 1; cout << "��!" << endl; break;
		case '#':
			block = 1; i--; cout << "����!" << endl; break;
		default:
			i++; cout << "���!" << endl; break;
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


	// ���� ���� �����̳� �Ķ� ������ ���ۿ� �� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
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
			cout << "move����!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}
	
	// �׷��� �ʰ�, ���� ������ �Ķ� ������ ��ġ�� ���� ���, �� �����ʿ� �ִ� ������ ������ �ְ� �Ѵ�.
	if (red_now.y == blue_now.y)
		if (red_now.x - i == blue_now.x - j)
		{
			cout << "��ħ!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// ���� ���� ������ �̵����� �ʾ��� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
	if (i == 0)
	{
		cout << "���� ���� �̵� ����!" << endl;
		//! ���� ���� �̵� ���ص�, �Ķ� ������ �̵��ϴ� ��찡 ������ ���� �ٶ�!

		store.push_back({ -1,-1 });
		return;
	}
	*/
	// ���� ������ ���� ��ǥ�� �Ķ� ������ ���� ��ǥ�� ������ ���� ���� �ִ��� �����Ѵ�.
	// �̵����� �ʾ��� ���� store ť���� �� �������� �ִ� ��ǥ�� �Ȱ����Ƿ� �Լ��� �����Ѵ�.
	for (int k = 0; k < store.size(); k++)
	{
		if ((red_now.y == store[k].y) && ((red_now.x - i) == store[k].x))
		{
			if ((blue_now.y == store_blue[k].y) && ((blue_now.x - j) == store_blue[k].x))
			{
				cout << "������ ���� �� ����!" << endl;

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
					cout << "move����!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	
	// �׷��� �ʴٸ�, �� ������ ���� ��ǥ��, ���� Ž������ ���� ��ǥ�� �����ϴ� ť�� �����Ѵ�.
	// ���� ������ ������ ����� ��ǥ�� �����ϴ� ť���� �����Ѵ�.
	cout << "����! ";
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
		cout << "move����!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// �Լ� ����
	return;
}


void rightmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// ���� ������ �̵��ϴ� �Ÿ�
	int j = 1;	// �Ķ� ������ �̵��ϴ� �Ÿ�
	int block = 0;
	do
	{
		switch (board[red_now.y][red_now.x + i])
		{
		case 'O':
			true_end = 1; cout << "��!" << endl; break;
		case '#':
			block = 1; i--; cout << "����!" << endl; break;
		default:
			i++; cout << "���!" << endl; break;
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

	// ���� ���� �����̳� �Ķ� ������ ���ۿ� �� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
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
			cout << "move����!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}

	// �׷��� �ʰ�, ���� ������ �Ķ� ������ ��ġ�� ���� ���, �� ���ʿ� �ִ� ������ ������ �ְ� �Ѵ�.
	if (red_now.y == blue_now.y)
		if (red_now.x + i == blue_now.x + j)
		{
			cout << "��ħ!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// ���� ���� ������ �̵����� �ʾ��� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
	if (i == 0)
	{
		cout << "���� ���� �̵� ����!" << endl;
		store.push_back({ -1,-1 });
		return;
	}
	*/
	// ���� ������ ���� ��ǥ�� �Ķ� ������ ���� ��ǥ�� ������ ���� ���� �ִ��� �����Ѵ�.
	// �̵����� �ʾ��� ���� store ť���� �� �������� �ִ� ��ǥ�� �Ȱ����Ƿ� �Լ��� �����Ѵ�.
	for (int k = 0; k < store.size(); k++)
	{
		if ((red_now.y == store[k].y) && ((red_now.x + i) == store[k].x))
		{
			if ((blue_now.y == store_blue[k].y) && ((blue_now.x + j) == store_blue[k].x))
			{
				cout << "������ ���� �� ����!" << endl;
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
					cout << "move����!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	// �׷��� �ʴٸ�, �� ������ ���� ��ǥ��, ���� Ž������ ���� ��ǥ�� �����ϴ� ť�� �����Ѵ�.
	// ���� ������ ������ ����� ��ǥ�� �����ϴ� ť���� �����Ѵ�.
	cout << "����! ";
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
		cout << "move����!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// �Լ� ����
	return;
}

void upmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// ���� ������ �̵��ϴ� �Ÿ�
	int j = 1;	// �Ķ� ������ �̵��ϴ� �Ÿ�
	int block = 0;
	do
	{
		switch (board[red_now.y - i][red_now.x])
		{
		case 'O':
			true_end = 1; cout << "��!" << endl; break;
		case '#':
			block = 1; i--; cout << "����!" << endl; break;
		default:
			i++; cout << "���!" << endl; break;
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

	// ���� ���� �����̳� �Ķ� ������ ���ۿ� �� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
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
			cout << "move����!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}

	// �׷��� �ʰ�, ���� ������ �Ķ� ������ ��ġ�� ���� ���, �� �Ʒ��� �ִ� ������ �Ʒ��� �ְ� �Ѵ�.
	if (red_now.y - i == blue_now.y - j)
		if (red_now.x == blue_now.x)
		{
			cout << "��ħ!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// ���� ���� ������ �̵����� �ʾ��� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
	if (i == 0)
	{
		cout << "���� ���� �̵� ����!" << endl;
		store.push_back({ -1,-1 });
		return;
	}
	*/
	// ���� ������ ���� ��ǥ�� �Ķ� ������ ���� ��ǥ�� ������ ���� ���� �ִ��� �����Ѵ�.
	// �̵����� �ʾ��� ���� store ť���� �� �������� �ִ� ��ǥ�� �Ȱ����Ƿ� �Լ��� �����Ѵ�.
	for (int k = 0; k < store.size(); k++)
	{
		if (((red_now.y - i) == store[k].y) && (red_now.x == store[k].x))
		{
			if (((blue_now.y - j) == store_blue[k].y) && (blue_now.x == store_blue[k].x))
			{
				cout << "������ ���� �� ����!" << endl;
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
					cout << "move����!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	// �׷��� �ʴٸ�, �� ������ ���� ��ǥ��, ���� Ž������ ���� ��ǥ�� �����ϴ� ť�� �����Ѵ�.
	// ���� ������ ������ ����� ��ǥ�� �����ϴ� ť���� �����Ѵ�.
	cout << "����! ";
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
		cout << "move����!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// �Լ� ����
	return;
}

void downmove(Point red_now, Point blue_now, queue<Point>& red_point, queue<Point>& blue_point,
	int &true_end, int &bad_end)
{
	int i = 1;	// ���� ������ �̵��ϴ� �Ÿ�
	int j = 1;	// �Ķ� ������ �̵��ϴ� �Ÿ�
	int block = 0;
	do
	{
		switch (board[red_now.y + i][red_now.x])
		{
		case 'O':
			true_end = 1; cout << "��!" << endl; break;
		case '#':
			block = 1; i--; cout << "����!" << endl; break;
		default:
			i++; cout << "���!" << endl; break;
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

	// ���� ���� �����̳� �Ķ� ������ ���ۿ� �� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
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
			cout << "move����!" << endl;
			cout << "store_size_count:" << store_size_count << endl;
		}
		return;
	}

	// �׷��� �ʰ�, ���� ������ �Ķ� ������ ��ġ�� ���� ���, �� ���ʿ� �ִ� ������ ������ �ְ� �Ѵ�.
	if (red_now.y + i == blue_now.y + j)
		if (red_now.x == blue_now.x)
		{
			cout << "��ħ!" << endl;
			if (i < j)
				j--;
			else
				i--;
		}
	/*
	// ���� ���� ������ �̵����� �ʾ��� ���, �Լ��� �����Ѵ�.
	// �� �� "���� ������ ������ ����� ��ǥ�� �����ϴ� ť"���� (-1,-1)�� �ִ´�.
	if (i == 0)
	{
		cout << "���� ���� �̵� ����!" << endl;
		store.push_back({ -1,-1 });
		return;
	}
	*/
	// ���� ������ ���� ��ǥ�� �Ķ� ������ ���� ��ǥ�� ������ ���� ���� �ִ��� �����Ѵ�.
	// �̵����� �ʾ��� ���� store ť���� �� �������� �ִ� ��ǥ�� �Ȱ����Ƿ� �Լ��� �����Ѵ�.
	for (int k = 0; k < store.size(); k++)
	{
		if (((red_now.y + i) == store[k].y) && (red_now.x == store[k].x))
		{
			if (((blue_now.y + j) == store_blue[k].y) && (blue_now.x == store_blue[k].x))
			{
				cout << "������ ���� �� ����!" << endl;
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
					cout << "move����!" << endl;
					cout << "store_size_count:" << store_size_count << endl;
				}
				return;
			}
		}
	}
	// �׷��� �ʴٸ�, �� ������ ���� ��ǥ��, ���� Ž������ ���� ��ǥ�� �����ϴ� ť�� �����Ѵ�.
	// ���� ������ ������ ����� ��ǥ�� �����ϴ� ť���� �����Ѵ�.
	cout << "����! ";
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
		cout << "move����!" << endl;
		cout << "store_size_count:" << store_size_count << endl;
	}
	// �Լ� ����
	return;
}