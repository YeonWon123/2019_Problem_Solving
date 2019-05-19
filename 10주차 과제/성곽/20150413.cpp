#include <iostream>
#include <queue>
using namespace std;

//#define DEBUG
//#define DEBUG2
// 좌표를 나타내는 구조체
typedef struct POINT {
	int y;
	int x;
} point;

// 입력값을 받을 int형 array
int input[50][50];

// 가장 넓은 방의 넓이를 구하기 위한 전역변수
int max_area = 0;

// bfs 함수에서도 잘 돌아가게 하기 위해 전역변수로 선언
int n, m;

// 탐색했는지 아직 안했는지를 알려주는 int형 배열 (탐색했으면 1, 안했으면 0)
int visited[50][50] = { 0, };

// bfs(너비우선탐색) 함수, queue를 사용
void bfs(int y, int x);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			cin >> input[j][i];
		}
	}

#ifdef DEBUG
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			cout << input[j][i] << " ";
		}
		cout << "\n";
	}

#endif

	// 이 성에 있는 방의 개수 - bfs 함수를 호출한 횟수 (이미 방문한 점은 bfs함수를 중복 호출하지 않으므로)
	// 가장 넓은 방의 넓이 - 모든 점에 대해 bfs 함수를 돌리면 자동으로 갱신됨 
	// 단 모든 점 중 이미 방문한 점은 bfs함수를 다시 돌리지 않음 - 의미 없음
	int counts = 0; // 방의 개수
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (visited[j][i] == 0) {
				counts++;  // 방의 개수 증가
				bfs(j, i); // 방의 넓이 구하기
			}
		}
	}

	cout << counts << "\n";     // 이 섬에 있는 방의 개수
	cout << max_area << "\n";   // 가장 넓은 방의 넓이

	// 하나의 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기
	// -> 벽을 하나씩 없애고 그 곳을 기준으로 bfs를 시도한다.
	// -> 그 넓이가 max_area일 경우 갱신
	// -> 그리고 나서 벽을 다시 생성한다. 이를 모든 벽에 반복


#ifdef DEBUG2
	cout << "\n\n\n\n\n벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기\n\n\n\n\n";
#endif

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {

#ifdef DEBUG2
			cout << "탐색할 점 : " << j << " " << i << endl;
#endif

			// 서쪽에 벽이 있다면 그 벽을 부수고(-1) bfs
			if ((input[j][i] & 1) != 0) {
#ifdef DEBUG2
				cout << "서쪽에 벽 있음!" << endl;
#endif
				// bfs 전 visited 배열 초기화
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}
				input[j][i] = input[j][i] - 1;
				bfs(j, i);
				input[j][i] = input[j][i] + 1;
			}

			// 북쪽에 벽이 있다면 그 벽을 부수고(-2) bfs
			if ((input[j][i] & 2) != 0) {
#ifdef DEBUG2
				cout << "북쪽에 벽 있음!" << endl;
#endif
				// bfs 전 visited 배열 초기화
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}

				input[j][i] = input[j][i] - 2;
				bfs(j, i);
				input[j][i] = input[j][i] + 2;
			}


			// 동쪽에 벽이 있다면 그 벽을 부수고(-4) bfs
			if ((input[j][i] & 4) != 0) {
#ifdef DEBUG2
				cout << "동쪽에 벽 있음!" << endl;
#endif
				// bfs 전 visited 배열 초기화
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}
				
				input[j][i] = input[j][i] - 4;
				bfs(j, i);
				input[j][i] = input[j][i] + 4;
			}

			// 남쪽에 벽이 있다면 그 벽을 부수고(-8) bfs
			if ((input[j][i] & 8) != 0) {
#ifdef DEBUG2
				cout << "남쪽에 벽 있음!" << endl;
#endif
				// bfs 전 visited 배열 초기화
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}

				input[j][i] = input[j][i] - 8;
				bfs(j, i);
				input[j][i] = input[j][i] + 8;
			}
		}
	}

	// 모두 수행하였다면 max_area가 하나의 벽을 제거하였을 때 가능한 최고 넓이
	cout << max_area << "\n"; // 하나의 벽을 제거하였을 때 가능한 최고 넓이

	return 0;
}

// bfs(너비우선탐색) 시작, queue를 사용
void bfs(int y, int x) {
#ifdef DEBUG
	cout << "최초시작점 : " << y << " " << x << endl;
#endif
	int area = 1; // 방의 크기가 최소 1 (아직 탐색하지 않은 점에 대해 bfs하는거니깐, 점 하나당 방의 크기 1)
	visited[y][x] = 1; // 탐색했음을 나타냄
	// bfs를 위한 queue
	queue<point> data;

	// 첫 번째 좌표를 queue에 push
	data.push({ y,x });
	
	// queue가 빌 때까지 push와 pop 반복
	// 즉 벽이 없는 영역에 대해서는 모두 탐색하여
	// 하나의 공간(방)의 넓이를 구한다.
	while (data.empty() == 0) {

		// 하나의 좌표 빼기
		point loc = data.front();
		data.pop();
#ifdef DEBUG
		cout << "뺀 좌표 : " << loc.y << " " << loc.x << endl;
#endif
		// 뺀 좌표에 대해 벽이 있는지 없는지 판단해보기
		// 비트마스크 사용
		// 11 & 1 = 1011 & 0001 = 0001 -> 벽 존재
		// 11 & 2 = 1011 & 0010 = 0010 -> 벽 존재
		// 11 & 4 = 1011 & 0100 = 0000 -> 벽 없음!
		// 11 & 8 = 1011 & 1000 = 1000 -> 벽 존재

		// 서쪽에 대해서 벽이 있는지 없는지 탐색 -> 벽이 없으면 그곳으로 이동 (x좌표 -1)
#ifdef DEBUG
		cout << input[loc.y][loc.x] << endl;
#endif
		if ((input[loc.y][loc.x] & 1) == 0) {
			int new_y = loc.y;
			int new_x = loc.x - 1;

			// 이동한 곳이 테두리면 안된다.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// 아직 방문을 안했으면 새로 방문해 본다.
				// 너비우선탐색이니 여기서 bfs함수를 재귀호출하면 안된다. -> 그건 dfs
				// 대신 queue에 그 좌표를 넣는다.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "서쪽으로 갈 수 있는 좌표 : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // 방문할 수 있다는 건 방 안의 넓이가 +1이라는 것이다.
				}
			}
		}

		// 북쪽에 대해서 벽이 있는지 없는지 탐색 -> 벽이 없으면 그곳으로 이동 (y좌표 -1)
		if ((input[loc.y][loc.x] & 2) == 0) {
			int new_y = loc.y - 1;
			int new_x = loc.x;

			// 이동한 곳이 테두리면 안된다.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// 아직 방문을 안했으면 새로 방문해 본다.
				// 너비우선탐색이니 여기서 bfs함수를 재귀호출하면 안된다. -> 그건 dfs
				// 대신 queue에 그 좌표를 넣는다.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "북쪽으로 갈 수 있는 좌표 : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // 방문할 수 있다는 건 방 안의 넓이가 +1이라는 것이다.
				}
			}
		}

		// 동쪽에 대해서 벽이 있는지 없는지 탐색 -> 벽이 없으면 그곳으로 이동 (x좌표 +1)
		if ((input[loc.y][loc.x] & 4) == 0) {
			int new_y = loc.y;
			int new_x = loc.x + 1;

			// 이동한 곳이 테두리면 안된다.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// 아직 방문을 안했으면 새로 방문해 본다.
				// 너비우선탐색이니 여기서 bfs함수를 재귀호출하면 안된다. -> 그건 dfs
				// 대신 queue에 그 좌표를 넣는다.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "동쪽으로 갈 수 있는 좌표 : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // 방문할 수 있다는 건 방 안의 넓이가 +1이라는 것이다.
				}
			}
		}

		// 남쪽에 대해서 벽이 있는지 없는지 탐색 -> 벽이 없으면 그곳으로 이동 (y좌표 +1)
		if ((input[loc.y][loc.x] & 8) == 0) {
			int new_y = loc.y + 1;
			int new_x = loc.x;

			// 이동한 곳이 테두리면 안된다.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// 아직 방문을 안했으면 새로 방문해 본다.
				// 너비우선탐색이니 여기서 bfs함수를 재귀호출하면 안된다. -> 그건 dfs
				// 대신 queue에 그 좌표를 넣는다.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "남쪽으로 갈 수 있는 좌표 : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // 방문할 수 있다는 건 방 안의 넓이가 +1이라는 것이다.
				}
			}
		}
	}

#ifdef DEBUG2
	cout << "area는 " << area << "\n";
#endif
	
	// queue가 빌 때까지 반복했다면, 하나의 방에 대해서 탐색을 모두 완료한 것이다.
	// 그러므로, 그 방이 가장 넓은 방인지 보고, 가장 넓은 방이면 가장 넓은 방의 넓이를 갱신하면 된다.
	if (max_area < area)
		max_area = area;
	
#ifdef DEBUG2
	cout << "max_area는 " << max_area << "\n\n";
#endif

}