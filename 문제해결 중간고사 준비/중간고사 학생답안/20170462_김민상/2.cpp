#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> vc;

bool possible(int mid, int k)
{
	int n = vc.size();
	int cnt = 0;
	int l, r;
	for (int i = 0; i < n; i++)
	{
		if(!i)l = r = vc[i];
		else
		{
			l = min(l, vc[i]);
			r = max(r, vc[i]);
			if (r - l <= mid)
				continue;
			l = r = vc[i];
			cnt++;
		}
	}
	return cnt + 1 <= k;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	int l, r;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		vc.push_back(x);
		if(!i)l = r = x;
		l = min(l, x);
		r = max(r, x);
	}
	r = r - l + 1;
	l = 0;
	while (l < r)
	{
		int mid = (l + r) / 2;
		if (possible(mid, k))
			r = mid;
		else
			l = mid + 1;
	}

	cout << r;
	return 0;
}