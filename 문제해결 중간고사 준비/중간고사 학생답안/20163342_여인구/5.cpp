#include <iostream>
#include <algorithm>
#define MAX 100
using namespace std;


int main() {
	int n, m, b;
	int b1, b2, b3, b4;
	int road[MAX + 1][MAX + 1] = { 0, };

	cin >> n >> m;
	cin >> b;
	for (int i = 0; i < b; i++) {
		cin >> b1 >> b2 >> b3 >> b4;
		road[b1][b2] = -1;
		road[b3][b4] = -1;
	}

	int check = 1;
	for (int i = 0; i <= n; i++) {
		if (road[i][0] == -1)
			if (road[i + 1][0] == -1)
				break;
			else
				continue;
		else road[i][0] = 1;
	}

	for (int i = 0; i <= m; i++) {
		if (road[0][i] == -1)
			if (road[0][i + 1] == -1)
				break;
			else
				continue;
		else road[0][i] = 1;
	}


	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if ((road[i][j] == -1) && (road[i + 1][j] == -1))
				road[i][j] = 0;
			else if ((road[i][j] == -1) && (road[i][j + 1] != -1))
				road[i][j] = 0;
			else {
				if (road[i - 1][j] == -1 || road[i][j - 1] == -1)
					road[i][j] = max(road[i - 1][j], road[i][j - 1]);
				else
					road[i][j] = road[i - 1][j] + road[i][j - 1];
			}
		}

	cout << road[n][m-1];

	return 0;
}