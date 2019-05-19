/*
1. ����

�� ���� �Ϸ��� ��Ģ�� ���� ������ �����Ѵ�.

�� �Ѵ� �ּ��� ������ �˰� �ִ� ������ ��(�ּ��� ������ ������ ���� �𸥴�),
�� ���� ���ΰ��� �ִ�� ���� �� �ִ� ������ �� ���ϱ� ?

��ӵǴ� �˰��� ������ ��������, �ƹ��� ¯���� �������� �ּ��� ������ ���������� ���� �ȿ��Ƿ�,
��� ��츦 ����غ���(������ ����) ���̳��� ���α׷������� Ǯ���.

2. Ǯ��

dp[turn][���� ī��� �� ���� ��][���� ī��� �� ������ ��]���� �迭�� ��ƺ���.

���� ������ ����Ǹ�, ���� ī����� �� �� ���� 0 ~ n-1 ������.
���̳��� ���α׷������� �� �� ��ϵ� dp�迭�� �����ϸ� ����ð��� ���ϵǹǷ� �迭 ũ�⿡ ����� O(2 * n*n)�� Ǯ �� �ְڴ�.

���� ������ Ǯ���� �Լ��� �����غ���.
func(int turn, int x, int y) = ���� turn�̰�, ���� ���� x, ������ ���� y �� �� ���� ���� �� �ִ� �ִ��� ����.

�츮�� ���� ������ʷ� x == y�� ��츦 ������ �� �� �ִ�.
���� ī�尡 �� ���̶� ����, �� ���̿��ٸ� ������ ���ϰ�, ��� ���̶�� "�׳� �׷�����" �ϰ� �Ѿ�� �ȴ�.

���� ������ ����������, �������� ���������� ������ �󸶳� ���� ����غ��� �Ѵ�.

�� ���̿��ٸ� ������ ���� ����� ���� �ڵ尡 �־�� ���װ�,
��� ���̿��ٸ�, ��뵵 �ּ��� �������� �÷����ϱ� ������ �� �� �÷��� �� ���� ������ �ּҷ� �ϴ� �÷��̸� �� ���̴�.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define my 0

int dp[2][1001][1001];
int arr[1001];
int t, n, i;

int func(int turn, int x, int y) {
	if (x == y) {
		if (turn == my)
			return arr[x];
		else
			return 0;
	}

	int& ref = dp[turn][x][y];
	if (ref != -1)
		return ref;

	if (turn == my)
		ref = max(func(turn ^ 1, x + 1, y) + arr[x], func(turn ^ 1, x, y - 1) + arr[y]); // ^ ������(XOR) ��� (0^1 = 1, 1^1 = 0)
	else
		ref = min(func(turn ^ 1, x + 1, y), func(turn ^ 1, x, y - 1));

	return ref;
}

int main(void) {
	scanf("%d", &t);
	while (t--) {
		memset(dp, -1, sizeof(dp));

		scanf("%d", &n);

		for (i = 0; i < n; ++i)
			scanf("%d", &arr[i]);

		printf("%d\n", func(my, 0, n - 1));
	}
}

/*
�з�: Algorithm Game, Dynamic Programming

	Analysis : �ٿ츦 A, ��츦 B��� �ϰڽ��ϴ�.
	������ A�� ���� �����մϴ�.
	���⼭ A�� �ΰ��� �������� �ֽ��ϴ� : ���� ���� ī�带 �������ų� ���� ������ ī�带 �������°�����.
	�ٿ찡 ������ �ִ�ȭ�Ϸ��� ���ʰ� �������� �׻� �����ִ� ���� �� ū ī�带 ���������ұ�� ? 
	��� �̷� �׸����� ���ٹ����δ� �� ������ �ذ��� �� �����ϴ�.
	�������{ 1,2,5,2 }�� 4���� ī�尡 ������� �־����ٰ��սô�.
	Ž�������� �� ������ �ذ��Ѵٸ� 
	A�� ���� �������� 2�� ��������, 
	B�� ���� �������� 5��, 
	�ٽ� A�� ���ʿ����� 2��, 
	B�� ���ʿ��� 1�� �������ϴ�.
	���� A�� �������� = 4, B�� �������� = 6�Դϴ�.
	
	������ ���� A�� ó�� �Ͽ��� 2�� �����ϰ� 1�� �������ٸ�, 
	�ٽ� A�� ���ʿ��� 5�� �������� �������� 6�� ���� �� �ֽ��ϴ�.
	���� Ž�� �˰����� �׻� �����ظ� ���� �� �����.

	Ž�� �˰����� ������ �ʴ´ٸ� ���̳��� ���α׷����� �õ��غ��߰��� ? 
	�켱 ��ȭ���� �������ϴµ� ���� ������ ���� �����߽��ϴ�
	dp[l][r][turn] = ���� ���� ī���� ��ġ l, ������ ī���� ��ġ r�̰� ���� turn �� �����϶�, 
	A(�ٿ�)�� ���� �� �ִ� �ִ� ����.
	turn = 0�� A�� ����, 
	turn = 1�� B�� ���ʶ�� �����ϸ� 
	dp[l][r][0] = max(a[l] + dp[l + 1][r][1], a[r] + dp[l][r - 1][1]), dp[l][r][1] = min(dp[l + 1][r][0], dp[l][r - 1][0]) 
	��� ���� ������ �� �ֽ��ϴ�.���⼭ a[]�� ī���� ���� ��� �ִ� �迭�̿���.
	��ȭ���� ��������� �̰� �������ָ� �˴ϴ�. ���� �޸������̼��� �̿��߾��. �Ʒ� C++ �� Java �ڵ带 �������ּ���.

	Time Complexity : O(TN2), T = test case �� ��, N = �� �׽�Ʈ ���̽��� �־����� ī���� ����.
*/
/*
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

vector<int> a;
int cache[1001][1001][2];
int solve(int l, int r, int turn) {
	if (l > r) return 0;
	int &ret = cache[l][r][turn];
	if (ret != -1) return ret;
	ret = 0;
	if (turn == 1) { // B's turn
		ret = min(solve(l + 1, r, 0), solve(l, r - 1, 0));
	}
	else { // A's turn
		ret = max(a[l] + solve(l + 1, r, 1), a[r] + solve(l, r - 1, 1));
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		a.clear();
		memset(cache, -1, sizeof(cache));
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int no;
			cin >> no;
			a.push_back(no);
		}
		int ans = solve(0, n - 1, 0); // A starts first
		cout << ans << endl;
	}
	return 0;
}
*/

/* Greedy Approach�� Ǭ �ڵ� (����)
But, �� ������ Greedy Approach�� Ǯ �� ����.
���翡 ������ ������ ���������� ������ ������ �� �� ���� �����̴�.
ex) 1 2 5 3 �� ���� ���, ������ �������� 3�� ���� ���� �� ���� ���� ������,
�� ��� ��밡 5�� ������ �� �ְ� �ǹǷ�,
���������δ� ������ 1�� �������� ���� �� ���� �����̱� �����̴�.
�̷� ������ Dynamic Programming�� �̿��ؼ� Ǯ��� �Ѵ�.

#include <iostream>
#include <deque>
using namespace std;

#define DEBUG

deque<int> input;

int a_score = 0;
int b_score = 0;

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;

		int in_n;
		for (int j = 0; j < N; j++) {
			cin >> in_n;
			input.push_back(in_n);
		}


		while (!(input.empty())) {
			if (input.front() > input.back()) {
				a_score += input.front();
#ifdef DEBUG
				cout << "a_score is : " << a_score << "\n";
#endif
				input.pop_front();
			}
			else {
				a_score += input.back();
#ifdef DEBUG
				cout << "a_score is : " << a_score << "\n";
#endif

				input.pop_back();
			}

			if (input.empty()) break;

			if (input.front() > input.back()) {
				b_score += input.front();
#ifdef DEBUG
				cout << "b_score is : " << b_score << "\n";
#endif

				input.pop_front();
			}
			else {
				b_score += input.back();
#ifdef DEBUG
				cout << "b_score is : " << b_score << "\n";
#endif

				input.pop_back();
			}
		}

		cout << a_score << "\n";
	}

	return 0;
}
*/