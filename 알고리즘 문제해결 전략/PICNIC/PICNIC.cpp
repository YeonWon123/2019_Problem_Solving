#include <iostream>
#include <cstring> // memset이 cstring에 있음
using namespace std;

int n; // 학생의 수
int m; // 친구 쌍의 수

bool areFriends[10][10];
// taken[i] = i번째 학생이 짝을 이미 찾았으면 true, 아니면 false
int countPairings(bool taken[10]) {
	// 남은 학생들 중 가장 번호가 빠른 학생을 찾는다
	int firstFree = -1;
	for (int i = 0; i < (n); i++) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}
	// 기저 사례: 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
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
	int C; // 테스트 케이스의 수
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