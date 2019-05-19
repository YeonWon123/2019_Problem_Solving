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
	printf("���� : %lld\n", 1LL * (A.x * B.y + B.x * C.y + C.x * A.y - B.x * A.y - C.x * B.y - A.x * C.y));
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

	// y��ǥ, x��ǥ�� ���� ������ ����
	sort(p, p + n, comp);

	// ���������κ��� ��� ��ġ ���
	for (int i = 1; i < n; i++) {
		p[i].p = p[i].x - p[0].x;
		p[i].q = p[i].y - p[0].y;
	}

	// �ݽð� �������� ����(������ ����)
	sort(p + 1, p + n, comp);

	printf("���ĵ� �� ����!\n");
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", p[i].x, p[i].y);
	}

	stack<int> s;

	// ���ÿ� first, second�� �־��ش�.
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

			// first, second, next�� ��ȸ�� ( > 0 )�̶�� second push
			// ��ȸ��( < 0 )�̶�� ���� while�� ��� �ݺ�
			if (ccw(p[first], p[second], p[next]) > 0) {
				s.push(second);
				break;
			}
		}

		// next push
		s.push(next++);
	}

	printf("���� : %d\n", s.size());
	printf("�� ��� ����\n");
	while (!s.empty()) {
		printf("%d\n", s.top());
		s.pop();
	}
	return 0;
}