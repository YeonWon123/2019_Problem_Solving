#include <iostream>
#include <algorithm>
using namespace std;

typedef struct BOX {
	int start;		// �ڽ��� ������ ������ȣ
	int end;		// �ڽ��� �޴� ������ȣ
	int count;		// ������ �ڽ� ����
} box;

bool comp(box p1, box p2) {
	// �޴� ������ ���� ������ ���� ����
	if (p1.end != p2.end)
		return p1.end < p2.end;
	// �޴� ������ ������ ������ ������ ���� ������ ���� ����
	else
		return p1.start < p2.start;
}

box pq[10001];		// �ڽ� ����
int truck[10001] = { 0, };		// Ʈ�� ����

int main()
{
	// �Է¹ޱ�
	int N, C;		// N�� ���� ��, C�� Ʈ���� �뷮
	cin >> N >> C;

	int M;
	cin >> M;		// ������ �ڽ� ������ ����
	for (int i = 1; i <= M; i++) {
		cin >> pq[i].start >> pq[i].end >> pq[i].count;
	}

	sort(pq + 1, pq + 1 + M, comp);

	// Ž������� ����

	int answer = 0;		// ����, ����� �ڽ��� ����


	// �� �ڽ����� �������ش�.
	for (int i = 1; i <= M; i++) {
		int maxi = 0;
		// ���� start ~ end ���̿� �ű� �� �ִ� �ڽ��� �뷮�� ���Ѵ�.
		for (int j = pq[i].start; j < pq[i].end; j++)
			maxi = max(maxi, truck[j]);

		// start ~ end ������ �ڽ��� �뷮�̶� pq[i].count �� ���� ���� �ű� �� �ִ�.
		int left = min(pq[i].count, C - maxi);
		answer += left;

		for (int j = pq[i].start; j < pq[i].end; j++)
			truck[j] += left;
	}

	cout << answer;
	return 0;
}