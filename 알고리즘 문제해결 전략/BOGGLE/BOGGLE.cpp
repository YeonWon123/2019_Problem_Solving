// 시간 초과 코드

#include <string>
#include <iostream>
using namespace std;

// 보글 게임판에서 단어를 찾는 재귀 호출 알고리즘
const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };

char board[5][5];

bool inRange(int y, int x)
{
	if (x >= 5 || x <= -1 || y >= 5 || y <= -1)
		return false;
	else
		return true;
}

// 5*5의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환
bool hasWord(int y, int x, const string& word) {
	// 기저 사례 1: 시작 위치가 범위 밖이면 무조건 실패
	if (!inRange(y, x)) return false;

	// 기저 사례 2: 첫 글자가 일치하지 않으면 실패
	if (board[y][x] != word[0]) return false;

	// 기저 사례 3: 단어 길이가 1이면 성공
	if (word.size() == 1) return true;

	// 인접한 여덟 칸을 검사한다.
	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction], nextX = x + dx[direction];
		// 다음 칸이 범위 안에 있는지, 첫 글자는 일치하는지 확인할 필요가 없다.
		if (hasWord(nextY, nextX, word.substr(1)))
			return true;
	}
	return false;
}

int main()
{
	int C; // 테스트 케이스의 수
	cin >> C;

	for (int k = 0; k < C; k++)
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				cin >> board[i][j];

		int N; // 단어의 수
		cin >> N;
		string *words = new string[N];
		for (int i = 0; i < N; i++)
		{
			int sw = 0;
			cin >> words[i];
			for (int x = 0; x < 5 && sw == 0; x++)
				for (int y = 0; y < 5 && sw == 0; y++)
					if (hasWord(x, y, words[i]) && sw == 0)
					{
						cout << words[i] << " " << "YES" << "\n";
						sw = 1;
					}
			if (sw == 0) cout << words[i] << " " << "NO" << "\n";
		}
	}
	return 0;
}