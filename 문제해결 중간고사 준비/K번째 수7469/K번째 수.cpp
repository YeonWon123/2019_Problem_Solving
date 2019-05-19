/*
https://www.acmicpc.net/problem/7469

1. pair<int, int> 배열을 선언하여 first에는 값, second에는 인덱스를 저장합니다.
2. 값을 기준으로 오름차순 정렬을 합니다.
3. 배열을 처음부터 순회하는데 인덱스 즉, second가 start 이상이고 end 이하인 숫자를 발견하면 cnt를 증가시킵니다.
4. cnt가 K가 되면 주어진 범위 내 K 번째 숫자를 찾게 된 것이므로 해당 숫자 즉, first를 출력해주면 됩니다.
https://jaimemin.tistory.com/744
*/

#include <iostream>
#include <algorithm>
using namespace std;

pair<int, int> arr[100001]; // first는 value, second는 index를 의미함
int n, m; // 배열의 크기 : n, 함수 Q를 호출한 횟수 : m

int Kth(int start, int end, int k) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		// second가 index이므로
		if (start <= arr[i].second && arr[i].second <= end)
			cnt++;
		
		// k번째 숫자 반환
		if (cnt == k)
			return arr[i].first;
	}
	return -1;
}

int main(void)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m; // 배열의 크기 : n, 함수 Q를 호출한 횟수 : m

	for (int p = 1; p <= n; p++) {
		cin >> arr[p].first;					// ex) 1 5 2 6 3 7 4
		arr[p].second = p;
	}

	// value를 기준으로 오름차순 정렬
	sort(arr + 1, arr + 1 + n);

	for (int p = 1; p <= m; p++) {
		int i, j, k;	// Q(i, j, k)를 호출할 때 사용한 인자 i,j,k
		cin >> i >> j >> k;					// ex) 2 5 3

		cout << Kth(i, j, k) << "\n";
	}
	return 0;
}