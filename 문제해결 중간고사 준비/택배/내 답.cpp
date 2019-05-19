#include <iostream>
#include <algorithm>
using namespace std;

typedef struct BOX {
	int start;		// 박스를 보내는 마을번호
	int end;		// 박스를 받는 마을번호
	int count;		// 보내는 박스 개수
} box;

bool comp(box p1, box p2) {
	// 받는 마을이 낮은 순으로 먼저 정렬
	if (p1.end != p2.end)
		return p1.end < p2.end;
	// 받는 마을이 같으면 보내는 마을이 낮은 순으로 먼저 정렬
	else
		return p1.start < p2.start;
}

box pq[10001];		// 박스 정보
int truck[10001] = { 0, };		// 트럭 정보

int main()
{
	// 입력받기
	int N, C;		// N은 마을 수, C는 트럭의 용량
	cin >> N >> C;

	int M;
	cin >> M;		// 보내는 박스 정보의 개수
	for (int i = 1; i <= M; i++) {
		cin >> pq[i].start >> pq[i].end >> pq[i].count;
	}

	sort(pq + 1, pq + 1 + M, comp);

	// 탐욕법으로 접근

	int answer = 0;		// 정답, 배송한 박스의 개수


	// 각 박스마다 수행해준다.
	for (int i = 1; i <= M; i++) {
		int maxi = 0;
		// 먼저 start ~ end 사이에 옮길 수 있는 박스의 용량을 구한다.
		for (int j = pq[i].start; j < pq[i].end; j++)
			maxi = max(maxi, truck[j]);

		// start ~ end 사이의 박스의 용량이랑 pq[i].count 중 적은 값을 옮길 수 있다.
		int left = min(pq[i].count, C - maxi);
		answer += left;

		for (int j = pq[i].start; j < pq[i].end; j++)
			truck[j] += left;
	}

	cout << answer;
	return 0;
}