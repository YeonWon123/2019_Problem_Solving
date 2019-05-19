/*
https://www.acmicpc.net/problem/7469

1. pair<int, int> �迭�� �����Ͽ� first���� ��, second���� �ε����� �����մϴ�.
2. ���� �������� �������� ������ �մϴ�.
3. �迭�� ó������ ��ȸ�ϴµ� �ε��� ��, second�� start �̻��̰� end ������ ���ڸ� �߰��ϸ� cnt�� ������ŵ�ϴ�.
4. cnt�� K�� �Ǹ� �־��� ���� �� K ��° ���ڸ� ã�� �� ���̹Ƿ� �ش� ���� ��, first�� ������ָ� �˴ϴ�.
https://jaimemin.tistory.com/744
*/

#include <iostream>
#include <algorithm>
using namespace std;

pair<int, int> arr[100001]; // first�� value, second�� index�� �ǹ���
int n, m; // �迭�� ũ�� : n, �Լ� Q�� ȣ���� Ƚ�� : m

int Kth(int start, int end, int k) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		// second�� index�̹Ƿ�
		if (start <= arr[i].second && arr[i].second <= end)
			cnt++;
		
		// k��° ���� ��ȯ
		if (cnt == k)
			return arr[i].first;
	}
	return -1;
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m; // �迭�� ũ�� : n, �Լ� Q�� ȣ���� Ƚ�� : m

	for (int p = 1; p <= n; p++) {
		cin >> arr[p].first;					// ex) 1 5 2 6 3 7 4
		arr[p].second = p;
	}

	// value�� �������� �������� ����
	sort(arr + 1, arr + 1 + n);

	for (int p = 1; p <= m; p++) {
		int i, j, k;	// Q(i, j, k)�� ȣ���� �� ����� ���� i,j,k
		cin >> i >> j >> k;					// ex) 2 5 3

		cout << Kth(i, j, k) << "\n";
	}
	return 0;
}