#include <iostream>
#include <algorithm>
using namespace std;

// 전역 변수 정의
// 입력받은 값을 저장받는 배열, 그 합을 저장하는 배열
// 그리고 이 둘을 탐색하면서 그 값을 저장하는 dp 배열
int input[3001] = { 0, };
int sum_input[3001] = { 0, };
int dp[3001] = { 0, };

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// 입력을 받는다.
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> input[i];
	}

	int truck, helicopter;
	cin >> truck >> helicopter;

	// 정렬
	sort(input + 1, input + 1 + N);

	// 부분합
	for (int i = 1; i <= N; i++) {
	//	cout << input[i] << "\n";
		sum_input[i] = sum_input[i - 1] + input[i];
	}

	// 계산 (DP 이용, 시간복잡도가 O(n^2)이어야 한다.
	// 시간복잡도가 O(n^3)일 경우 시간 초과!
	for (int i = 1; i <= N; i++) {
		int answer;
		// 앞에꺼는 계산이 되어 있는 상태에서,
		// 새 input을 트럭만을 이용하는 경우
		answer = dp[i - 1] + input[i] * truck;
		
		// 헬리콥터를 쓰는 경우
		// 이 경우는 반대로(뒤에서부터) 탐색을 해 보자
		for (int j = i; j > 0; j--) {
			int part_answer = dp[j - 1] + helicopter;
			int mid = (j + i) / 2;

			// 시간 초과를 막아야 한다.
			// for문을 하나 없애서, O(n^3)을 O(n^2)으로 만들자
			/*
			// 전체
			for (int k = j; k <= i; k++) {
				int temp2 = (input[mid] - input[k]) * truck;
				if (temp2 < 0) temp2 *= -1;
				part_answer += temp2;
			}

			// 가운데를 중심으로 왼쪽
			for (int k = j; k < mid; k++) {
				int temp2 = (input[mid] - input[k]) * truck;
				part_answer += temp2;
			}

			// 가운데를 중심으로 오른쪽
			for (int k = mid+1; k <= i; k++) {
				int temp2 = (input[k] - input[mid]) * truck;
				part_answer += temp2;
			}
			*/

			// 부분합을 이용해서 식을 세우고 여기에 적는다.
			int left_sum = (input[mid] * (mid - j + 1) - (sum_input[mid] - sum_input[j-1])) * truck;
			int right_sum = ((sum_input[i] - sum_input[mid - 1]) - (input[mid] * (i - mid + 1))) * truck;
			part_answer += left_sum;
			part_answer += right_sum;
		//	cout << left_sum << "\n";
		//	cout << right_sum << "\n";
			if (answer > part_answer) answer = part_answer;
		//  cout << part_answer << "\n";
		//  cout << answer << "\n";
		}
		dp[i] = answer;
	//  cout << dp[i] << "\n";
	}

	cout << dp[N];
	return 0;
}