#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define MAX 100005
#define INF 987654321
#define MOD 31991
#pragma warning(disable:4996)
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;

typedef struct {
	ll x, y;
}cood;
int n;
cood arr[200100];
// ccw(a, b, c) == 0 일직선, == 1 반시계, == -1 시계
int ccw(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
	ll k = (ll)(bx - ax)*(cy - ay) - (ll)(cx - ax)*(by - ay);
	if (k > 0)return 1;
	if (k < 0)return -1;
	return 0;
}
int ccw(cood a, cood b, cood c) {
	return ccw(a.x, a.y, b.x, b.y, c.x, c.y);
}
ll get_dist(cood a, cood b) {
	return (b.x - a.x) * (b.x - a.x) + (b.y - a.y)*(b.y - a.y);
}
// 제일 작은 0번 좌표와 각 비교 -> convexhull용 정렬
bool cood_cmp(cood a, cood b) {
	int k = ccw(arr[0], a, b);
	if (!k)return abs(a.y - arr[0].y) + abs(a.x - arr[0].x) < abs(b.y - arr[0].y) + abs(b.x - arr[0].x);
	return k > 0;
}
void rotating_calipers() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &arr[i].x, &arr[i].y);
	}
	// convex_hull
	printf("n: %d\n", n);
	for (int i = 0; i < n; i++) {
		if (arr[0].y > arr[i].y || arr[0].y == arr[i].y && arr[0].x > arr[i].x) {
			swap(arr[0], arr[i]);
		}
	}

	// 정렬된 좌표들 확인
	printf("\n정렬된 좌표들을 확인\n");
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", arr[i].x, arr[i].y);
	}


	sort(arr + 1, arr + n, cood_cmp);

	// 정렬된 좌표들 확인
	printf("\n정렬된 좌표들을 확인\n");
	for (int i = 0; i < n; i++) {
		printf("%d %d\n", arr[i].x, arr[i].y);
	}

	vector<int> convex_hull = { 0 };
	for (int i = 1; i < n; i++) {
		while (convex_hull.size() > 1 && ccw(arr[convex_hull[convex_hull.size() - 2]], arr[convex_hull[convex_hull.size() - 1]], arr[i]) <= 0)
			convex_hull.pop_back();
		convex_hull.push_back(i);
	}

	// 컨벡스홀 확인
	printf("컨벡스홀 개수 : %d\n", convex_hull.size());

	printf("\n컨벡스홀 좌표 확인\n\n");
	for (int i = 0; i < convex_hull.size(); i++) {
		printf("%lld %lld\n", arr[convex_hull[i]].x, arr[convex_hull[i]].y);
	}

	//rotating calipers
	int j = 1, m = convex_hull.size();
	ll ans = 0;
	cood p = arr[0], q = arr[1];
	for (int i = 0; i < m; i++) {
		int ni = (i + 1) % m;
		while (true) {
			int nj = (j + 1) % m;
			int v = ccw(0, 0,
				arr[convex_hull[ni]].x - arr[convex_hull[i]].x, arr[convex_hull[ni]].y - arr[convex_hull[i]].y,
				arr[convex_hull[nj]].x - arr[convex_hull[j]].x, arr[convex_hull[nj]].y - arr[convex_hull[j]].y);
			if (v > 0)
				j = nj;
			else
				break;
		}
		ll v = get_dist(arr[convex_hull[i]], arr[convex_hull[j]]);
		if (ans < v) {
			ans = v;
			p = arr[convex_hull[i]];
			q = arr[convex_hull[j]];
		}
	}
	// ans -> 제일 긴 길이, p, q 그 좌표값
	double a = (double)(p.x - q.x), b = (double)(p.y - q.y);
	printf("%lf\n", sqrt(a*a + b * b));
}

int main()
{
	rotating_calipers();
	return 0;
}