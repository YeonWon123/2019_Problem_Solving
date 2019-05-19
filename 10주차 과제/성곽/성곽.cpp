#include <iostream>
#include <queue>
using namespace std;

//#define DEBUG
//#define DEBUG2
// ��ǥ�� ��Ÿ���� ����ü
typedef struct POINT {
	int y;
	int x;
} point;

// �Է°��� ���� int�� array
int input[50][50];

// ���� ���� ���� ���̸� ���ϱ� ���� ��������
int max_area = 0;

// bfs �Լ������� �� ���ư��� �ϱ� ���� ���������� ����
int n, m;

// Ž���ߴ��� ���� ���ߴ����� �˷��ִ� int�� �迭 (Ž�������� 1, �������� 0)
int visited[50][50] = { 0, };

// bfs(�ʺ�켱Ž��) �Լ�, queue�� ���
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

	// �� ���� �ִ� ���� ���� - bfs �Լ��� ȣ���� Ƚ�� (�̹� �湮�� ���� bfs�Լ��� �ߺ� ȣ������ �����Ƿ�)
	// ���� ���� ���� ���� - ��� ���� ���� bfs �Լ��� ������ �ڵ����� ���ŵ� 
	// �� ��� �� �� �̹� �湮�� ���� bfs�Լ��� �ٽ� ������ ���� - �ǹ� ����
	int counts = 0; // ���� ����
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (visited[j][i] == 0) {
				counts++;  // ���� ���� ����
				bfs(j, i); // ���� ���� ���ϱ�
			}
		}
	}

	cout << counts << "\n";     // �� ���� �ִ� ���� ����
	cout << max_area << "\n";   // ���� ���� ���� ����

	// �ϳ��� ���� �����Ͽ� ���� �� �ִ� ���� ���� ���� ũ��
	// -> ���� �ϳ��� ���ְ� �� ���� �������� bfs�� �õ��Ѵ�.
	// -> �� ���̰� max_area�� ��� ����
	// -> �׸��� ���� ���� �ٽ� �����Ѵ�. �̸� ��� ���� �ݺ�


#ifdef DEBUG2
	cout << "\n\n\n\n\n���� �����Ͽ� ���� �� �ִ� ���� ���� ���� ũ��\n\n\n\n\n";
#endif

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {

#ifdef DEBUG2
			cout << "Ž���� �� : " << j << " " << i << endl;
#endif

			// ���ʿ� ���� �ִٸ� �� ���� �μ���(-1) bfs
			if ((input[j][i] & 1) != 0) {
#ifdef DEBUG2
				cout << "���ʿ� �� ����!" << endl;
#endif
				// bfs �� visited �迭 �ʱ�ȭ
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}
				input[j][i] = input[j][i] - 1;
				bfs(j, i);
				input[j][i] = input[j][i] + 1;
			}

			// ���ʿ� ���� �ִٸ� �� ���� �μ���(-2) bfs
			if ((input[j][i] & 2) != 0) {
#ifdef DEBUG2
				cout << "���ʿ� �� ����!" << endl;
#endif
				// bfs �� visited �迭 �ʱ�ȭ
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}

				input[j][i] = input[j][i] - 2;
				bfs(j, i);
				input[j][i] = input[j][i] + 2;
			}


			// ���ʿ� ���� �ִٸ� �� ���� �μ���(-4) bfs
			if ((input[j][i] & 4) != 0) {
#ifdef DEBUG2
				cout << "���ʿ� �� ����!" << endl;
#endif
				// bfs �� visited �迭 �ʱ�ȭ
				for (int k = 0; k < 50; k++) {
					for (int p = 0; p < 50; p++) {
						visited[p][k] = 0;
					}
				}
				
				input[j][i] = input[j][i] - 4;
				bfs(j, i);
				input[j][i] = input[j][i] + 4;
			}

			// ���ʿ� ���� �ִٸ� �� ���� �μ���(-8) bfs
			if ((input[j][i] & 8) != 0) {
#ifdef DEBUG2
				cout << "���ʿ� �� ����!" << endl;
#endif
				// bfs �� visited �迭 �ʱ�ȭ
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

	// ��� �����Ͽ��ٸ� max_area�� �ϳ��� ���� �����Ͽ��� �� ������ �ְ� ����
	cout << max_area << "\n"; // �ϳ��� ���� �����Ͽ��� �� ������ �ְ� ����

	return 0;
}

// bfs(�ʺ�켱Ž��) ����, queue�� ���
void bfs(int y, int x) {
#ifdef DEBUG
	cout << "���ʽ����� : " << y << " " << x << endl;
#endif
	int area = 1; // ���� ũ�Ⱑ �ּ� 1 (���� Ž������ ���� ���� ���� bfs�ϴ°Ŵϱ�, �� �ϳ��� ���� ũ�� 1)
	visited[y][x] = 1; // Ž�������� ��Ÿ��
	// bfs�� ���� queue
	queue<point> data;

	// ù ��° ��ǥ�� queue�� push
	data.push({ y,x });
	
	// queue�� �� ������ push�� pop �ݺ�
	// �� ���� ���� ������ ���ؼ��� ��� Ž���Ͽ�
	// �ϳ��� ����(��)�� ���̸� ���Ѵ�.
	while (data.empty() == 0) {

		// �ϳ��� ��ǥ ����
		point loc = data.front();
		data.pop();
#ifdef DEBUG
		cout << "�� ��ǥ : " << loc.y << " " << loc.x << endl;
#endif
		// �� ��ǥ�� ���� ���� �ִ��� ������ �Ǵ��غ���
		// ��Ʈ����ũ ���
		// 11 & 1 = 1011 & 0001 = 0001 -> �� ����
		// 11 & 2 = 1011 & 0010 = 0010 -> �� ����
		// 11 & 4 = 1011 & 0100 = 0000 -> �� ����!
		// 11 & 8 = 1011 & 1000 = 1000 -> �� ����

		// ���ʿ� ���ؼ� ���� �ִ��� ������ Ž�� -> ���� ������ �װ����� �̵� (x��ǥ -1)
#ifdef DEBUG
		cout << input[loc.y][loc.x] << endl;
#endif
		if ((input[loc.y][loc.x] & 1) == 0) {
			int new_y = loc.y;
			int new_x = loc.x - 1;

			// �̵��� ���� �׵θ��� �ȵȴ�.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// ���� �湮�� �������� ���� �湮�� ����.
				// �ʺ�켱Ž���̴� ���⼭ bfs�Լ��� ���ȣ���ϸ� �ȵȴ�. -> �װ� dfs
				// ��� queue�� �� ��ǥ�� �ִ´�.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "�������� �� �� �ִ� ��ǥ : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // �湮�� �� �ִٴ� �� �� ���� ���̰� +1�̶�� ���̴�.
				}
			}
		}

		// ���ʿ� ���ؼ� ���� �ִ��� ������ Ž�� -> ���� ������ �װ����� �̵� (y��ǥ -1)
		if ((input[loc.y][loc.x] & 2) == 0) {
			int new_y = loc.y - 1;
			int new_x = loc.x;

			// �̵��� ���� �׵θ��� �ȵȴ�.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// ���� �湮�� �������� ���� �湮�� ����.
				// �ʺ�켱Ž���̴� ���⼭ bfs�Լ��� ���ȣ���ϸ� �ȵȴ�. -> �װ� dfs
				// ��� queue�� �� ��ǥ�� �ִ´�.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "�������� �� �� �ִ� ��ǥ : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // �湮�� �� �ִٴ� �� �� ���� ���̰� +1�̶�� ���̴�.
				}
			}
		}

		// ���ʿ� ���ؼ� ���� �ִ��� ������ Ž�� -> ���� ������ �װ����� �̵� (x��ǥ +1)
		if ((input[loc.y][loc.x] & 4) == 0) {
			int new_y = loc.y;
			int new_x = loc.x + 1;

			// �̵��� ���� �׵θ��� �ȵȴ�.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// ���� �湮�� �������� ���� �湮�� ����.
				// �ʺ�켱Ž���̴� ���⼭ bfs�Լ��� ���ȣ���ϸ� �ȵȴ�. -> �װ� dfs
				// ��� queue�� �� ��ǥ�� �ִ´�.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "�������� �� �� �ִ� ��ǥ : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // �湮�� �� �ִٴ� �� �� ���� ���̰� +1�̶�� ���̴�.
				}
			}
		}

		// ���ʿ� ���ؼ� ���� �ִ��� ������ Ž�� -> ���� ������ �װ����� �̵� (y��ǥ +1)
		if ((input[loc.y][loc.x] & 8) == 0) {
			int new_y = loc.y + 1;
			int new_x = loc.x;

			// �̵��� ���� �׵θ��� �ȵȴ�.
			if (new_y >= 0 && new_x >= 0 && new_y < m && new_x < n) {
				// ���� �湮�� �������� ���� �湮�� ����.
				// �ʺ�켱Ž���̴� ���⼭ bfs�Լ��� ���ȣ���ϸ� �ȵȴ�. -> �װ� dfs
				// ��� queue�� �� ��ǥ�� �ִ´�.
				if (visited[new_y][new_x] == 0) {
#ifdef DEBUG
					cout << "�������� �� �� �ִ� ��ǥ : " << new_y << " " << new_x << "\n";
#endif
					data.push({ new_y, new_x });
					visited[new_y][new_x] = 1;
					area++; // �湮�� �� �ִٴ� �� �� ���� ���̰� +1�̶�� ���̴�.
				}
			}
		}
	}

#ifdef DEBUG2
	cout << "area�� " << area << "\n";
#endif
	
	// queue�� �� ������ �ݺ��ߴٸ�, �ϳ��� �濡 ���ؼ� Ž���� ��� �Ϸ��� ���̴�.
	// �׷��Ƿ�, �� ���� ���� ���� ������ ����, ���� ���� ���̸� ���� ���� ���� ���̸� �����ϸ� �ȴ�.
	if (max_area < area)
		max_area = area;
	
#ifdef DEBUG2
	cout << "max_area�� " << max_area << "\n\n";
#endif

}