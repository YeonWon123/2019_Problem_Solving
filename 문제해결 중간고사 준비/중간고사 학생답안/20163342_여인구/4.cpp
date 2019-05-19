#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 200
using namespace std;

int main() {
	int n, k;
	int light[MAX + 1] = { 0, };

	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> light[i];

	int i = 1, j = n, max = 0, maxLoc = 0;
	while (i <= j) {
		int temp = 0;
		if (light[i] == light[j]) {
			i++;
			j--;
			temp++;
			if (temp > max) {
				max = temp;
				maxLoc = i;
			}
		}
		else {
			i++;
			j = n;
		}

	}




	return 0;
}