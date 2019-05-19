#include <iostream>
#include <vector>
#include <cmath>

// #define DEBUG
#define SIZE 500001
using namespace std;

// ������ ���ݵ��� �����ϴ� �迭
int price[50];

// ������ ���� ������ ������ �����ϴ� �迭
int counts[50];

// 0���� 500000������ index�� ������ �����ϰ�, �� ������ ���� �� �ִ����� ã�ƺ�.
long long DP[SIZE] = { 0, };

// ���� ����� ������ �����ϴ� ���� ����
long long answer = 0;

bool thisisnumber(int input);

int main(void)
{
	// 1. �Է��� �޾Ƽ� 1���� �迭�� ����
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
		cout << price[j] << "�� " << counts[j] << "�� �ֽ��ϴ�!\n";
	}
#endif

	int zero_number = -1;
	int flag = 0;
	// 2. �����ؼ�, �� ���յǾ� ���� ���ڸ� index�� �ϸ� DP[index]�� ���� 1 ������Ŵ.
	// �ϳ��� ĵ�� ���� Ž���ϰ�, �ٸ� ĵ�� �������Ѽ� Ž���ϰ�...
	for (int j = 0; j < i; j++) {
		if (price[j] == 0) {
			zero_number = j;
			continue; // 0�̸�, ���߿� �������!
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
					//		cout << "�̶�!\n";
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

	// DP[index]�� ���� 0�� �ƴϸ�, �� ���� ĵ���� �������� ���� �� �ִٴ� ��
	// ����, index�� �Ҽ����, DP[index]�� ���� answer�� ���� �ش�.
	for (int k = 0; k < SIZE; k++) {
		if (DP[k] != 0 && thisisnumber(k)) answer += DP[k];
	}

	// 0�� ���� ����������!
	// �ϴ� �ΰ�, ���߿� �信 ���ϱ⸦ �� �ָ� �ɵ�
	// 0�� �� ���� ��쵵 ���� �״� (0�� ���� + 1)�� ���� �ش�
	if (zero_number != -1)
		answer = answer * (counts[zero_number] + 1);

	cout << answer;

	return 0;
}

// �Ҽ����� �����ϴ� �Լ�
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