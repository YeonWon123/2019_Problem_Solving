// 100 이하의 9개의 수 중 7개를 뽑아서 그 합이 100이 되면,
// 그 수들 7개를 오름차순으로 출력

#include <iostream>
#include <algorithm>
#define SIZE 9
using namespace std;

int input[SIZE];
void sum_7_number(int* input, int stop1, int stop2);

int main()
{
	for (int i = 0; i < SIZE; i++)
	{
		cin >> input[i];
	}
	
	// 오름차순으로 정렬
	sort(input, input+9);
	
	int stop1 = 0;
	int stop2 = 1;

	// 9개의 수들 중 두 개의 수를 제외한 나머지 수들을 더해 봄
	// 더하다가, 100을 넘으면 패스, 모두 더했을때 100 미만일 경우 패스
	for (stop1 = 0; stop1 < SIZE; stop1++)
		for (stop2 = 0; stop2 < SIZE; stop2++)
			sum_7_number(input, stop1, stop2);
}

void sum_7_number(int* input, int stop1, int stop2)
{
	int sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (i != stop1 && i != stop2)
		{
			sum = sum + input[i];
		}

		if (sum > 100)
			return;
	}

	if (sum < 100) return;
	else 
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i != stop1 && i != stop2)
			{
				cout << input[i] << "\n";
			}
		}
		exit(0);
	}
}