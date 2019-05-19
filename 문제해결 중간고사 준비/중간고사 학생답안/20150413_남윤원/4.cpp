#include <iostream>
#include <vector>
using namespace std;

int input[201];
int store[21] = { 0, };
int store_count = 0;
int palindrome[201][201]; // input[i]���� input[j]���� �Ӹ�����̸� 1, �ƴϸ� 0
int counts = 1;
int palindrome_counts = 0;

int main(void)
{
	int N, K;
	cin >> N >> K;
	
	int a;
	for (int i = 1; i <= N; i++) {
		cin >> a;
		if (i == 1) {
			input[counts] = a;
			counts++;
		}
		else {
			if (input[counts - 1] == a) continue;
			else {
				input[counts] = a;
				counts++;
			}
		}
	}

	counts--;

#ifdef DEBUG
	for (int i = 1; i <= counts; i++) {
		cout << input[i] << " ";
		}
#endif

	// �Ӹ������ �Ẹ��!
	// �ϳ��� ��� �Ӹ����
	for (int i = 1; i <= counts; i++)
		palindrome[i][i] = 1;

	// �ΰ��� ���� ������ ������ �Ӹ����
	for (int i = 1; i < counts; i++)
		if (input[i] == input[i + 1])
			palindrome[i][i + 1] = 1;
		else
			palindrome[i][i + 1] = 0;

	// �������� ��� ��ȭ���� ������ ����
	// if (input[i] == input[j]) palindrome[i][j] = palindrome[i+1][j-1];
	// else palindrome[i][j] = 0;
	for (int j = 2; j < counts; j++) {
		for (int i = 1; i + j <= counts; i++) {
			if (input[i] == input[i + j]) palindrome[i][i + j] = palindrome[i + 1][i + j - 1];
			else palindrome[i][i + j] = 0;
			
			if (palindrome[i][i + j] == 1) {
				palindrome_counts++;
			}
		}
	}
	
#ifdef DEBUG


	cout << "\n�Ӹ���� ���\n";
	for (int i = counts; i >= 1; i++) {
		for (int j = 1; j <= counts; j++)
			cout << palindrome[i][j] << " ";
		cout << "\n";
	}
#endif

	if (palindrome[1][counts] == 1) {
		cout << counts / 2;
		return 0;
	}

	int answer = 0;
	for (int j = counts - 1; j > 2; j++) {
		for (int i = 1; i + j <= counts; i++) {
			if (palindrome[i][i + j] == 1) {
				store_count = 1;
				// ���� �̹� ó���� �κ��̸� ����ϱ�
				int sw = 0;
				for (int p = i; p < i + j; p++) {
					if (input[p] != input[p + 1]) {
						sw = 1;	break;
					}
				}
				// i���� i+j������ ���� �� input[i]�� �ٲٱ�
				// �ٸ��� ������ ���, �� ���� - 1 �ϱ�
				if (sw == 0) {
					store[store_count] = input[i];
					store_count++;
					for (int p = i; p < i + j; p++) {
						if (input[i] != input[p + 1]) {
							int sw2 = 0;
							for (int t = 1; t <= store_count; t++) {
								if (store[t] == input[p + 1]) {
									sw2 = 1;
									break;
								}
								if (sw2 == 0) {
									store[store_count] = input[p + 1];
									store_count++;
								}
								input[p + 1] = input[i];
							}
						}
					}
				}

				answer += store_count - 1;
			}
		}
	}
	
	int answer_arr[201];
	answer_arr[1] = input[1];
	int answer_arr_count = 1;
	for (int i = 2; i <= counts; i++) {
		if (input[1] != input[i]) {
			int sw3 = 1;
			for (int j = 2; j <= answer_arr_count; j++) {
				if (answer_arr[j] == input[i]) {
					sw3 = 0;
					break;
				}
			}
			if (sw3 == 1) {
				answer_arr_count++;
				answer[answer_arr_count] = input[i];
			}
		}
	}

	answer += answer_arr_count;
	cout << answer;
	return 0;
}