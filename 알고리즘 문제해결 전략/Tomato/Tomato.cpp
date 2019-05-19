#include <iostream>
using namespace std;

int day_total = 0;

int zero = 0;
int one = 0;

void check(int** W, int i, int j, int length, int width, int day);


int main()
{
	int width;  // 가로 칸의 개수
	int length; // 세로 칸의 개수
	
	cin >> width >> length;

	// 동적 할당
	int **W = new int*[length];
	for(int i = 0; i < length; i++)
		W[i] = new int[width];

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cin >> W[i][j];

			switch (W[i][j])
			{
			case 0:
				zero++;
				break;
			case 1:
				one++;
				break;
			}
		}
	}

	int one_zero_sum = one + zero;

	int day = 0;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (W[i][j] == 1)
			{
				check(W, i, j, length, width, day);
			}
		}
	}

	if (one == one_zero_sum)
		cout << day_total;
	else
		cout << -1;

	return 0;
}

void check(int** W, int i, int j, int length, int width, int day)
{
	int left = 0;
	int right = 0;
	int up = 0;
	int down = 0;

	if (i != 0 && W[i - 1][j] == 0)
	{
		W[i - 1][j] = 1;
		one++;
		zero--;
		left = 1;
	}
	if (i != length-1 && W[i + 1][j] == 0)
	{
		W[i + 1][j] = 1;
		one++;
		zero--;
		right = 1;
	}
	if (j != 0 && W[i][j - 1] == 0)
	{
		W[i][j - 1] = 1;
		one++;
		zero--;
		up = 1;
	}

	if (j != length-1 && W[i][j + 1] == 0)
	{
		W[i][j + 1] = 1;
		one++;
		zero--;
		down = 1;
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << W[i][j] << " ";
		}
		cout << "\n";
	}

	cout << day << " 번째" << endl << endl;

	if(left == 1) check(W, i-1, j, length, width, day+1);
	if(right == 1) check(W, i+1, j, length, width, day+1);
	if(up == 1) check(W, i, j-1, length, width, day+1);
	if(down == 1) check(W, i, j+1, length, width, day+1);

	if (day_total < day)
		day_total = day;
}