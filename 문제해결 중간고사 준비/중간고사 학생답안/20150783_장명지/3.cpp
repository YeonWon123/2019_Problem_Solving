#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
int t, k;
//int m[100001];
int d[100001];
int c[100001];
vector<pair<int, int>> m;
int desc(int a, int b) {
	return a < b;
}
int slove(int des,int ans, int x) {
	des = (ans - m[x].second)*m[x].first;
	for (int i = x - 1; i >= 0; i--) {

	}
	return 0;
}
int main() {
	cin >> t >> k;
	int x, y;
	/*for (int i = 1; i < k; i++) {
		scanf("%d %d", &x, &y);
		c[x] = y;
	}
	for (int i = 1; i < k; i++) {
		d[i] = 100001;
	}

	for (int i = 0; i < k; i++) {
		for(int j=)
	}*/
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &x, &y);
		c[x] = y;
		//printf("%d %d\n", x, y);
		m.push_back({ x,y });
	}
	sort(m.begin(), m.end());
	//for (int i = 0; i < k; i++)
		//printf("############%d\n", m[i].first);
	int ans = 0;
	int des = 0,sans=0;
	for (int i = k-1; i>=0; i--) {
		ans = t / m[i].first;
		k %= m[i].first;
		cout << ans << endl;;
		if (m[i].second < ans) {
			des = (ans - m[i].second)*m[i].first;
			for (int j = m[i].first; j>=0; j--) {
				int dd = des / j;
				if (c[j] > dd)
					printf(" ตส\n");
				//dd %= j;
				
					
				printf("c: %d %d\n",des, dd);
			}
		}
	}
	
}