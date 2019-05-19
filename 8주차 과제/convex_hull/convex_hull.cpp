#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>

#define MAX 100002

using namespace std;

typedef long long ll;

struct INFO {
	int x, y;
	int p, q;
	INFO(int x1 = 0, int y1 = 0) : x(x1), y(y1), p(1), q(0) {}
};

bool comp(const INFO &A, const INFO &B) {
	if (1LL * A.q * B.p != 1LL * A.p*B.q)
		return 1LL * A.q * B.p < 1LL * A.p*B.q;

	if (A.y != B.y)
		return A.y < B.y;

	return A.x < B.x;
}

ll ccw(const INFO &A, const INFO &B, const INFO &C) {
	printf("넓이 : %lld\n", 1LL * (A.x * B.y + B.x * C.y + C.x * A.y - B.x * A.y - C.x * B.y - A.x * C.y));
	return 1LL * (A.x * B.y + B.x * C.y + C.x * A.y - B.x * A.y - C.x * B.y - A.x * C.y);
}

INFO p[MAX];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);

		p[i] = INFO(x, y);
	}

	// y좌표, x좌표가 작은 순으로 정렬
	sort(p, p + n, comp);

	// 기준점으로부터 상대 위치 계산
	for (int i = 1; i < n; i++) {
		p[i].p = p[i].x - p[0].x;
		p[i].q = p[i].y - p[0].y;
	}

	// 반시계 방향으로 정렬(기준점 제외)
	sort(p + 1, p + n, comp);

	printf("정렬된 점 보기!\n");
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", p[i].x, p[i].y);
	}

	stack<int> s;

	// 스택에 first, second를 넣어준다.
	s.push(0);
	s.push(1);

	int next = 2;

	while (next < n) {
		printf("next : %d\n", next);
		while (s.size() >= 2) {
			int first, second;
			second = s.top();
			s.pop();
			first = s.top();

			// first, second, next가 좌회전 ( > 0 )이라면 second push
			// 우회전( < 0 )이라면 위의 while문 계속 반복
			if (ccw(p[first], p[second], p[next]) > 0) {
				s.push(second);
				break;
			}
		}

		// next push
		s.push(next++);
	}

	printf("개수 : %d\n", s.size());
	printf("점 출력 시작\n");
	while (!s.empty()) {
		printf("%d\n", s.top());
		s.pop();
	}
	return 0;
}