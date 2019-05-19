https://www.acmicpc.net/problem/1931

// 주어진 시간이 2^31 - 1이므로, Greedy하게 풀어야 한다.
// DP로 풀 시 시간초과가 나며 Greedy하게 풀 수 있는 문제이다.

/*
DP로 문제에 접근하려고 했다가 주어진 시간이 2 ^ 31 - 1 인 것을 보고 그리디로 접근했다.

회의의 시작 시간과 끝나는 시간이 주어질 때
어떻게 정렬을 해서 문제를 풀어야 가장 최적의 답으로 구하는 것인지가 중요한 문제이다.

회의 시간을 정렬할 때 가장 많은 회의를 선택하도록 정렬하는 방법은
끝나는 시간을 기준으로 정렬을 하는 것이다.
가장 빨리 끝나는 회의를 먼저 고려한다면 그만큼 뒤에 남아있는 회의가 많기 때문이다.

문제를 풀 때 생각한 자료구조는 우선순위 큐이다.
구조체를 통해 끝나는 시간이 빠른 순서대로 리턴할 수 있도록 하고
이 구조체를 큐에 담아서 끝나는 시간이 빠른 회의부터 앞에 올 수 있도록 하는 것이다.

여기서 2가지 실수 때문에 문제를 푸는 데 굉장히 힘들었다...
문제의 조건이 조금 애매하다 보니 반례를 찾는 게 쉽지 않았다.

첫 번째로 시작 시간과 끝나는 시간이 여러 개 일 때 해당하는 회의를 모두 선택해 주는 것이다.

예를 들어 회의가 (1, 3) / (3, 3) / (3, 3)이 있다고 생각해보자.
처음에 (1, 1)과 (3, 3)을 고려하여 2가지를 구했는데,
(3, 3)이 두 개 있을 때는 하나만 해당된다고 가정하고 중복을 없애버렸다.
그런데 이 문제에서는 시작 시간과 끝나는 시간이 같은 경우가 여러 개 일 때는
동시에 회의를 모두 할 수 있다고 생각하고 풀어야 한다.

두 번째로 종료 시간이 같을 때는 시작 시간이 빠른 순서대로 정렬해야 한다.
예를 들어 회의가 (3, 3) / (2, 3) / (3, 3)이 있다고 생각해보자.
위의 3개의 회의 시간의 종료 시간이 모두 같을 때, 최적의 해답은(2, 3) (3, 3) (3, 3)으로 총 3가지가 된다.

그러나 시작 시간 순서대로 정렬하지 않는다면
(3, 3) 다음에(2, 3)의 회의 시간이 올 수가 없기 때문에 2가지 경우밖에 답이 될 수 없다.

그리디에서 최적의 해답이 되기 위한 조건을 찾는 것도 중요하지만 항상 반례를 생각해서 안되는 경우를 생각하는 것도 중요한 것 같다.
결론은 문제를 많이 풀자!!
*/


#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct TIME {
	int start;
	int end;
	TIME(int start, int end) : start(start), end(end) {};
} time;

bool operator<(time p1, time p2) {
	if (p1.end != p2.end)		// 종료 시간이 다르면
		return p1.end > p2.end;	// 종료 시간이 빠른 순서대로 ( < 니깐 반대로)
	else
		return p1.start > p2.start; // 종료 시간이 같으면 시작 시간이 빠른 순서대로 ( < 니깐 반대로)
}

priority_queue<time> pq;

int main(void)
{
	// 입력받기
	int N;
	cin >> N;

	int start_time, end_time; // 시작 시간, 종료 시간
	
	for (int i = 1; i <= N; i++) {
		cin >> start_time >> end_time;
		pq.push(time(start_time, end_time));
	}
#ifdef DEBUG
	cout << "출력";
	for (int i = 0; i < N; i++) {
		cout << pq.top().start << " " << pq.top().end << endl;
		pq.pop();
	}
#endif
	// 탐욕법으로 접근

	int ans = 0;
	end_time = -1;

	while (!pq.empty()) {
		time s = pq.top();
		pq.pop();
		
		if (s.start >= end_time) {	// 시작 시간과 끝나는 시간이 같은 경우가 여러 개 일 때는
									// 동시에 회의를 모두 할 수 있다고 생각하고 풀어야 한다.
			ans++;
			end_time = s.end;
		}
	}

	cout << ans << endl;
	return 0;
}
