#include <iostream>
#include <vector>
#include <cmath>

#define DEBUG
using namespace std;

// 사탕의 가격들을 저장하는 배열
int price[50];

// 가격이 같은 사탕의 개수를 저장하는 배열
int counts[50];

// DP를 사용해서 누적시키는 값을 저장할 배열
int DP[100000];

// 최종 방법의 갯수를 저장하는 전역 변수
long long answer = 0;

bool thisisnumber(int input);

int main(void)
{
	// 1. 입력을 받아서 1차원 배열에 저장
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;

	int sw;
	int input;
	int i = 0;
	for (int k = 0; k < N; k++) {
		sw = 0;
		price[i] = 0;
		counts[i] = 0;
		cin >> input;

		for (int j = 0; j < i; j++) {
			if (price[j] == input) {
				sw = 1;
				counts[j]++;
				break;
			}
		}

		if (sw == 1) {
			sw = 0;
		}
		else {
			price[i] = input;
			counts[i]++;
			i++;
		}

	}

#ifdef DEBUG
	for (int j = 0; j < i; j++) {
		cout << price[j] << "는 " << counts[j] << "개 있습니다!\n";
	}
#endif

	// 2. 조합해서 소수인지 확인해보기
	// 하나의 캔디를 먼저 탐색하고, 다른 캔디를 누적시켜서 탐색하고...
	// 1이 4개, 2가 3개, 3이 2개, 4가 1개 있으면
	// 먼저 1을 탐색, DP 배열에는 0 1 2 3 4가 저장됨
	// 다음 2를 탐색, DP 배열에는 0 1 2 3 4 / 2 3 4 5 6 (2 1개 사용)/ 4 5 6 7 8 (2 두 개 사용)/ 6 7 8 9 10 (2 세 개 사용) 이 저장됨
	// 다음 3을 탐색, DP 배열에는 0 1 2 3 4 2 3 4 5 6 4 5 6 7 8 6 7 8 9 10 / 3 4 5 6 7 ... 이 저장됨
	int offset = 0;
	int offset_move = 0;
	for (int j = 0; j < i; j++) {
		if (j == 0) {
			for (int k = 0; k <= counts[j]; k++) {
				DP[k] = price[j] * k;
#ifdef DEBUG
				cout << DP[k] << " ";
#endif
				if (thisisnumber(DP[k])) {
#ifdef DEBUG
				//	cout << "답!";
#endif
					answer++;
				}
			}
			offset = counts[j] + 1;
			offset_move = offset;
#ifdef DEBUG
			cout << "\n";
#endif
		}
		else {
			for (int k = 1; k <= counts[j]; k++) {
				for (int m = 0; m < offset; m++) {
					DP[offset_move] = price[j] * k + DP[m];
#ifdef DEBUG
					cout << DP[offset_move] << " ";
#endif
					if (thisisnumber(DP[offset_move]))
					{
#ifdef DEBUG
					//	cout << "답!";
#endif
						answer++;
					}
					offset_move++;
				}

				offset = offset_move;
#ifdef DEBUG
				cout << "\n";
#endif
			}
		}
	}

	cout << answer << "\n";

	return 0;
}

// 소수인지 판정하는 함수
bool thisisnumber(int input)
{
	if (input == 2) return true;
	else if (input == 1 || input % 2 == 0) return false;

	for (int i = 3; i < sqrt(input); i++)
	{
		if (input % i == 0) return false;
		i++;
	}

	if ((int)sqrt(input)*(int)sqrt(input) == input) return false;

	return true;
}