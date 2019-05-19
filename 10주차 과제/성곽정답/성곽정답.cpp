#include<iostream>
#include<queue>
#include<cstring>

#define endl "\n"
#define MAX 50
using namespace std;

int N, M;
int MAP[MAX][MAX];
bool Visit[MAX][MAX];

int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };

int Bigger(int A, int B) { if (A > B) return A; return B; }

void Input()
{
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAP[i][j];
		}
	}
}

int BFS(int a, int b)
{
	int Room_Size = 0;
	queue<pair<int, int>> Q;
	Q.push(make_pair(a, b));
	Visit[a][b] = true;
	Room_Size++;

	while (Q.empty() == 0)
	{
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();

		int Wall = 1;

		for (int i = 0; i < 4; i++)
		{
			if ((MAP[x][y] & Wall) != Wall)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (nx >= 0 && ny >= 0 && nx < N && ny < M)
				{
					if (Visit[nx][ny] == false)
					{
						Room_Size++;
						Visit[nx][ny] = true;
						Q.push(make_pair(nx, ny));
					}
				}
			}
			Wall = Wall * 2;
		}
	}
	return Room_Size;
}

void Solution()
{
	int Room_Cnt = 0;
	int Biggest_Room_Size = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Visit[i][j] == false)
			{
				Biggest_Room_Size = Bigger(Biggest_Room_Size, BFS(i, j));
				Room_Cnt++;
			}
		}
	}

	cout << Room_Cnt << endl;
	cout << Biggest_Room_Size << endl;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int Wall = 1; Wall <= 8; Wall *= 2)
			{
				if ((MAP[i][j] & Wall) == Wall)
				{
					memset(Visit, false, sizeof(Visit));
					MAP[i][j] = MAP[i][j] - Wall;
					Biggest_Room_Size = Bigger(Biggest_Room_Size, BFS(i, j));
					MAP[i][j] = MAP[i][j] + Wall;
				}
			}
		}
	}

	cout << Biggest_Room_Size << endl;
}

void Solve()
{
	Input();
	Solution();
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("Input.txt", "r", stdin);
	Solve();

	return 0;
}
