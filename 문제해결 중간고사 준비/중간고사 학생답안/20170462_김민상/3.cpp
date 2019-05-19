#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int DP[10001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, t;
	cin >> n >> t;
	DP[0] = 1;
	for (int i = 0; i < t; i++)
	{
		int a, b;
		cin >> a >> b;
		for (int j = n; j >= 0; j--)
		{
			for (int k = 1; k <= b; k++)
			{
				if(j - k * a >= 0)
					DP[j] += DP[j - k * a];
			}
		}
	}
	cout << DP[n];
	return 0;
}