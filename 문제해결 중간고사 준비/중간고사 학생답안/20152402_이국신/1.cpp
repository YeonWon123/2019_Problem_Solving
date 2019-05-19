#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;
vector<int> a;
int n = 0;

void dq(int i) {
	if (n <= 3) {
		return;
	}
	int num;
	num = 2 * a[i - 1] + i + 3;
	a.push_back(num);

	if (a[i] >= n) {
		return;
	}

	dq(i + 1);
}


void finding(int k) {

	if (k == 0) {
		if (n == 1) {
			printf("m");
			return;
		}
		else {
			printf("o");
			return;
		}
	}

	if (n <= a[k - 1]) {
		finding(k - 1);
	}
	else if (n > a[k] - a[k - 1]) {
		finding(k - 1);
		n = n - (a[k] - a[k - 1]);
	}
	else {
		if (n == a[k - 1] + 1) {
			printf("m");
			return;
		}
		else {
			printf("o");
			return;
		}
	}
}
int main(void) {
	scanf("%d", &n);

	a.push_back(3);
	dq(1);

	int k = a.size() - 1;

	finding(k);

	return 0;
}