#include <iostream>
using namespace std;

int arr[1001]; // 1 ~ 1000까지 사용할 것
int P[1001]; // LIS에서의 위치를 나타냄
int LIS[1001] = { 0, }; // 1 ~ 1000까지 사용하되, LIS[0] = 99999로 초기화
int LIS_count = 0; // LIS안에 몇개있는지 보기

int main(void)
{
	// 입력받기
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}

	// 수열 A의 가장 긴 감소하는 부분 수열의 길이 출력
	// 단, 같은 숫자는 겹칠 수 없음
	LIS[0] = 99999;
	for (int i = 1; i <= N; i++) {
		int sw = 0;
		for (int j = 0; j <= LIS_count; j++) {

			if (arr[i] >= LIS[j]) {
				LIS[j] = arr[i];
				P[i] = j;
				sw = 1;
				break;
			}

		}
		if (sw == 0) {
			LIS_count++;
			LIS[LIS_count] = arr[i];
			P[i] = LIS_count;
		}
	}
	
	for (int i = 1; i <= N; i++)
		cout << P[i] << " ";
	cout << "\n";

	for (int i = 1; i <= LIS_count; i++)
		cout << LIS[i] << " ";
	cout << "\n";
	cout << LIS_count;
	return 0;
}