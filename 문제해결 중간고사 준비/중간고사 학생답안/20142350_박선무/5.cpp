#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>

using namespace std;

//vector<char> moo;

int N;
int M;
int f;
long long city[101][101];
bool avail[101][101][101][101];

//int case_school(int x, int y)
//{
//	if (x == N - 1 && y == M) return 0;
//	
//}

int main()
{
	//freopen("input.txt", "r", stdin);//다하고 무조건 주석
	memset(avail, 1, sizeof(avail));
	memset(city, 0, sizeof(city));
	cin >> N;
	cin >> M;
	cin >> f;
	for (int i = 0; i < f; i++)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		avail[a][b][c][d] = false;
		avail[c][d][a][b] = false;
	}

	//printf("%d\n", case_school(0, 0));

	for (int i = 0; i <= N; i++)
	{
		city[i][0] = 1;
		if (!avail[i][0][i + 1][0])
			break;
	}
	for (int i = 0; i <= M; i++)
	{
		city[0][i] = 1;
		if (!avail[0][i][0][i+1])
			break;
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (avail[i][j - 1][i][j])
			{
				city[i][j] += city[i][j - 1];
			}
			if (avail[i - 1][j][i][j])
			{
				city[i][j] += city[i-1][j];
			}
		}
	}
	cout << city[N][M] << endl;
	//cout << avail[5][5][5][5] << endl;
}
