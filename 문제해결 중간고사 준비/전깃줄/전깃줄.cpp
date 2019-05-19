#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// 1. 연결한 줄을 입력받고, A 전봇대 인덱스를 모두 visited 배열에 표시
// 2. LIS 함수를 통해 가장 긴 부분 증가 수열의 길이를 구한다.
//		-> answer 배열에 {인덱스, 연결된 B 전봇대 인덱스}를 표시해 준다.
// 3. N - (2번에서 구한 길이)를 출력해 준다.
// 4. 각 인덱스에 위치한 A 전봇대 인덱스를 구하고, 해당 인덱스는 연결이 되어있는 상태이므로
//	visited 배열에서 빼준다.
// 5. 4번까지 완료하면, visited 배열에 표시되어있는 인덱스는 초기에는 연결했지만,
// LIS를 위해 연결을 해제한 인덱스이므로 출력을 해 준다.

const int MAX = 500000 + 1;

int N;
pair<int, int> connect[MAX];
pair<int, int> answer[MAX]; // 인덱스, 연결된 B 전봇대 인덱스
int cache[MAX];
bool visited[MAX];
stack<int> s;

int LIS(void) {
	int idx = 0;
	int length = 0;
	cache[idx] = connect[0].second;
	answer[0] = { 0, connect[0].first };

	for (int i = 1; i < N; i++) {
		if (cache[idx] < connect[i].second) {
			cache[++idx] = connect[i].second;
			answer[i] = { idx, connect[i].first };
		}
		else {
			int idx2 = lower_bound(cache, cache + idx, connect[i].second) - cache;
			cache[idx2] = connect[i].second;
			answer[i] = { idx2, connect[i].first };
		}
	}
	// idx가 0부터 시작했으므로
	return idx + 1;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> connect[i].first >> connect[i].second;
		visited[connect[i].first] = true;
	}

	sort(connect, connect + N);

	int result = LIS();
	// result는 존재하는 줄
	cout << N - result << "\n";

	int num = result - 1;
	for (int i = N - 1; i >= 0; i--) {
		if (answer[i].first == num) {
			s.push(answer[i].second);
			num--;
		}
	}
	
	while (!s.empty()) {
		visited[s.top()] = false;
		s.pop();
	}
	
	for (int i = 0; i < MAX; i++)
		if (visited[i])
			cout << i << "\n";

	return 0;
}




