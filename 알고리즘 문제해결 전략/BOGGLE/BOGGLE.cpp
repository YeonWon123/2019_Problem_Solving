// �ð� �ʰ� �ڵ�

#include <string>
#include <iostream>
using namespace std;

// ���� �����ǿ��� �ܾ ã�� ��� ȣ�� �˰���
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

// 5*5�� ���� ���� ���� �ش� ��ġ���� �־��� �ܾ �����ϴ����� ��ȯ
bool hasWord(int y, int x, const string& word) {
	// ���� ��� 1: ���� ��ġ�� ���� ���̸� ������ ����
	if (!inRange(y, x)) return false;

	// ���� ��� 2: ù ���ڰ� ��ġ���� ������ ����
	if (board[y][x] != word[0]) return false;

	// ���� ��� 3: �ܾ� ���̰� 1�̸� ����
	if (word.size() == 1) return true;

	// ������ ���� ĭ�� �˻��Ѵ�.
	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction], nextX = x + dx[direction];
		// ���� ĭ�� ���� �ȿ� �ִ���, ù ���ڴ� ��ġ�ϴ��� Ȯ���� �ʿ䰡 ����.
		if (hasWord(nextY, nextX, word.substr(1)))
			return true;
	}
	return false;
}

int main()
{
	int C; // �׽�Ʈ ���̽��� ��
	cin >> C;

	for (int k = 0; k < C; k++)
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				cin >> board[i][j];

		int N; // �ܾ��� ��
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