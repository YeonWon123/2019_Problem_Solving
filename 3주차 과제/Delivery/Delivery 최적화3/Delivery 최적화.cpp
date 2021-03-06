#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
//#define DEBUG
using namespace std;

// 물품이 있는 지점과, 같은 지점이면 그 개수를 저장하는 구조체 정의
typedef struct polong_count {
	long polong;
	long counts;

} POlong_COUNT;

// 전역 변수
vector<POlong_COUNT> arr;
vector<POlong_COUNT> accu;
long truck, helicopter;
long *dp_answer;

// 함수 원형
bool compare(POlong_COUNT a, POlong_COUNT b);

int main(void)
{
	// 입력을 받는 부분
	long N;
	cin >> N;

	arr.push_back({ 0, 0 });
	long temp;
	long sw = 0;
	long flag;
	for (long i = 1; i <= N; i++) {
		cin >> temp;
		flag = 0;
		for (long j = 1; j < i - sw; j++) {
			if (temp == arr[j].polong) {
				arr[j].counts++;
				flag = 1;
				sw++;
				break;
			}
		}
		if (flag == 0) arr.push_back({ temp, 1 });
	}

	sort(arr.begin() + 1, arr.end(), compare);

	accu.push_back({ 0, 0 });
	accu.push_back({ arr[1].polong * arr[1].counts, arr[1].counts });
	for (long i = 2; i < arr.size(); i++)
		accu.push_back({ arr[i].polong * arr[i].counts + accu[i - 1].polong, arr[i].counts + accu[i - 1].counts });
#ifdef DEBUG
	for (long i = 1; i < arr.size(); i++)
		cout << arr[i].polong << " " << arr[i].counts << "\n";
#endif
	cin >> truck >> helicopter;

	// 계산하는 부분
	// DP를 이용하여 해결해 보자. 우선 배열에 동적 할당
	dp_answer = new long[arr.size()];


	// 앞에서부터 순차적으로 탐색해 나간다.
	// 택배 목적지가 10만 있을 때, 10이랑 20이 있을 때, 10이랑 20이랑 40이 있을 때, ...
	for (long i = 1; i < arr.size(); i++) {
#ifdef DEBUG
		cout << i << "\n";
#endif
		// 변수 초기화
		long mid = 0;
		long mid2 = 0;
		long answer = 1000000000;
		long truck_only = 0;

		// 택배 목적지가 하나만 있다면, 트럭이 좋을까 헬리콥터가 좋을까 판정해서
		// dp_answer 배열의 맨 앞에 저장
		if (i == 1) {
			truck_only = arr[i].polong * arr[i].counts * truck;
			answer = (truck_only > helicopter ? helicopter : truck_only);
			dp_answer[i] = answer;
#ifdef DEBUG
			cout << answer << "\n";
#endif
			continue;
		}

		// 택배 목적지가 두 곳이 있다면
		// 1. 헬리콥터를 전혀 쓰지 않는 경우
		// 2. 헬리콥터를 1대만 쓰는 경우
		// 3. 헬리콥터를 2대 쓰는 경우
		// 그러나 dp를 이용하면 이미 첫 목적지에서의 최적값이 구해졌으니깐
		// 두 번째 목적지에 있는 택배를 어떻게 최적으로 옮기는지만 따지면 된다.

		// 먼저 두 번째 목적지에 있는 택배를 트럭만 이용한 경우
		// 이 때 앞에서 계산한 값(이전 목적지에 있는 택배를 최적으로 계산한 값)을 가져옴
		answer = arr[i].polong * arr[i].counts * truck + dp_answer[i - 1];
#ifdef DEBUG
		cout << answer << "\n";
#endif
		// 헬리콥터를 사용하는 경우를 판정해 보자.
		// 이 경우 뒤에서부터 탐색을 하면 이전에 저장한 최적값을 사용할 수 있다.(DP)
		for (long j = i; j > 0; j--) {
			long part_answer;
			if (j == 1) part_answer = 0;
			else part_answer = dp_answer[j - 1];
			// 헬리콥터를 가장 잘 쓰는 방법은
			// 지점의 중간 지점에 헬리콥터를 내려 두는 것이다.
			// 따라서 중간 지점에 해당하는 좌표를 먼저 구하자.
			// mid = (arr[j].polong + arr[i].polong) / 2;
			mid = arr[(j + i) / 2].polong;
			mid2 = (j + i) / 2;

			// 헬리콥터를 타고 온 다음에 트럭으로 옮기는 거 계산하기
			part_answer += helicopter;
			// mid2 중심으로 왼쪽
			long left = ((mid * (accu[mid2].counts - accu[j - 1].counts)) - (accu[mid2].polong - accu[j - 1].polong)) * truck;
			part_answer += left;

			/*for (long k = j; k < mid2; k++) {
				long temp2 = ((mid - arr[k].polong) * arr[k].counts * truck);
				part_answer += temp2;
			}*/

			long right = ((accu[i].polong - accu[mid2 - 1].polong) - (mid * (accu[i].counts - accu[mid2 + 1].counts))) * truck;
			// mid2 중심으로 오른쪽
			part_answer += right;
			/*
			for (long k = mid2 + 1; k <= i; k++) {
				long temp2 = ((mid - arr[k].polong) * arr[k].counts * truck);
				temp2 = (temp2 > 0) ? temp2 : temp2 * (-1);
				part_answer += temp2;
			}*/
			// 최적의 값(최솟값)인지 비교하기
#ifdef DEBUG
			cout << "left: " << left << "\n";
			cout << "right: " << right << "\n";
			cout << part_answer << "\n";
#endif
			if (answer > part_answer) answer = part_answer;
		}
#ifdef DEBUG
		cout << "dp_answer : " << answer << "\n";
#endif
		// 이 for문이 끝나면 i-1번째 목적지에 있는 택배 + i번째 목적지에 있는 택배까지 합해서
		// 최적값이 나오므로 이 값을 dp_answer[i]에 저장
		dp_answer[i] = answer;
	}

	// 최종 결과값은 dp_answer에서 맨 뒤에 배정됨.
	cout << dp_answer[arr.size() - 1];
	return 0;
}

bool compare(POlong_COUNT a, POlong_COUNT b) {
	// polong가 더 적은 순으로 정렬하기!
	return a.polong < b.polong;
}