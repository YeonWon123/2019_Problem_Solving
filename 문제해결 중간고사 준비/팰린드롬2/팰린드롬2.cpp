// 쿼리의 수도 100만 개...
// 수열의 길이도 100만 개...

// dp[]를 먼저 구한 후 쿼리에 O(1)만에 응답하기
// 이 경우 1차원 배열로 구현해야 한다..

// int q[2000010]; 이라는 배열 선언
// 1 2 3 2 1 이라는 수열을 1 0 2 0 3 0 2 0 1 로 바꿔쓰기 때문!
// 그 이유는, 팰린드롬의 중심을 표현하기 위함
// q를 채워나가는 방법 -> 대칭 이용

// https://softgoorm.tistory.com/41

#include <stdio.h>
#include <algorithm>
using namespace std;

int arr[2000010];
int q[2000010];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", arr + 2 * i);
	}

	n <<= 1;
	int maxR = 0, j = 0;

	for (int i = 0; i <= n; i++) {
		if (maxR > i) q[i] = min(q[2 * j - i], maxR - i);

		while (i + q[i] < n && i - q[i] > 0 && arr[i + q[i] + 1] == arr[i - q[i] - 1])
			q[i]++;

		if (maxR < i + q[i]) {
			maxR = i + q[i];
			j = i;
		}
	}

	int qn;
	scanf("%d", &qn);

	while (qn--) {
		int L, R;
		scanf("%d%d", &L, &R);

		if (q[L + R - 2] < R - L) puts("0");
		else puts("1");
	}

	return 0;
}