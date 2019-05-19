#include <iostream>
#include <vector>
#include <cmath>
// #define DEBUG
using namespace std;

// ������ ���ݵ��� �����ϴ� �迭
int *price;

// ������ ���� ������ ������ �����ϴ� �迭
int *counts;

// ���� ������ �� ���� �����ϴ� ���� ����
int total = 0;

// ������ ���� ������ �ִ� �� �� �ִ��� �����ϴ� ���� ����
int max_counts = 0;

// ���� ����� ������ �����ϴ� ���� ����
int answer = 0;

bool thisisnumber(int input);
void combination(int i, int def, int *prices);

int main(void)
{
	// 1. �Է��� �޾Ƽ� 1���� �迭�� ����

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
		cout << price[j] << "�� " << counts[j] << "�� �ֽ��ϴ�!\n";
	}
	cout << "���� ������ ���� ���� ������ " << max_counts << "�� �Դϴ�!\n";

#endif

	// 2. �����ؼ� �Ҽ����� Ȯ���غ���

	// ���� �� ���ҿ��� 1������ �̾Ƽ� �����غ��� (ex: 1 2 7�θ� ����)
	combination(i, 0, price);

#ifdef DEBUG
	cout << answer << endl;
#endif

	// �������� ���Ұ� 2�� �̻� �ִ� ���� ����
	// �ߺ������ �����ϰ�, ���Ұ� 2�� �̻� ������ ���ļ� �װ͸� ���Ե� �����͸� ���ϱ�
	// ���� ������ ��� : (1 1) 2 7, 1 2 (7 7), (1 1 1) 2 7, 1 2 (7 7 7 7), ...
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