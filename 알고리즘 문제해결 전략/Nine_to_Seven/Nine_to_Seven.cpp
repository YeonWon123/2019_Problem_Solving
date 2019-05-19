// 100 ������ 9���� �� �� 7���� �̾Ƽ� �� ���� 100�� �Ǹ�,
// �� ���� 7���� ������������ ���

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
	
	// ������������ ����
	sort(input, input+9);
	
	int stop1 = 0;
	int stop2 = 1;

	// 9���� ���� �� �� ���� ���� ������ ������ ������ ���� ��
	// ���ϴٰ�, 100�� ������ �н�, ��� �������� 100 �̸��� ��� �н�
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