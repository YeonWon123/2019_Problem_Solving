#include <iostream>
#include <queue>
using namespace std;

typedef struct info {
	int rx;
	int ry;
	int bx;
	int by;
}INFO;

char map[10][11];

int visited[11][11][11][11] = { 0, };

//큐
queue<INFO> q;

//방향 탐색
int dy[] = { 1,0,-1,0 };
int dx[] = { 0,1,0,-1 };

//목적지 좌표
int hx, hy;

int bfs_find();

int main()
{

	int N, M;
	int i, j;
	INFO start;
	cin >> N;
	cin >> M;
	for (i = 0; i < N; i++)
	{
		cin >> map[i];
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (map[i][j] == 'R')
			{
				start.rx = j;
				start.ry = i;
			}
			if (map[i][j] == 'B')
			{
				start.bx = j;
				start.by = i;
			}
			if (map[i][j] == 'O')
			{
				hx = j;
				hy = i;
			}
		}
	}

	visited[start.rx][start.ry][start.bx][start.by] = 1; //방문기록 추가 

	//처음의 경우를 큐에다가 넣어줌
	q.push(start);

	int res = bfs_find();
	cout << res - 1 << endl;

	return 0;

}

int bfs_find()
{
	int i;
	int new_rx, new_ry, new_bx, new_by;
	while (!q.empty())//큐가 비어있지 않을때까지
	{
		INFO temp;
		temp = q.front();
		q.pop();

		if ((temp.rx == hx) && (temp.ry == hy)) // 만약 빨간 공이 구멍에 위치하면 리턴
		{
			return visited[temp.rx][temp.ry][temp.bx][temp.by];
		}

		for (i = 0; i < 4; i++)
		{
			new_rx = temp.rx;
			new_ry = temp.ry;
			new_bx = temp.bx;
			new_by = temp.by;

			int d_case; //1이면 빨간공 먼저 혹은 상관없음, 2이면 파란공 먼저

			if (i == 0)
			{
				d_case = 1;
				if (temp.rx == temp.bx)
				{
					if (temp.ry < temp.by)
					{
						d_case = 2;
					}
				}
			}
			else if (i == 1)
			{
				d_case = 1;
				if (temp.ry == temp.by)
				{
					if (temp.rx < temp.bx)
					{
						d_case = 2;
					}
				}
			}
			else if (i == 2)
			{
				d_case = 1;
				if (temp.rx == temp.bx)
				{
					if (temp.ry > temp.by)
					{
						d_case = 2;
					}
				}
			}
			else if (i == 3)
			{
				d_case = 1;
				if (temp.ry == temp.by)
				{
					if (temp.rx > temp.bx)
					{
						d_case = 2;
					}
				}
			}
			if (d_case == 1) //빨간공 먼저
			{
				while (map[new_ry + dy[i]][new_rx + dx[i]] != '#')//빨간 공을 이동
				{
					if (map[new_ry + dy[i]][new_rx + dx[i]] == 'O')//빨간공이 구멍에 들어가면 그 위치에 안착시키고 종료
					{
						new_ry = new_ry + dy[i];
						new_rx = new_rx + dx[i];
						break;
					}
					else
					{
						new_ry = new_ry + dy[i];
						new_rx = new_rx + dx[i];
					}
				}

				while ((map[new_by + dy[i]][new_bx + dx[i]] != '#') && ((new_by + dy[i] != new_ry) || (new_bx + dx[i] != new_rx)))//파란 공을 이동
				{
					if (map[new_by + dy[i]][new_bx + dx[i]] == 'O') break;//파란공이 구멍에 빠지면 이 경우는 해당사항 없음
					new_by = new_by + dy[i];
					new_bx = new_bx + dx[i];
				}
			}

			if (d_case == 2) //파란공 먼저
			{
				while (map[new_by + dy[i]][new_bx + dx[i]] != '#')//파란 공을 이동
				{
					if (map[new_by + dy[i]][new_bx + dx[i]] == 'O') break;//파란공이 구멍에 빠지면 이 경우는 해당사항 없음
					new_by = new_by + dy[i];
					new_bx = new_bx + dx[i];
				}

				while ((map[new_ry + dy[i]][new_rx + dx[i]] != '#') && ((new_ry + dy[i] != new_by) || (new_rx + dx[i] != new_bx)))//빨간 공을 이동
				{
					if (map[new_by + dy[i]][new_bx + dx[i]] == 'O') break;//파란공이 구멍에 빠지면 이 경우는 해당사항 없음
					
					if (map[new_ry + dy[i]][new_rx + dx[i]] == 'O')//빨간공이 구멍에 들어가면 그 위치에 안착시키고 종료
					{
						new_ry = new_ry + dy[i];
						new_rx = new_rx + dx[i];
						break;
					}
					else
					{
						new_ry = new_ry + dy[i];
						new_rx = new_rx + dx[i];
					}
				}

			}
			
			if (map[new_by + dy[i]][new_bx + dx[i]] == 'O')//파란공이 구멍에 빠지면 이 경우는 해당사항 없음
			{
				continue;
			}

			if ((visited[new_rx][new_ry][new_bx][new_by] == 0) && (visited[temp.rx][temp.ry][temp.bx][temp.by] <= 10))//방문한 기록이 없고 기울인 횟수가10 미만이면 큐에 추가
			{
				visited[new_rx][new_ry][new_bx][new_by] = visited[temp.rx][temp.ry][temp.bx][temp.by] + 1;
				INFO new_info = { new_rx,new_ry, new_bx ,new_by };
				q.push(new_info);
			}
		}
	}
	return 0;
}