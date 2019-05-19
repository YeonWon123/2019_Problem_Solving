#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main()
{
	int n, m;
	int target, cnt, ans = 0;
	list<int> lst;
	list<int>::iterator it;

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		lst.push_back(i);

	it = lst.begin();
	for (int i = 0; i < m; i++)
	{
		cin >> target;
		cnt = 0;
		while (*it != target) {
			it++; 
			cnt++;
			if (it == lst.end()) it = lst.begin();
		}
		ans += min(n - cnt, cnt);
		it = lst.erase(it);
		n--;
		if (it == lst.end()) it = lst.begin();
	}
	cout << ans << endl;
	return 0;
}