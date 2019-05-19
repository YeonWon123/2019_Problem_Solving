// 이분 탐색을 이용하여 푼다.
// T번의 변경 안에 모든 인접한 숫자의 차가 mid 이하이면 true
// 아니라면 false를 반환하는 possible 함수를 구현

// 최소 차를 찾는 과정이므로, 1번이 성립하면 high를 줄이고,
// 성립하지 않으면 low를 늘림

// possible 함수가 성립하고, 
// mid가 기존 차보다 작으면 result 배열을 업데이트

#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100000 + 1;

int N, T;
int A[MAX];
int copyA[MAX];
int result[MAX];

bool possible(int diff)
{
	for (int i = 0; i < N; i++)
		copyA[i] = A[i];

	int cnt = 0;
	// 인접한 오른쪽 체크
	for (int i = 0; i < N-1; i++)
		if (copyA[i + 1] - copyA[i] > diff) {
			cnt += copyA[i + 1] - (copyA[i] + diff);
			copyA[i + 1] = copyA[i] + diff;
		}

	// 인접한 왼쪽 체크
	for (int i = N-1; i > 0; i--) 
		if (copyA[i - 1] - copyA[i] > diff) {
			cnt += copyA[i - 1] - (copyA[i] + diff);
			copyA[i - 1] = copyA[i] + diff;
		}

	// 변경 횟수가 T 이하인가 체크
	if (cnt <= T) 
		return true;
	else 
		return false;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> T;

	for (int i = 0; i < N; i++)
		cin >> A[i];

	int low = 0, high = MAX;
	int minDiff = MAX; // 최소 차
	while (low <= high) {
		int mid = (low + high) / 2;
		if (possible(mid)) {
			for (int i = 0; i < N; i++)
				result[i] = copyA[i];
			high = mid - 1;
		}
		else
			low = mid + 1;
	}
	for (int i = 0; i < N; i++)
		cout << result[i] << " ";
	cout << "\n";
	return 0;
}
