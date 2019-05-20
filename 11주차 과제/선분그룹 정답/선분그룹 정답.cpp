/*
< 선분 그룹 >

이 문제는 최대 3000개의 선분을 입력 받고 그 선분들이 한 점이라도 공통된 점이 있다면 한 그룹으로 엮는다.
그룹의 수와 가장 많은 선분을 가진 그룹의 선분의 개수를 출력해주면 된다.


처음에는 선분의 식을 구해서 다른 선분의 양 끝점을 대입했을 때 - 와 + 가 나오는 경우에 교차하는 형태로 접근하려 했으나
모든 경우의 수를 고려하지 못할 뿐더러 코드가 매우 복잡했다.


결국 선분 교차 알고리즘을 검색하였고, 그 결과 CCW라는 새로운 알고리즘을 알게되었다.
CCW는 세 점이 시계 방향인지, 반 시계 방향인지, 평행한 지 알려주는 알고리즘이다.
CCW를 이용하여 선분 교차 여부를 판별하는 알고리즘을 짤 수 있었다.


1. 선분 교차 알고리즘 https ://onecoke.tistory.com/entry/%EC%84%A0%EB%B6%84-%EA%B5%90%EC%B0%A8-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-CCW-%EC%9D%B4%EC%9A%A9

2. 선분이 교차하는 경우, parent 배열 갱신(index가 큰 선분을 index가 작은 선분에 연결)
*/

#include <iostream>
#include <vector>
#include <memory.h>
#define SIZE 3001

using namespace std;

typedef struct _tagPoint
{
	int x, y;
}POINT;

// 약 25mb
int parent[SIZE];
int num[SIZE] = { 0 };
int n;
vector < pair<pair<int, int>, pair<int, int>> > v;

void Input()
{
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		v.push_back({ {x1, y1}, {x2, y2} });

		parent[i] = i;
		num[i] = 0;
	}
}

int CCW(pair<int, int> &p1, pair<int, int> &p2, pair<int, int> &p3)
{
	int op = p1.first * p2.second + p2.first*p3.second + p3.first*p1.second;
	op -= (p1.first*p3.second + p2.first*p1.second + p3.first*p2.second);

	if (op > 0) return 1;
	else if (op == 0) return 0;
	else return -1;
}

bool CheckIntersect(int line1, int line2)
{
	pair<int, int> p1 = v[line1].first;
	pair<int, int> p2 = v[line1].second;
	pair<int, int> p3 = v[line2].first;
	pair<int, int> p4 = v[line2].second;

	int line1_2 = CCW(p1, p2, p3) * CCW(p1, p2, p4);
	int line2_1 = CCW(p3, p4, p1) * CCW(p3, p4, p2);

	if (line1_2 == 0 && line2_1 == 0)
	{
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);

		return p1 <= p4 && p3 <= p2;
	}
	return line1_2 <= 0 && line2_1 <= 0;
}

bool visit[SIZE];

int getParent(int p)
{
	cout << "진행중...\n";
	if (parent[p] == p) return p;
	getParent(parent[p]);
}

void unoin_find(int a, int b)
{
	int p_a = getParent(a);
	int p_b = getParent(b);

	if (p_a < p_b) parent[p_b] = p_a;
	else if (p_a > p_b) parent[p_a] = p_b;
}

void solution()
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if (CheckIntersect(i, j))
			{
				cout << i << "와 " << j << "에서 선분교차!\n";
				unoin_find(i, j);
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	Input();
	solution();

	int iMax = 0;
	int cnt = 0;

	for (int i = 0; i < n; ++i)
	{
		if (parent[i] == i) ++cnt;
		num[getParent(i)]++;
		if (num[getParent(i)] > iMax) iMax = num[getParent(i)];
	}

	cout << cnt << '\n';
	cout << iMax << '\n';

	return 0;
}

