#include <iostream>
#include <queue>
using namespace std;

char **board;
vector<int> odd_even;
queue<int> column_list;
void star(int N, int row);

int main()
{
	int N;
	cin >> N;

	board = new char*[N+1];
	for (int i = 0; i < N+1; i++)
		board[i] = new char[2*N+1];

	for (int i = 0; i < N+1; i++)
		for (int j = 0; j < 2*N+1; j++)
			board[i][j] = ' ';

	int column = 3;
	int row = 4;
	int sw = 1; // 0�̸� ¦��, 1�̸� Ȧ��
	int queuein = 3;
	column_list.push(3);
	int count = 2;
	int even_count = 0;

	star(N, 1);
	while (1)
	{
		if (queuein == N) break;
		if (queuein % 2 == 0)
		{
			if (sw == 1)
			{
				row = row + 3;
				sw = 0;
			}
			star(N - queuein, row);
			star(N + queuein, row);

			column_list.push(queuein - 3);
			column_list.push(queuein + 3);
		}
		else
		{
			if (sw == 0)
			{
				even_count++;
				row = row + 3;
				cout << "row : " << row << " ";
				sw = 1;
			}
			int front, back;
			front = column_list.front();
			cout << "Ȧ�� ����: " << front << " ";
			back = column_list.back();
			cout << "Ȧ�� ������: " << back << endl;
			int k = -1;
			while (!column_list.empty())
			{
				int a = column_list.front();
				star(N - a, row);
				star(N + a, row);
				
				if (even_count % 2 == 1 && even_count != 1)
				{
					odd_even.push_back(a + 3 * k);
					k *= -1;
				}

				column_list.pop();
			}
			if (queuein != 3 && queuein != row-1)
			{
				column_list.push(front-3);
				
				if (even_count % 2 == 1 && even_count != 1)
				{
					for (int i = 1; i < odd_even.size()-1; i++)
					{
						column_list.push(odd_even[i]);
					}

					while (!odd_even.empty())
						odd_even.pop_back();
				} 

				column_list.push(back+3);
			}
		}

		if (column_list.empty())
		{
			if (N == 3 * count) break;
			count++;
			even_count = 0;
			column = column * 2;
			queuein = column;
		}
		else
		{
			queuein = column_list.front();
			if (queuein % 2 == 0) column_list.pop();
		}
	}

	for (int i = 1; i < N+1; i++)
	{
		for (int j = 1; j < 2*N+1; j++)
			cout << board[i][j];

		if (i == N) break;
		cout << "\n";
	}

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