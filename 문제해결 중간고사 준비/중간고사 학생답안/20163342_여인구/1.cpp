#include <iostream>
#include <string>
#define MAX 1000000000	// 10^9
using namespace std;

char moo[MAX + 2] = {'m', 'o', 'o'};

int main() {
	int i = 3;
	int o = 3;	// 넣어야할 o의 갯수
	int now = 3;	// 문자 끝의 위치
	
	while (i <= MAX) {
		moo[i] = 'm';
		i++;
		for (int j = 0; j < o; j++) {
			moo[i] = 'o';
			i++;
		}
		o++;
		for (int j = 0; j < now; j++) {
			moo[i] = moo[j];
			i++;
		}
		now = i;
	}

	int n;
	cin >> n;
	cout << moo[n - 1];

	return 0;
}