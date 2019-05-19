// 모범 답안
/*
트럭은 한번 방문한 도시를 다시 방문하지 않고 1번 도시부터 출발하기 때문에,
1번 도시와 가까운 순으로 박스를 옮겨서 최적의 해를 구할 수 있습니다.

먼저 박스 데이터를 입력 받아서 도착지 순으로, 같다면 출발지 순으로 정렬을 합니다.
gogo[i]에 i번째 마을에서 트럭에 있는 택배의 개수가 저장을 하겠습니다.
left라는 변수는 트럭에 더 담을 수 있는 양을,
maxi라는 변수는 현재 택배를 처리하는 도중 가장 많이 적재된 양을 나타냅니다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct BOX {
	int start, end, count;
	bool operator < (BOX a) {
		if (end != a.end)	return end < a.end;
		else			return start < a.start;
	}
};

int N, C, M;
vector<BOX> v;
vector<int> truck;

int main(void)
{
	cin >> N >> C >> M;
	v.resize(M);
	for (int i = 0; i < M; i++) {
		cin >> v[i].start >> v[i].end >> v[i].count;
	}

	sort(v.begin(), v.end());

	int answer = 0;
	truck.resize(N + 1);
/*
	truck[i]에 i번째 마을에서 트럭에 있는 택배의 개수가 저장을 하겠습니다.
	left라는 변수는 트럭에 더 담을 수 있는 양을,
	maxi라는 변수는 현재 택배를 처리하는 도중 가장 많이 적재된 양을 나타냅니다.
*/

	for (int i = 0; i < M; i++) {
		int maxi = 0;
		for (int j = v[i].start; j < v[i].end; j++) 
			maxi = max(maxi, truck[j]);

		// v[i].count와 C - maxi를 비교해서
		// 더 적은 쪽만큼 담을 수 있음

		/* 참고 
		s에서 택배꾸러미를 받아서 e에서 택배를 내려놓는다고 할때
		s에서부터 e-1까지 해당 택배꾸러미를 계속 들고 있어야 합니다.
		(e는 내려놓는 곳이니까 제외하죠)
		해당 택배꾸러미의 용량을 w라고 하면 s부터 e까지는 택배를
		기본 여유용량 C에서 w만큼 뺀 것입니다.
		즉, 예를 들면 원래 가방용량이 40이고 
		s=2 e=4라고 하고 
		들고다닐 택배꾸러미 용량 w=20이라고 하면 
		(택배를 주고받는 곳이 6개 있다고 합시다)
		1    2    3    4    5    6
		40   20   20   40   40   40 <-이 됩니다. (각 지점에서의 가방의 여유용량)

		그럼 다음번에 1-4구간에서 택배용량이 30만큼 되는걸 나르려고 해도 
		2-3구간의 여유용량이 20밖에 되지 않으므로 20만큼만 나를 수 있습니다.

		그리고 이러한 알고리즘이 가능하게 된 것은 
		처음에 도착지점을 기준으로 오름차순 정렬을 하기 때문입니다.
		(두번째 우선순위로는 출발지점을 기준으로 오름차순 정렬인거죠)
		그니까 이 문제는 도착지점이 1쪽에 가까울수록.. 
		그니까 택배를 어디서 받았든간에(출발지점이 어떻든간에)
		1에 가까운 도착지점에 택배를 내릴 수록 더 많은 택배를 실어날을 수 있습니다.

*/
		int left = min(v[i].count, C - maxi); 
		answer += left;

		for (int j = v[i].start; j < v[i].end; j++) 
			truck[j] += left;
	}
	cout << answer;

	// https://justicehui.github.io/koi/2018/11/15/BOJ8980/
	// https://www.acmicpc.net/board/view/6327
}
