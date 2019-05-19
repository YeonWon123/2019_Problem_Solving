#include <iostream>
#include <vector>
#include <cmath>

#define DEBUG
using namespace std;

// ������ ���ݵ��� �����ϴ� �迭
int price[50];

// ������ ���� ������ ������ �����ϴ� �迭
int counts[50];

// DP�� ����ؼ� ������Ű�� ���� ������ �迭
int DP[100000];

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

	// 2. �����ؼ� �Ҽ����� Ȯ���غ���
	// �ϳ��� ĵ�� ���� Ž���ϰ�, �ٸ� ĵ�� �������Ѽ� Ž���ϰ�...
	// 1�� 4��, 2�� 3��, 3�� 2��, 4�� 1�� ������
	// ���� 1�� Ž��, DP �迭���� 0 1 2 3 4�� �����
	// ���� 2�� Ž��, DP �迭���� 0 1 2 3 4 / 2 3 4 5 6 (2 1�� ���)/ 4 5 6 7 8 (2 �� �� ���)/ 6 7 8 9 10 (2 �� �� ���) �� �����
	// ���� 3�� Ž��, DP �迭���� 0 1 2 3 4 2 3 4 5 6 4 5 6 7 8 6 7 8 9 10 / 3 4 5 6 7 ... �� �����
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
				//	cout << "��!";
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
					//	cout << "��!";
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