// https://www.acmicpc.net/problem/1300

#include <iostream>
using namespace std;

int main(void)
{
	// 입력받기
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, K;
	cin >> N >> K;

	// Parametric Search 이용
	// 어떠한 기준값을 정했을 때, 배열에서 1부터 mid까지의 개수를 O(N)만에 알아낼 수 있으니,
	// 이 기준값을 이분 탐색으로 돌리면 O(N*logN)만에 해결할 수 있다.
	int start = 1, end = K;
	while (start <= end) {
		int mid = (start + end) / 2;
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			if ((mid / i) > N)
				cnt += N;
			else
				cnt += mid / i;
		}
		if (cnt < K) start = mid + 1;
		else end = mid - 1;
	}
	cout << start;
	return 0;
}

/*

0 1 2 3 4... 10^5(까지 가능)
1 1 2 3 4
2 2 4 6 8
3 3 6 9 12
4 4 8 12 16
.
.
.
10^5(까지 가능)

-> 1 2 2 3 3 4 4 4 6 6 8 8 9 12 12 16

풀이
임의의 숫자 m을 골라서 K번째 숫자인지 판단해보자!
그 임의의 숫자 m은 무려 O(log K)에! 무려 이분 탐색으로 찾아보자!
그렇다면 떠오르는 질문, m 보다 작은 숫자의 개수를 어떻게 하면 빠르게 구할 수 있을까?
A[i][j]에서, i행에 속한 숫자들은 i*j이므로 모두 i의 배수이다.
그러므로 min(mid/i, N)이 i번째 행에서 mid보다 작은(= 임의의 m보다 작은) 숫자들의 개수가 된다.
eg. N = 1000인 경우, 첫 mid가 1000*1000/2 = 50만이 되는데, 50만/i가 N을 넘어갈 수 있으므로 min(mid/i, N)을 해준다.

조금 더 쉽게 쓰자면, i행의 숫자들은 i*1, i*2, i*3, ..., i*N으로 구성되어 있다.
i행의 숫자들 중 m보다 작거나 같은 숫자는 (i*j <= m)를 만족하는 j의 개수이고
이는 i*1, i*2, ..., i*j이므로, m/i와 같은 값이 된다.

각 O(log K)에 대해, 1부터 N까지 모든 i행에 대해 m/i를 수행해주어야 하므로
총 시간 복잡도는 O(NlogK)가 된다

http://wookje.dance/2017/02/20/boj-1300-K%EB%B2%88%EC%A7%B8-%EC%88%98/
*/