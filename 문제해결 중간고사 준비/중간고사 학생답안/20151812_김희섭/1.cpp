#include <iostream>
using namespace std;

char space[1000000010];

void divide(int start,int end, int len,int idx);

int main()
{
	int N;
	cin >> N;
	int cnt = 3;
	int idx = 0;
	while (cnt <= N)
	{
		cnt = cnt + cnt + 3 + (idx+1);
		idx++;
	}

	//구해야 할 길이가 나옴
	divide(0, cnt - 1, cnt,idx);

	cout << space[N-1] << endl;

	return 0;
}

void divide(int start, int end, int len, int idx)
{
	int temp_cnt = (len - (idx+3)) / 2;
	int i;
	if (len >= 3)
	{
		divide(start, end- temp_cnt + idx + 3, temp_cnt, idx - 1);
		space[start + temp_cnt] = 'm';
		for (i = 1; i <= idx + 2; i++)
		{
			space[start + temp_cnt+i] = 'o';
		}
		divide(start + temp_cnt+idx+3, end, temp_cnt, idx - 1);
	}

}