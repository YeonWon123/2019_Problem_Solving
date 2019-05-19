// ������ ���� 100�� ��...
// ������ ���̵� 100�� ��...

// dp[]�� ���� ���� �� ������ O(1)���� �����ϱ�
// �� ��� 1���� �迭�� �����ؾ� �Ѵ�..

// int q[2000010]; �̶�� �迭 ����
// 1 2 3 2 1 �̶�� ������ 1 0 2 0 3 0 2 0 1 �� �ٲ㾲�� ����!
// �� ������, �Ӹ������ �߽��� ǥ���ϱ� ����
// q�� ä�������� ��� -> ��Ī �̿�

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