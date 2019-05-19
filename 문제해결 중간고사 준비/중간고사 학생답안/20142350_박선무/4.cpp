#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>

using namespace std;


int N;
int M;

int light[201];
int cache[201][201];
vector<int> grouped;
//int case_school(int x, int y)
//{
//	if (x == N - 1 && y == M) return 0;
//	
//}


int solve(int x, int y)
{
	int &ret = cache[x][y];

	if (x == y) return ret = 0;
	ret = 9999999;
	int val;
	for (int i = x; i < y-1; i++)
	{
		if (light[i] == light[i + 1])
			val = 0;
		else
			val = 1;
		ret = min(ret,val + solve(x,i) + solve(i+1,y));
	}
	return ret;
}

int main()
{
//	freopen("input.txt", "r", stdin);//다하고 무조건 주석

	cin >> N >> M;
	int pre = 9999;
	for (int i = 0; i < N; i++)
	{
		cin >> light[i];
		if (light[i] != pre)
			grouped.push_back(light[i]);
		pre = light[i];

	}
	if (M == 1)
	{
		printf("0\n");
		return 0;
	}
	int best = 0;
	int best_idx;
	int total = 0;
	while (1)
	{
		for (int i = 0; i < grouped.size(); i++)
		{
			//cout << grouped[i] << " ";
			int best_cnt = 0;
			for (int j = 1; j < M; j++)
			{
				if (i - j >= 0 && i + j < grouped.size())
				{
					if (grouped[i - j] == grouped[i + j])
					{
						best_cnt++;
					}
					else
						break;
				}
			}
			if (best_cnt > best)
			{
				best_idx = i;
				best = best_cnt;
			}
		}
		if (best != 0)
		{
			grouped.erase(grouped.begin() + best_idx - best, grouped.begin() + best_idx + best);
			total += best;
		}
		else if (grouped.size() != 1)
		{
			int mid = grouped.size() / 2;
			grouped.erase(grouped.begin() + mid);
			total++;
		}
		
		best = -1;
		if (grouped.size() == 1)
			break;
	}


	printf("%d\n", total);
	//cout << avail[5][5][5][5] << endl;
}
