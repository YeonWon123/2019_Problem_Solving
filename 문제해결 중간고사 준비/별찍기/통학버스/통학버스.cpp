/*
학교를 기준으로 하여 왼쪽 파트와 오른쪽 파트를 나누었다.
중요한 부분은 다 채웠을때와 다 채우지 않았을 때를 정확히 구분하고
버스가 학교를 갔다가 다시 돌아올때 어느 지점으로 컴백하는지가 중요하다.
*/

#include<iostream>
#include<algorithm>
using namespace std;

pair<int, int> ppl[30003];
bool cmp(pair<int, int> p1, pair<int, int> p2)
{
	return p1.first < p2.first;
}

int cal(int dir, int home, int bus, int school)
{
	int temp = bus;
	int cnt, i;

	if (dir == 1) cnt = school - ppl[0].first;
	else cnt = ppl[home - 1].first - school;

	for (dir ? i = 0 : i = home - 1; ppl[i].first != school;)
	{
		if (temp >= ppl[i].second)
		{
			temp -= ppl[i].second;
			ppl[i].second = 0;
		}
		else if (temp != 0 && temp < ppl[i].second)
		{
			ppl[i].second -= temp;
			temp = 0;
		}

		if (temp == 0 && ppl[i].second != 0)
		{
			temp = bus;
			cnt += abs(school - ppl[i].first) * 2;
		}

		if (ppl[i].second == 0)
		{
			dir ? cnt += abs(ppl[i + 1].first - ppl[i].first) : cnt += abs(ppl[i - 1].first - ppl[i].first);
			dir ? i++ : i--;
		}
	}
	return cnt;
}

int main()
{
	int home, bus, school;
	cin >> home >> bus >> school;
	for (int i = 0; i < home; i++)
		cin >> ppl[i].first >> ppl[i].second;
	ppl[home++].first = school;
	sort(ppl, ppl + home, cmp);

	int cnt = cal(1, home, bus, school);
	cnt += cal(0, home, bus, school);
	cout << cnt << endl;
	return 0;
}