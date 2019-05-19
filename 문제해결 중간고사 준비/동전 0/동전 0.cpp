// greedy 알고리즘

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

	// 오름차순이니깐 먼저 맨 끝에 있는 동전으로 값을 만들수 있는지 테스트
	// 재귀함수를 돌면서 계속 테스트...
	int sum = 0;
	sum_value(sum, counts, N, K);
	
	cout << counts;
	return 0;
}

// 오름차순으로 동전이 들어오니, 먼저 맨 끝에 것으로 동전의 합이 도출되는지,
// 아니면 그 밑에껄로 값을 만들수 있는지 테스트
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
// dp 알고리즘

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

	// 오름차순이니깐 먼저 맨 끝에 있는 동전으로 값을 만들수 있는지 테스트
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

// 오름차순으로 동전이 들어오니, 먼저 맨 끝에 것으로 동전의 합이 도출되는지,
// 아니면 그 밑에껄로 값을 만들수 있는지 테스트
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