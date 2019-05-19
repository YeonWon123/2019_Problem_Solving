#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int getLeftCnt(deque<int> &dq, int target)
{
	int cnt = 0;
	while (target != dq.front()) {
		dq.push_back(dq.front());
		dq.pop_front();
		cnt++;
	}
	return cnt;
}

int getRightCnt(deque<int> dq, int target)
{
	int cnt = 0;
	while (target != dq.front()) {
		dq.push_front(dq.back());
		dq.pop_back();
		cnt++;
	}
	return cnt;
}

int main()
{
	int n, m;
	int target, ans = 0;
	deque<int> dq;

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		dq.push_back(i);

	for (int i = 0; i < m; i++)
	{
		cin >> target;
		ans += min(getLeftCnt(dq, target), getRightCnt(dq, target));
		dq.pop_front();
	}
	cout << ans << endl;
	return 0;
}