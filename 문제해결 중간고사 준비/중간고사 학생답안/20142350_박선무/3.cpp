#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>

using namespace std;

//vector<char> moo;

int T;
int k;
int coin[10001];
int total_cnt[10001];
int added[10001];
vector<int> val;


int main()
{
	//freopen("input.txt", "r", stdin);//다하고 무조건 주석

	cin >> T;
	cin >> k;
	memset(coin, 0, sizeof(coin));
	memset(total_cnt, 0, sizeof(total_cnt));
	for (int i = 0; i < k; i++)
	{
		int in, cnt;
		cin >> in >> cnt;
		val.push_back(in);
		coin[in] = cnt;
	}
	for (int j = 0; j < val.size(); j++)
	{
		if (j == 0)
		{
			for (int i = 0; i <= coin[val[j]]; i++)
			{
				total_cnt[val[j] * i] = 1;
				//printf("%d = 1\n", val[j] * i);
			}
		}
		else
		{
			for (int i = 0; i <= T; i++)
			{
				for (int cnt = 1; cnt <= coin[val[j]]; cnt++)
				{
					int price = cnt * val[j];
					if (i - price >= 0 && total_cnt[i - price] > 0)
					{
						added[i] += total_cnt[i - val[j] * cnt];
						//printf("%d = %d + %d\n", i, price, i-price);
					}
				}

			}
			for (int f = 0; f <= T; f++)
			{
				//printf("added[%d] = %d\n", f, added[f]);
				total_cnt[f] += added[f];
			}
			memset(added, 0, sizeof(added));
		}
	}
	cout << total_cnt[T] << endl;
}
