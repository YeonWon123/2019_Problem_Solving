// greedy �˰���

#include <iostream>
using namespace std;

int arr[10];

void sum_value(int & sum, int & counts, int N, int K);

int main(void)
{
	int N, K;
	int counts = 0;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// ���������̴ϱ� ���� �� ���� �ִ� �������� ���� ����� �ִ��� �׽�Ʈ
	// ����Լ��� ���鼭 ��� �׽�Ʈ...
	int sum = 0;
	sum_value(sum, counts, N, K);
	
	cout << counts;
	return 0;
}

// ������������ ������ ������, ���� �� ���� ������ ������ ���� ����Ǵ���,
// �ƴϸ� �� �ؿ����� ���� ����� �ִ��� �׽�Ʈ
void sum_value(int & sum, int & counts, int N, int K) {
	//cout << N << endl;
	int i = 0;
	for (i = 0; (sum + arr[N - 1] <= K); i++) {
		sum += arr[N - 1];
		counts++;
	}

	if (N > 1) {
		sum_value(sum, counts, N - 1, K);
	}

	return;
}

/*
// dp �˰���

#include <iostream>
using namespace std;

int arr[10];

void sum_value(int & sum, int & counts, int N, int K);

int main(void)
{
	int N, K;
	int counts = 0;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	// ���������̴ϱ� ���� �� ���� �ִ� �������� ���� ����� �ִ��� �׽�Ʈ
	int sum = 0;
	int min = 99999;
	for (int i = N; i > 0; i--) {
		sum = 0;
		counts = 0;
		sum_value(sum, counts, i, K);
		if (min > counts) min = counts;
	}
	
	cout << min;
	return 0;
}

// ������������ ������ ������, ���� �� ���� ������ ������ ���� ����Ǵ���,
// �ƴϸ� �� �ؿ����� ���� ����� �ִ��� �׽�Ʈ
void sum_value(int & sum, int & counts, int N, int K) {
	//cout << N << endl;
	int i = 0;
	for (i = 0; (sum + arr[N - 1] <= K); i++) {
		sum += arr[N - 1];
		counts++;
	}

	if (N > 1) {
		sum_value(sum, counts, N-1, K);
	}

	return;
}

*/