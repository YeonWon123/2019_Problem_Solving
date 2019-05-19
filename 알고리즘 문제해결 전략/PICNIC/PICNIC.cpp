#include <iostream>
#include <cstring> // memset�� cstring�� ����
using namespace std;

int n; // �л��� ��
int m; // ģ�� ���� ��

bool areFriends[10][10];
// taken[i] = i��° �л��� ¦�� �̹� ã������ true, �ƴϸ� false
int countPairings(bool taken[10]) {
	// ���� �л��� �� ���� ��ȣ�� ���� �л��� ã�´�
	int firstFree = -1;
	for (int i = 0; i < (n); i++) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}
	// ���� ���: ��� �л��� ¦�� ã������ �� ���� ����� ã������ �����Ѵ�.
	if (firstFree == -1) return 1;
	int ret = 0;
	for (int pairWith = (firstFree + 1); pairWith < (n); pairWith++) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}


int main(void)
{
	int C; // �׽�Ʈ ���̽��� ��
	cin >> C;

	for (int k = 0; k < C; k++)
	{
		cin >> n >> m;

		memset(areFriends, 0, sizeof(areFriends));

/*		for(int i = 0; i < 10; i++)
			for(int j = 0; j < 10; j++)
				areFriends[i][j] = 0;        */

		int a, b;
		for (int i = 0; i < m; i++)
		{
			cin >> a >> b;
			areFriends[a][b] = true;
			areFriends[b][a] = true;
		}

		bool taken[10] = { 0, };

		// memset(taken, 0, sizeof(taken));
		
		cout << countPairings(taken) << "\n";
	}
	return 0;
}