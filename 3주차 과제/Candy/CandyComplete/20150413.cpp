#include <iostream>
#include <vector>
#include <cmath>

// #define DEBUG
#define SIZE 500001
using namespace std;

// 사탕의 가격들을 저장하는 배열
int price[50];

// 가격이 같은 사탕의 개수를 저장하는 배열
int counts[50];

// 0부터 500000까지의 index를 가지게 설정하고, 이 값들이 나올 수 있는지를 찾아봄.
long long DP[SIZE] = { 0, };

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

	int zero_number = -1;
	int flag = 0;
	// 2. 조합해서, 그 조합되어 나온 숫자를 index라 하면 DP[index]의 값을 1 증가시킴.
	// 하나의 캔디를 먼저 탐색하고, 다른 캔디를 누적시켜서 탐색하고...
	for (int j = 0; j < i; j++) {
		if (price[j] == 0) {
			zero_number = j;
			continue; // 0이면, 나중에 계산하자!
		}
		if (flag == 0) {
			for (int k = 0; k <= counts[j]; k++) {
				DP[price[j] * k]++;
				flag = 1;
			}
		}
		else {
			for (int k = SIZE; k >= 0; k--) {
				if (DP[k] != 0) {
					for (int m = 1; m <= counts[j]; m++) {
					//	if (k + price[j] * m == 5) 
					//		cout << "이때!\n";
						DP[k + price[j] * m] += DP[k];
						
					}
				}
			}
		}
	}

#ifdef DEBUG	
	for(int i = 0; i < 30; i++)
		cout << DP[i] << "\n";
#endif

	// DP[index]의 값이 0이 아니면, 그 수를 캔디의 조합으로 만들 수 있다는 뜻
	// 따라서, index가 소수라면, DP[index]의 값을 answer에 더해 준다.
	for (int k = 0; k < SIZE; k++) {
		if (DP[k] != 0 && thisisnumber(k)) answer += DP[k];
	}

	// 0은 따로 구분해주자!
	// 일단 두고, 나중에 답에 곱하기를 해 주면 될듯
	// 0을 안 쓰는 경우도 있을 테니 (0의 개수 + 1)을 곱해 준다
	if (zero_number != -1)
		answer = answer * (counts[zero_number] + 1);

	cout << answer;

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