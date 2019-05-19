/*
1. 접근

두 명이 일련의 규칙에 따라 게임을 진행한다.

단 둘다 최선의 전략을 알고 있다 가정할 때(최선의 전략이 뭔지는 아직 모른다),
선 턴인 주인공이 최대로 얻을 수 있는 점수는 몇 점일까 ?

계속되는 알고리즘 게임의 일종으로, 아무리 짱구를 굴려봐도 최선의 전략이 무엇일지는 감이 안오므로,
모든 경우를 계산해보는(하지만 빠른) 다이나믹 프로그래밍으로 풀어보자.

2. 풀이

dp[turn][남은 카드들 중 왼쪽 끝][남은 카드들 중 오른쪽 끝]으로 배열을 잡아보자.

턴은 번갈아 진행되며, 남은 카드들의 양 쪽 끝은 0 ~ n-1 까지다.
다이나믹 프로그래밍으로 한 번 기록된 dp배열에 접근하면 상수시간에 리턴되므로 배열 크기에 비례한 O(2 * n*n)에 풀 수 있겠다.

이제 문제를 풀어줄 함수를 정의해보자.
func(int turn, int x, int y) = 턴이 turn이고, 왼쪽 끝은 x, 오른쪽 끝은 y 일 때 내가 얻을 수 있는 최대의 점수.

우리는 이제 기저사례로 x == y인 경우를 생각해 볼 수 있다.
남은 카드가 한 장이란 말로, 내 턴이였다면 점수를 취하고, 상대 턴이라면 "그냥 그랬구나" 하고 넘어가면 된다.

이제 왼쪽을 가져가든지, 오른쪽을 가져가든지 점수가 얼마나 될지 계산해봐야 한다.

내 턴이였다면 실제로 점수 계산을 위한 코드가 있어야 할테고,
상대 턴이였다면, 상대도 최선의 전략으로 플레이하기 때문에 양 쪽 플레이 중 나의 점수를 최소로 하는 플레이를 할 것이다.
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
		ref = max(func(turn ^ 1, x + 1, y) + arr[x], func(turn ^ 1, x, y - 1) + arr[y]); // ^ 연산자(XOR) 사용 (0^1 = 1, 1^1 = 0)
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
분류: Algorithm Game, Dynamic Programming

	Analysis : 근우를 A, 명우를 B라고 하겠습니다.
	게임은 A가 먼저 시작합니다.
	여기서 A는 두가지 선택지가 있습니다 : 제일 왼쪽 카드를 가져가거나 제일 오른쪽 카드를 가져가는것이죠.
	근우가 점수를 최대화하려면 왼쪽과 오른쪽중 항상 적혀있는 값이 더 큰 카드를 가져가야할까요 ? 
	사실 이런 그리디한 접근법으로는 이 문제를 해결할 수 없습니다.
	예를들어{ 1,2,5,2 }의 4장의 카드가 순서대로 주어졌다고합시다.
	탐욕적으로 이 문제를 해결한다면 
	A는 제일 오른쪽의 2를 가져가고, 
	B는 제일 오른쪽의 5를, 
	다시 A의 차례에서는 2를, 
	B의 차례에서 1을 가져갑니다.
	따라서 A의 최종점수 = 4, B의 최종점수 = 6입니다.
	
	하지만 만약 A가 처음 턴에서 2를 포기하고 1을 가져간다면, 
	다시 A의 차례에서 5를 가져가서 최종점수 6을 얻을 수 있습니다.
	따라서 탐욕 알고리즘은 항상 최적해를 구할 수 없어요.

	탐욕 알고리즘이 먹히지 않는다면 다이나믹 프로그래밍을 시도해봐야겠죠 ? 
	우선 점화식을 세워야하는데 저는 다음과 같이 생각했습니다
	dp[l][r][turn] = 가장 왼쪽 카드의 위치 l, 오른쪽 카드의 위치 r이고 현재 turn 의 차례일때, 
	A(근우)가 얻을 수 있는 최대 점수.
	turn = 0은 A의 차례, 
	turn = 1은 B의 차례라고 정의하면 
	dp[l][r][0] = max(a[l] + dp[l + 1][r][1], a[r] + dp[l][r - 1][1]), dp[l][r][1] = min(dp[l + 1][r][0], dp[l][r - 1][0]) 
	라는 식을 유도할 수 있습니다.여기서 a[]는 카드의 값을 담고 있는 배열이에요.
	점화식을 만들었으니 이걸 구현해주면 됩니다. 저는 메모이제이션을 이용했어요. 아래 C++ 와 Java 코드를 참고해주세요.

	Time Complexity : O(TN2), T = test case 의 수, N = 각 테스트 케이스에 주어지는 카드의 개수.
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

/* Greedy Approach로 푼 코드 (오답)
But, 이 문제는 Greedy Approach로 풀 수 없다.
현재에 최적인 선택이 최종적으로 최적인 선택이 될 수 없기 때문이다.
ex) 1 2 5 3 이 있을 경우, 당장은 오른쪽의 3을 고르는 것이 더 나을 수도 있지만,
그 경우 상대가 5를 가져갈 수 있게 되므로,
최종적으로는 왼쪽의 1을 가져가는 것이 더 나은 선택이기 때문이다.
이런 문제는 Dynamic Programming을 이용해서 풀어야 한다.

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