#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// 1. ������ ���� �Է¹ް�, A ������ �ε����� ��� visited �迭�� ǥ��
// 2. LIS �Լ��� ���� ���� �� �κ� ���� ������ ���̸� ���Ѵ�.
//		-> answer �迭�� {�ε���, ����� B ������ �ε���}�� ǥ���� �ش�.
// 3. N - (2������ ���� ����)�� ����� �ش�.
// 4. �� �ε����� ��ġ�� A ������ �ε����� ���ϰ�, �ش� �ε����� ������ �Ǿ��ִ� �����̹Ƿ�
//	visited �迭���� ���ش�.
// 5. 4������ �Ϸ��ϸ�, visited �迭�� ǥ�õǾ��ִ� �ε����� �ʱ⿡�� ����������,
// LIS�� ���� ������ ������ �ε����̹Ƿ� ����� �� �ش�.

const int MAX = 500000 + 1;

int N;
pair<int, int> connect[MAX];
pair<int, int> answer[MAX]; // �ε���, ����� B ������ �ε���
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
	// idx�� 0���� ���������Ƿ�
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
	// result�� �����ϴ� ��
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




