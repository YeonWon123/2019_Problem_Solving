#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, G;
int cnt;
vector<vector<int>> map(101, vector<int>(101));
bool gongsa[101][101][101][101];

void bfs(int x, int y) 
{
	
	if (x == N && y == M) {
		cnt++;
		return;
	} 
	else if (x == N)
		if (!gongsa[x][y][x][y+1])
			bfs(x, y + 1);
	else if (y == M)
		if (!gongsa[x][y][x + 1][y])
			bfs(x + 1, y);
	else {
		if (!gongsa[x][y][x][y + 1])
			bfs(x, y + 1);
		if (!gongsa[x][y][x + 1][y]) 
			bfs(x + 1, y);
	}
}

int main(void)
{
	cin >> N >> M >> G;

	for (int i = 0; i < G; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		gongsa[x1][y1][x2][y2] = true;
	}

	bfs(0, 0);

	cout << cnt;
}