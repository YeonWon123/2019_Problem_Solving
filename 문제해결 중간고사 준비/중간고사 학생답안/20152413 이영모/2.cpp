
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;

int arr[5001];
int res = 987654321;
int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	int left = 1, right = 1;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		right += arr[i];
	}
	while (left < right) {
		int mid = (left + right) / 2;
		int sum = 0, group = 1;
		int mmax = -1, mmin = 5001;
		int ret = 0;
		bool check = 1;
		for (int i = 1; i <= N; i++) {
			mmax = max(mmax, arr[i]);
			mmin = min(mmin, arr[i]);
			if (mmax - mmin <= mid) {
				ret = max(ret, mmax - mmin);
			}
			else if (mmax - mmin > mid) {
				group++;
				if (group > M) {
					check = 0;
					break;
				}
				mmax = -1, mmin = 5001;
				i = i - 1;
				continue;
			}
		}
		if (!check) {
			check = true;
			left = mid + 1;
			continue;
		}
		if (group <= M) {
			right = mid;
			res = min(res, ret);
		}
	}
	printf("%d", res);

	return 0;
}

