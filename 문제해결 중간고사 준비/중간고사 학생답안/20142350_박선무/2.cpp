#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>

using namespace std;

//vector<char> moo;

int N, M;
vector <int> ary;


int main()
{
	cin >> N >> M;
	int m = 999999;
	int mx = 0;
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		int in; cin >> in; ary.push_back(in);
		m = min(m, in);
		mx = max(mx, in);
		sum += in;
	}
	if (M == 1)
	{
		printf("%d\n", mx - m);
		return 0;
	}
	else if (m == mx)
	{
		printf("0\n");
		return 0;
	}
	int left = m;
	int right = sum;
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;

		//printf("%d\n", mid);
		int group_sum = 0;
		int group_cnt = 1;

		int mm = 99999;
		int mx = 0;
		for (int i = 0; i < N; i++)
		{
			mm = min(mm, ary[i]);
			mx = max(mx, ary[i]);
			int diff = mx - mm;
			if (diff > mid)
			{
				mm = ary[i];
				mx = ary[i];
				group_cnt++;
			}
		}
		//printf("group = %d\n", group_cnt);
		if (group_cnt > M)//좀더 높여야함
		{
			left = mid + 1;
			mid = left;
		}
		else//그렇지않다
		{
			right = mid - 1;
		}
	}
	cout << mid << endl;
	//cout << "hello world" << endl;
}
