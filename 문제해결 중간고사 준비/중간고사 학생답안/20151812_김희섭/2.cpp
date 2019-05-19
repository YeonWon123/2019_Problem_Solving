#include <iostream>
using namespace std;

int arr[5010];
//int group_sum[5010];

int group_count(int num);
int N, M;

int main()
{
	int i;
	int front = 0, rear = 0, mid;
	cin >> N;
	cin >> M;
	int bound;
	for (i = 1; i <= N; i++)
	{
		cin >> arr[i];
		rear += arr[i];
	}

	bound = rear;

	while (front <= rear)
	{
		mid = (front + rear) / 2;
		
		if (group_count(mid) <= M)
		{
			front = mid + 1;
			if (bound > mid)
			{
				bound = mid;
			}
		}
		else
		{
			rear = mid - 1;
		}
	}
	
	cout << bound << endl;

	return 0;
}

int group_count(int num)
{
	int res = 0;
	int sum = arr[1];
	int i;
	for (i = 2; i <= N; i++)
	{
		sum += arr[i];
		if (sum > num)
		{
			sum = arr[i];
			res++;
		}
	}
	res++;
	return res;
}