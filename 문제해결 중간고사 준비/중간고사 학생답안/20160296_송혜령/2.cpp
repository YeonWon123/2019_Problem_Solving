#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<stack>

using namespace std;

int N, M;
vector<int> arr(5005);

bool decision(int num)
{
	int groupNum = 0;
	int diff = 0;
	int minNum = arr[0];
	int maxNum = arr[0];

	for (int i = 1; i < N; ++i)
	{
		minNum = min(minNum, arr[i]);
		maxNum = max(maxNum, arr[i]);
		diff = maxNum - minNum;
		if (diff <= num)
		{
			continue;
		}
		else {
			groupNum++;
			minNum = arr[i];
			maxNum = arr[i];
			diff = -1;
		}
	}

	groupNum++;

	if (groupNum <= M)
	{
		return true;
	}

	return false;

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	int s = 1 << 30;
	int e = 0;

	for (int i = 0; i < N; ++i)
	{
		cin >> arr[i];
		s = min(s, arr[i]);
		e = max(arr[i], e);
	}

	e -= s;
	s = 0;

	if (decision(s))
	{
		cout << "0\n";
		return 0;
	}

	while (s + 1 < e)
	{
		int m = (s + e) / 2;

		if (decision(m))
			e = m;
		else
			s = m;
	}

	cout << e;


	return 0;
}