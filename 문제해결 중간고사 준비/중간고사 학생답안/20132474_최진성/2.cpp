#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;
int num[5003];
int low=0, high = 199999999;
int answer = 199999999;

bool make_group(int point) {
	int group = 1;
	int pos = 0;
	int max_num=0;
	int min_num=10001;

	while (pos < n) {
		int cur = num[pos++];

		max_num = max(max_num, cur);
		min_num = min(min_num, cur);

		if (max_num-min_num > point) {
			group++;
			pos--;
			max_num = 0;
			min_num = 10001;
		}
	}

	if (group <= m) return true;
	else return false;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w+", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
	}

	while (low <= high) {
		int mid = (low + high + 1) / 2;
		if (make_group(mid)) {
			if (mid < answer)
				answer = mid;
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	printf("%d", answer);

	return 0;
}