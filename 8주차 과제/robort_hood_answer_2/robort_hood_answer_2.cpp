#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct pos {
	int x, y;
	pos(int a, int b) : x(a), y(b) {}
	pos() {}
	bool operator < (pos &rhs) {
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
};

vector<pos> point;

int ccw(pos a, pos b, pos c) {
	long long ret = a.x * b.y + b.x * c.y + c.x * a.y;
	ret -= b.x * a.y + c.x * b.y + a.x * c.y;
	if (ret > 0) return 1;
	if (ret) return -1;
	return 0;
}

bool chk(pos a, pos b, pos c, pos d) {
	pos t = { b.x - a.x, b.y - a.y };
	pos tt = { d.x - c.x, d.y - c.y };
	return ccw({ 0, 0 }, t, tt) >= 0;
}

long long dist(pos a, pos b) {
	long long dx = b.x - a.x;
	long long dy = b.y - a.y;
	return dx * dx + dy * dy;
}

double rotatingCalipers() {
	vector<pos> hull;
	swap(point[0], *min_element(point.begin(), point.end()));
	sort(point.begin() + 1, point.end(), [](pos a, pos b) {
		int cw = ccw(point[0], a, b);
		if (cw) return cw > 0;
		return dist(point[0], a) < dist(point[0], b);
	});

	printf("\n최초정렬 좌표 확인\n");
	for (int i = 0; i < 100; i++) {
		printf("%d %d\n", point[i].x, point[i].y);
	}


	for (auto i : point) {
		while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), i) <= 0) {
			hull.pop_back();
		}
		hull.push_back(i);
	}

	printf("좌표의 개수 : %d\n", hull.size());
	printf("\n좌표 확인\n");
	for (int i = 0; i < hull.size(); i++) {
		printf("%d %d\n", hull[i].x, hull[i].y);
	}

	int pt = 0;
	long long ret = 0;
	for (int i = 0; i < hull.size(); i++) {
		while (pt + 1 < hull.size() && chk(hull[i], hull[i + 1], hull[pt], hull[pt + 1])) {
			ret = max(ret, dist(hull[i], hull[pt])); ++pt;
		}
		ret = max(ret, dist(hull[i], hull[pt]));
	}

	return sqrt(ret);
}

int main() {
	int n; cin >> n;
	point.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &point[i].x, &point[i].y);
	}
	printf("%lf", rotatingCalipers());
}