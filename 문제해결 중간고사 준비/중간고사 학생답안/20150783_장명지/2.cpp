#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<math.h>
using namespace std;
int n;
int m;
int a[50001000];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	int l = 0;
	int r = n*10000;
	int mid, ans = 0;
	while (l <= r) {
		mid = (r + l) / 2;
		int std = a[0];
		int group = 1;
		for (int i = 0; i < n; i++) {

			//sum += a[i];
			//printf("%d %d %d\n",group,sum,mid);
			if (abs(std - a[i]) >= mid) {
				group++;
				std = a[i];

			}
		}
		if (group>m) {
			l = mid + 1;
			//printf("¿Þ %d %d\n", l,group);
			if(ans<mid)
				ans = mid;
		}
		else {
			r = mid - 1;
			//printf("¿À %d %d\n", r,group);
			//if (ans < mid)
				
		}

		
		
	}
	cout << ans << endl;
}