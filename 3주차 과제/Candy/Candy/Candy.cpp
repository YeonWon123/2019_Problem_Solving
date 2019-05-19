#include <iostream>
#include <vector>
#include <cmath>
// #define DEBUG
using namespace std;

// 사탕의 가격들을 저장하는 배열
int *price;

// 가격이 같은 사탕의 개수를 저장하는 배열
int *counts;

// 사탕 가격의 총 합을 저장하는 전역 변수
int total = 0;

// 가격이 같은 사탕이 최대 몇 개 있는지 저장하는 전역 변수
int max_counts = 0;

// 최종 방법의 갯수를 저장하는 전역 변수
int answer = 0;

bool thisisnumber(int input);
void combination(int i, int def, int *prices);

int main(void)
{
	// 1. 입력을 받아서 1차원 배열에 저장

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;

	price = new int[N];
	counts = new int[N];

	int sw;
	int input;
	int i = 0;
	for (int k = 0; k < N; k++) {
		sw = 0;
		price[i] = 0;
		counts[i] = 0;
		cin >> input;
		total = total + input;

		for (int j = 0; j < i; j++) {
			if (price[j] == input) {
				sw = 1;
				counts[j]++;
				if (max_counts < counts[j]) max_counts = counts[j];
				break;
			}
		}

		if (sw == 1) {
			sw = 0;
		}
		else {
			price[i] = input;
			counts[i]++;
			if (max_counts < counts[i]) max_counts = counts[i];
			i++;
		}

	}

#ifdef DEBUG
	for (int j = 0; j < i; j++) {
		cout << price[j] << "는 " << counts[j] << "개 있습니다!\n";
	}
	cout << "같은 사탕이 가장 많은 개수는 " << max_counts << "개 입니다!\n";

#endif

	// 2. 조합해서 소수인지 확인해보기

	// 먼저 각 원소에서 1개씩만 뽑아서 조합해보기 (ex: 1 2 7로만 조합)
	combination(i, 0, price);

#ifdef DEBUG
	cout << answer << endl;
#endif

	// 다음으로 원소가 2개 이상 있는 곳을 보기
	// 중복계산은 방지하고, 원소가 2개 이상 있으면 합쳐서 그것만 포함된 데이터만 비교하기
	// 현재 가능한 계산 : (1 1) 2 7, 1 2 (7 7), (1 1 1) 2 7, 1 2 (7 7 7 7), ...
	int *part = new int[i];
	
	for (int m = 2; m <= max_counts; m++) {
		for (int n = 0; n < i; n++) {
			if (counts[n] >= m) {
				if (thisisnumber(price[n]) * m) answer++;

				int sw = 0;
				for (int j = 0; j < i - 1; j++) {
					part[j - sw] = price[j];
					if (part[j] == price[n]) sw = 1;
				}

				combination(i - m + 1, price[n] * m, part);
			}
		}
	}

#ifdef DEBUG
	cout << answer << endl;
#endif
	
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

	if (sqrt(input)*sqrt(input) == input) return false;

	return true;
}

void combination(int i, int def, int *prices)
{
	for (int p = 0; p < i; p++)
	{
		for (int j = 0; j < i - p; j++) {
			int temp = def;
			for (int m = 0; m <= p; m++) temp = temp + prices[j + m];
			if (thisisnumber(temp)) {
#ifdef DEBUG
				cout << temp << endl;
#endif
				answer++;
			}
		}
	}
}