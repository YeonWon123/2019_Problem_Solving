#include<iostream>

using namespace std;
typedef long long ll;

ll presum[100];

char solve(ll t, ll k)
{
	if (k == 0)return t == 1 ? 'm' : 'o';
	ll before = presum[k-1];
	if (before >= t)return solve(t, k - 1);
	if (t > before + k + 3)
	{
		t = t - (before + k + 3);
		return solve(t, k - 1);
	}
	else
	{
		t = t - before;
		if (t == 1)return 'm';
		else return 'o';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	presum[0] = 3;
	for (int i = 0; i < 31; i++)
		presum[i] = presum[i - 1] * 2 + i + 3;
	ll n;
	cin >> n;
	ll start;
	for (ll i = 0; i < 31; i++)
	{
		if (n < presum[i])
		{
			start = i;
			break;
		}
	}
	cout << solve(n, start);
	return 0;
}